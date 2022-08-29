#pragma once

#define code_virtual CTL_CODE(FILE_DEVICE_UNKNOWN, 0x269, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_physical CTL_CODE(FILE_DEVICE_UNKNOWN, 0x472, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_image CTL_CODE(FILE_DEVICE_UNKNOWN, 0xfee, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_security 0xcabd5e5
#define physical_read 0x27b
#define physical_write 0xdfd
#define virtual_read 0xfc6
#define virtual_write 0x359

typedef struct t_virtual {
	INT32 security_code;
	INT32 process_id;
	INT32 virtual_mode;
	ULONGLONG address;
	ULONGLONG buffer;
	ULONGLONG size;
} e_virtual, * s_virtual;

typedef struct t_physical {
	INT32 security_code;
	INT32 process_id;
	INT32 physical_mode;
	ULONGLONG address;
	ULONGLONG buffer;
	ULONGLONG size;
} e_physical, * s_physical;

typedef struct t_image {
	INT32 security_code;
	INT32 process_id;
	ULONGLONG* address;
} e_image, * s_image;

namespace driver {
	HANDLE driver_handle;
	INT32 process_id;

	bool find_driver() {
		driver_handle = CreateFile("\\\\.\\\pymodule", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

		if (!driver_handle || (driver_handle == INVALID_HANDLE_VALUE))
			return false;

		return true;
	}

	void read_virtual_memory(PVOID address, PVOID buffer, DWORD size) {
		t_virtual arguments = { 0 };

		arguments.security_code = code_security;
		arguments.address = (ULONGLONG)address;
		arguments.buffer = (ULONGLONG)buffer;
		arguments.size = size;
		arguments.process_id = process_id;
		arguments.virtual_mode = virtual_read;

		DeviceIoControl(driver_handle, code_virtual, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	void write_virtual_memory(PVOID address, PVOID buffer, DWORD size) {
		t_virtual arguments = { 0 };

		arguments.security_code = code_security;
		arguments.address = (ULONGLONG)address;
		arguments.buffer = (ULONGLONG)buffer;
		arguments.size = size;
		arguments.process_id = process_id;
		arguments.virtual_mode = virtual_write;

		DeviceIoControl(driver_handle, code_virtual, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	void read_physical_memory(PVOID address, PVOID buffer, DWORD size) {
		t_virtual arguments = { 0 };

		arguments.security_code = code_security;
		arguments.address = (ULONGLONG)address;
		arguments.buffer = (ULONGLONG)buffer;
		arguments.size = size;
		arguments.process_id = process_id;
		arguments.virtual_mode = physical_read;

		DeviceIoControl(driver_handle, code_physical, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	void write_physical_memory(PVOID address, PVOID buffer, DWORD size) {
		t_virtual arguments = { 0 };

		arguments.security_code = code_security;
		arguments.address = (ULONGLONG)address;
		arguments.buffer = (ULONGLONG)buffer;
		arguments.size = size;
		arguments.process_id = process_id;
		arguments.virtual_mode = physical_write;

		DeviceIoControl(driver_handle, code_physical, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	uintptr_t find_image() {
		uintptr_t image_address = { NULL };
		t_image arguments = { NULL };

		arguments.security_code = code_security;
		arguments.process_id = process_id;
		arguments.address = (ULONGLONG*)&image_address;

		DeviceIoControl(driver_handle, code_image, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);

		return image_address;
	}

	INT32 find_process(LPCTSTR process_name) {
		PROCESSENTRY32 pt;
		HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pt.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hsnap, &pt)) {
			do {
				if (!lstrcmpi(pt.szExeFile, process_name)) {
					CloseHandle(hsnap);
					process_id = pt.th32ProcessID;
					return pt.th32ProcessID;
				}
			} while (Process32Next(hsnap, &pt));
		}
		CloseHandle(hsnap);


		return { NULL };
	}
}

template <typename T>
T read_virtual(uint64_t address) {
	T buffer{ };
	driver::read_virtual_memory((PVOID)address, &buffer, sizeof(T));
	return buffer;
}

template<typename T>
void write_virtual(uint64_t address, T buffer) {
	driver::write_virtual_memory((PVOID)address, &buffer, sizeof(T));
}

template <typename T>
T read_physical(uint64_t address) {
	T buffer{ };
	driver::read_physical_memory((PVOID)address, &buffer, sizeof(T));
	return buffer;
}

template<typename T>
void write_physical(uint64_t address, T buffer) {
	driver::write_physical_memory((PVOID)address, &buffer, sizeof(T));
}

UINT64 find_code_cave(UINT64 BaseAddress, int index)
{
	BYTE tmp = 0;
	int i = 0;
	int Size = 0;
	int w = 0;
	for (int i = 0; i < 0x7ffffffff; i++)
	{
		tmp = read_physical<BYTE>(BaseAddress + i);
		if (tmp == 0xcc)
			Size++;
		else if (Size > 200)
		{
			if (w == index)
			{
				//std::cout << "Code Cave at: " << (BaseAddress + i - Size) << " Size of: " << Size << "\n";
				return (BaseAddress + i - Size);
			}
			Size = 0;

			w++;
		}

		i++;
	}
	return 0;
}