/*

#pragma once

#include "Includes.h"
#include "CheatEncryption.h"

#define BASE_OPERATION 0x81
#define COMMAND_MAGIC BASE_OPERATION * 0x45 * 0x01
#define EFI_VARIABLE_NON_VOLATILE 0x00000001
#define EFI_VARIABLE_BOOTSERVICE_ACCESS 0x00000002
#define EFI_VARIABLE_RUNTIME_ACCESS 0x00000004
#define EFI_VARIABLE_HARDWARE_ERROR_RECORD 0x00000008
#define EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS 0x00000010
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS 0x00000020
#define EFI_VARIABLE_APPEND_WRITE 0x00000040
#define SE_SYSTEM_ENVIRONMENT_PRIVILEGE (22L)
#define ATTRIBUTES (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_HARDWARE_ERROR_RECORD | EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS | EFI_VARIABLE_APPEND_WRITE)
#define M_PI 3.1415926535

typedef NTSTATUS(*mNtQuerySystemInformation) (
    SYSTEM_INFORMATION_CLASS SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
    );

typedef NTSTATUS(*mNtSetSystemEnvironmentValueEx) (
    PUNICODE_STRING VariableName,
    LPGUID VendorGuid,
    PVOID Value,
    ULONG ValueLength,
    ULONG Attributes
    );

typedef NTSTATUS(*mRtlAdjustPrivilege) (
    ULONG Privilege, BOOLEAN Enable,
    BOOLEAN Client,
    PBOOLEAN WasEnabled
    );

typedef struct _MemoryCommand {
    int magic;
    int operation;
    unsigned long long data[6];
} MemoryCommand;

typedef struct _RTL_PROCESS_MODULE_INFORMATION
{
    HANDLE Section;
    PVOID MappedBase;
    PVOID ImageBase;
    ULONG ImageSize;
    ULONG Flags;
    USHORT LoadOrderIndex;
    USHORT InitOrderIndex;
    USHORT LoadCount;
    USHORT OffsetToFileName;
    UCHAR FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, * PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES
{
    ULONG NumberOfModules;
    RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, * PRTL_PROCESS_MODULES;

namespace Memory
{
    static HMODULE ntModule;
    static GUID DummyGuid = { 2 };

    static mNtQuerySystemInformation myNtQuerySystemInformation = (mNtQuerySystemInformation)NULL;
    static mNtSetSystemEnvironmentValueEx myNtSetSystemEnvironmentValueEx = (mNtSetSystemEnvironmentValueEx)NULL;
    static mRtlAdjustPrivilege myRtlAdjustPrivilege = (mRtlAdjustPrivilege)NULL;

    static BOOLEAN SeSystemEnvironmentWasEnabled;

    static uintptr_t currentProcessId = 0;
    static uintptr_t kernelModuleAddress;
    static uintptr_t kernel_PsLookupProcessByProcessId;
    static uintptr_t kernel_PsGetProcessSectionBaseAddress;
    static uintptr_t kernel_MmCopyVirtualMemory;
    static uintptr_t kernel_ZwProtectVirtualMemory;
    static uintptr_t kernel_KeStackAttachProcess;
    static uintptr_t kernel_KeUnstackDetachProcess;
    static uintptr_t kernel_NtCurrentProcess;


    static constexpr auto STATUS_INFO_LENGTH_MISMATCH = 0xC0000004;
    static constexpr auto SystemModuleInformation = 11;
    static constexpr auto SystemHandleInformation = 16;
    static constexpr auto SystemExtendedHandleInformation = 64;

    NTSTATUS SetSystemEnvironmentPrivilege(BOOLEAN Enable, PBOOLEAN WasEnabled)
    {
        if (WasEnabled != nullptr)
            *WasEnabled = FALSE;

        const NTSTATUS Status = myRtlAdjustPrivilege(SE_SYSTEM_ENVIRONMENT_PRIVILEGE, Enable, FALSE, &SeSystemEnvironmentWasEnabled);
        if (NT_SUCCESS(Status) && WasEnabled != nullptr)
            *WasEnabled = SeSystemEnvironmentWasEnabled;

        return Status;
    }

    void SendCommand(MemoryCommand* cmd)
    {
        wchar_t VarName[] = { 'B','o','o','t','e','r','C','-','D','r','i','v','e','r','\0' };
        UNICODE_STRING FVariableName = UNICODE_STRING();
        FVariableName.Buffer = VarName;
        FVariableName.Length = 28;
        FVariableName.MaximumLength = 30;
        myNtSetSystemEnvironmentValueEx(&FVariableName, &DummyGuid, cmd, sizeof(MemoryCommand), ATTRIBUTES);
        memset(VarName, 0, sizeof(VarName));
    }

    NTSTATUS copy_memory(uintptr_t src_process_id, uintptr_t src_address, uintptr_t dest_process_id, uintptr_t dest_address, size_t size)
    {
        uintptr_t result = 0;
        MemoryCommand cmd = MemoryCommand();
        cmd.operation = BASE_OPERATION * 0x45 * 0x3;
        cmd.magic = COMMAND_MAGIC;
        cmd.data[0] = (uintptr_t)src_process_id;
        cmd.data[1] = (uintptr_t)src_address;
        cmd.data[2] = (uintptr_t)dest_process_id;
        cmd.data[3] = (uintptr_t)dest_address;
        cmd.data[4] = (uintptr_t)size;
        cmd.data[5] = (uintptr_t)&result;
        SendCommand(&cmd);
        return (NTSTATUS)result;
    }

    NTSTATUS read_memory(uintptr_t process_id, uintptr_t address, uintptr_t buffer, size_t size)
    {
        return copy_memory(process_id, address, currentProcessId, buffer, size);
    }

    NTSTATUS write_memory(uintptr_t process_id, uintptr_t address, uintptr_t buffer, size_t size)
    {
        return copy_memory(currentProcessId, buffer, process_id, address, size);
    }

    uintptr_t GetBaseAddress(uintptr_t pid)
    {
        uintptr_t result = 0;
        MemoryCommand cmd = MemoryCommand();
        cmd.operation = BASE_OPERATION * 0x45 * 0x4;
        cmd.magic = COMMAND_MAGIC;
        cmd.data[0] = pid;
        cmd.data[1] = (uintptr_t)&result;
        SendCommand(&cmd);
        return result;
    }

    uintptr_t GetKernelModuleAddress(char* module_name)
    {
        void* buffer = nullptr;
        DWORD buffer_size = 0;

        NTSTATUS status = myNtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(SystemModuleInformation), buffer, buffer_size, &buffer_size);
        while (status == STATUS_INFO_LENGTH_MISMATCH)
        {
            VirtualFree(buffer, 0, MEM_RELEASE);
            buffer = VirtualAlloc(nullptr, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            if (buffer == 0) {
                return 0;
            }
            status = myNtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(SystemModuleInformation), buffer, buffer_size, &buffer_size);
        }

        if (!NT_SUCCESS(status))
        {
            VirtualFree(buffer, 0, MEM_RELEASE);
            return 0;
        }

        const PRTL_PROCESS_MODULES modules = (PRTL_PROCESS_MODULES)buffer;
        if (modules == nullptr) {
            VirtualFree(buffer, 0, MEM_RELEASE);
            return 0;
        }
        for (auto i = 0u; i < modules->NumberOfModules; ++i)
        {
            char* current_module_name = (char*)(modules->Modules[i].FullPathName + modules->Modules[i].OffsetToFileName);
            if (!_stricmp(current_module_name, module_name))
            {
                const uintptr_t result = (uintptr_t)(modules->Modules[i].ImageBase);
                VirtualFree(buffer, 0, MEM_RELEASE);
                return result;
            }
        }

        VirtualFree(buffer, 0, MEM_RELEASE);
        return 0;
    }

    uintptr_t GetKernelModuleExport(uintptr_t kernel_module_base, char* function_name)
    {
        if (!kernel_module_base)
        {
            return 0;
        }

        IMAGE_DOS_HEADER dos_header = { 0 };
        IMAGE_NT_HEADERS64 nt_headers = { 0 };

        read_memory(4, kernel_module_base, (uintptr_t)&dos_header, sizeof(dos_header));
        if (dos_header.e_magic != IMAGE_DOS_SIGNATURE)
        {
            return 0;
        }

        read_memory(4, kernel_module_base + dos_header.e_lfanew, (uintptr_t)&nt_headers, sizeof(nt_headers));
        if (nt_headers.Signature != IMAGE_NT_SIGNATURE)
        {
            return 0;
        }

        const auto export_base = nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
        const auto export_base_size = nt_headers.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
        if (!export_base || !export_base_size)
        {
            return 0;
        }

        const auto export_data = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(VirtualAlloc(nullptr, export_base_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));

        read_memory(4, kernel_module_base + export_base, (uintptr_t)export_data, export_base_size);

        const auto delta = reinterpret_cast<uintptr_t>(export_data) - export_base;
        const auto name_table = reinterpret_cast<UINT32*>(export_data->AddressOfNames + delta);
        const auto ordinal_table = reinterpret_cast<UINT16*>(export_data->AddressOfNameOrdinals + delta);
        const auto function_table = reinterpret_cast<UINT32*>(export_data->AddressOfFunctions + delta);

        for (auto i = 0u; i < export_data->NumberOfNames; ++i)
        {
            char* current_function_name = (char*)(name_table[i] + delta);
            if (!_stricmp(current_function_name, function_name))
            {
                const auto function_ordinal = ordinal_table[i];
                const auto function_address = kernel_module_base + function_table[function_ordinal];
                if (function_address >= kernel_module_base + export_base && function_address <= kernel_module_base + export_base + export_base_size)
                {
                    VirtualFree(export_data, 0, MEM_RELEASE);
                    return 0;
                }
                VirtualFree(export_data, 0, MEM_RELEASE);
                return function_address;
            }
        }

        VirtualFree(export_data, 0, MEM_RELEASE);
        return 0;
    }

    bool StartDriver()
    {
        std::cout << "\nhi ";
        currentProcessId = GetCurrentProcessId();

        ntModule = LoadLibraryW(TEXT(L"ntdll.dll"));
        std::cout << "\nntModule: " << ntModule;
        BYTE ntqsi[] = { 'N','t','Q','u','e','r','y','S','y','s','t','e','m','I','n','f','o','r','m','a','t','i','o','n',0 };
        myNtQuerySystemInformation = (mNtQuerySystemInformation)GetProcAddress(ntModule, (char*)ntqsi);

        BYTE nssevex[] = { 'N','t','S','e','t','S','y','s','t','e','m','E','n','v','i','r','o','n','m','e','n','t','V','a','l','u','e','E','x',0 };
        myNtSetSystemEnvironmentValueEx = (mNtSetSystemEnvironmentValueEx)GetProcAddress(ntModule, (char*)nssevex);

        BYTE rtlajp[] = { 'R','t','l','A','d','j','u','s','t','P','r','i','v','i','l','e','g','e',0 };
        myRtlAdjustPrivilege = (mRtlAdjustPrivilege)GetProcAddress(ntModule, (char*)rtlajp);

        NTSTATUS status = SetSystemEnvironmentPrivilege(true, &SeSystemEnvironmentWasEnabled);
        if (!NT_SUCCESS(status)) {
            return false;
        }

        BYTE nstosname[] = { 'n','t','o','s','k','r','n','l','.','e','x','e',0 };
        kernelModuleAddress = GetKernelModuleAddress((char*)nstosname);
        memset(nstosname, 0, sizeof(nstosname));

        BYTE pbid[] = { 'P','s','L','o','o','k','u','p','P','r','o','c','e','s','s','B','y','P','r','o','c','e','s','s','I','d',0 };
        kernel_PsLookupProcessByProcessId = GetKernelModuleExport(kernelModuleAddress, (char*)pbid);
        memset(pbid, 0, sizeof(pbid));

        BYTE gba[] = { 'P','s','G','e','t','P','r','o','c','e','s','s','S','e','c','t','i','o','n','B','a','s','e','A','d','d','r','e','s','s',0 };
        kernel_PsGetProcessSectionBaseAddress = GetKernelModuleExport(kernelModuleAddress, (char*)gba);
        memset(gba, 0, sizeof(gba));

        BYTE mmcp[] = { 'M','m','C','o','p','y','V','i','r','t','u','a','l','M','e','m','o','r','y',0 };
        kernel_MmCopyVirtualMemory = GetKernelModuleExport(kernelModuleAddress, (char*)mmcp);
        memset(mmcp, 0, sizeof(mmcp));

        ////////////////////////////////////


        //ZwProtectVirtualMemory 
        BYTE v1[] = { 'Z','w','P','r','o','t','e','c','t','V','i','r','t','u','a','l','M','e','m','o','r','y',0 };
        kernel_ZwProtectVirtualMemory = GetKernelModuleExport(kernelModuleAddress, (char*)v1);
        memset(v1, 0, sizeof(v1));
        std::cout << "\n ZwProtectVirtualMemory: " << kernel_ZwProtectVirtualMemory;

        //KeStackAttachProcess 
        BYTE v2[] = { 'K','e','S','t','a','c','k','A','t','t','a','c','h','P','r','o','c','e','s','s',0 };
        kernel_KeStackAttachProcess = GetKernelModuleExport(kernelModuleAddress, (char*)v2);
        memset(v2, 0, sizeof(v2));
        std::cout << "\n KeStackAttachProcess: " << kernel_KeStackAttachProcess;

        //KeUnstackDetachProcess (funktioniert)
        BYTE v3[] = { 'K','e','U','n','s','t','a','c','k','D','e','t','a','c','h','P','r','o','c','e','s','s',0 };
        kernel_KeUnstackDetachProcess = GetKernelModuleExport(kernelModuleAddress, (char*)v3);
        memset(v3, 0, sizeof(v3));
        std::cout << "\n KeUnstackDetachProcess: " << kernel_KeUnstackDetachProcess;

        std::cout << "\n PsLookupProcessByProcessId: " << kernel_PsLookupProcessByProcessId;
        //Sleep(-1);
        uintptr_t result = 0;
        MemoryCommand cmd = MemoryCommand();
        cmd.operation = BASE_OPERATION * 0x45 * 0x2;
        cmd.magic = COMMAND_MAGIC;
        cmd.data[0] = kernel_PsLookupProcessByProcessId;
        cmd.data[1] = kernel_PsGetProcessSectionBaseAddress;
        cmd.data[2] = kernel_MmCopyVirtualMemory;
        cmd.data[3] = (uintptr_t)&result;
        SendCommand(&cmd);
        std::cout << "\nresult: " << result;
        return result;
    }

    uintptr_t ProtectAddressXD(uintptr_t TargetPid, uintptr_t Address) {
        uintptr_t result = 0;
        MemoryCommand cmd = MemoryCommand();

        cmd.operation = BASE_OPERATION * 0x45 * 0x5;
        cmd.magic = COMMAND_MAGIC;

        cmd.data[0] = (uintptr_t)TargetPid; //pid
        cmd.data[1] = (uintptr_t)Address; //addr to unprotect
        cmd.data[2] = (uintptr_t)4; //region size (must be 4!)
        cmd.data[3] = (uintptr_t)&result;

        SendCommand(&cmd);
        return result;
        //0 = pid
        //1 = addr to unprotect
        //2 = region size
        //3 = result addr
    }

    template <typename T> T read(const uintptr_t process_id, const uintptr_t address, PNTSTATUS out_status = 0)
    {
        T buffer{ };
        NTSTATUS status = read_memory(process_id, address, (uintptr_t)&buffer, sizeof(T));
        if (out_status)
        {
            *out_status = status;
        }
        return buffer;
    }

    template <typename T> void write(const uintptr_t process_id, const uintptr_t address, const T& buffer, PNTSTATUS out_status = 0)
    {
        NTSTATUS status = write_memory(process_id, address, (uintptr_t)&buffer, sizeof(T));
        if (out_status)
        {
            *out_status = status;
        }
    }
};

void read_virtualEx(PVOID Base, PVOID Buffer, DWORD Size) {
    Memory::read_memory(ProcessID, (uintptr_t)Base, (uintptr_t)Buffer, Size);
}

void ReadVirtualMemory(uintptr_t Base, PVOID Buffer, DWORD Size) {
    Memory::read_memory(ProcessID, (uintptr_t)Base, (uintptr_t)Buffer, Size);
}

template <typename T> static T read_virtual(uintptr_t address) {
    return Memory::read<T>(ProcessID, address);
}

template <typename T> static void write_virtual(uintptr_t address, T buffer) {
    return Memory::write<T>(ProcessID, address, buffer);
}

bool IsDriverLoaded()
{
    return false;
}*/