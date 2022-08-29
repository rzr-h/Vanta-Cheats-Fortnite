#include "Includes.h"
#include "Hijacked.h"
#include "Helper.h"
#include "Shellcode.h"
#include "Console.h"

namespace Overlay {
    bool bExecuteOnce = true;
    bool bIsGameHijacked = false;
    struct DirectX9Interface {
        IDirect3D9Ex* IDirect3D9 = NULL;
        IDirect3DDevice9Ex* pDevice = NULL;
        D3DPRESENT_PARAMETERS pParameters = { NULL };
        MARGINS Margin = { -1 };
        MSG Message = { NULL };
    }DirectX9;
    HWND GetGDIHwnd(uintptr_t pProcess)
    {
        HWND hCurWnd = nullptr;
        do
        {
            hCurWnd = FindWindowEx(nullptr, hCurWnd, nullptr, nullptr);
            DWORD checkProcessID = 0;
            GetWindowThreadProcessId(hCurWnd, &checkProcessID);
            if (checkProcessID == pProcess)
            {
                char className[256];
                GetClassNameA(hCurWnd, className, 256);
                if (strstr(className, TEXT("GDI+ Hook Window Class"))) {
                    return hCurWnd;
                }

            }

        } while (hCurWnd != nullptr);

        return 0;
    }

    void BeginOverlay()
    {
        // get paint process id
        //if (!FindProcessID(TEXT("mspaint.exe"))) system(TEXT("start mspaint.exe"));

        Sleep(1000);

        // find window to hijack
        HWND hWnd = (HWND)1337;
        hWnd = GetGDIHwnd(FindProcessID(TEXT("mspaint.exe")));
        if (!hWnd || hWnd == (HWND)1337) {
            cout << TEXT("[") << hue::red << TEXT("!") << hue::reset << TEXT("] Failed to find paint window.") << endl;
            Sleep(-1);
            exit(0);
            *(uintptr_t*)(0) = 0;
        }

        // setup window style
        ShowWindow(hWnd, SW_SHOW);
        DwmExtendFrameIntoClientArea(hWnd, &DirectX9.Margin);
        SetWindowLongA(hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);

        ShowWindow(hWnd, SW_SHOW);
        UpdateWindow(hWnd);
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

         // create directx device 
        if (Direct3DCreate9Ex(D3D_SDK_VERSION, &DirectX9.IDirect3D9) < 0) {
            cout << TEXT("[") << hue::red << TEXT("!") << hue::reset << TEXT("] DirectX device failed.") << endl;
            Sleep(-1);
            exit(0);
            *(uintptr_t*)(0) = 0;
        }

        // window style settings

        D3DPRESENT_PARAMETERS pParamsInfo = {
            CenterX * 2, CenterY * 2, D3DFMT_A8R8G8B8, 0,
            D3DMULTISAMPLE_TYPE(0), D3DMULTISAMPLE_NONE,
            D3DSWAPEFFECT_DISCARD, hWnd, TRUE, TRUE, D3DFMT_D16, 0,
            0, D3DPRESENT_INTERVAL_ONE
        };

        // create device
        if (DirectX9.IDirect3D9->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &pParamsInfo, 0, &DirectX9.pDevice) < 0) {

            // release object
            DirectX9.IDirect3D9->Release();
            //Unload();
        }

        // initialize imgui
        ImGui::CreateContext();
        ImGui_ImplWin32_Init(hWnd);
        ImGui_ImplDX9_Init(DirectX9.pDevice);
        DirectX9.IDirect3D9->Release();

        //ImGui::GetIO().Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 16);
        ImGui::GetIO().Fonts->AddFontDefault();

        // wait until message is not equal to WM_QUIT
        ZeroMemory(&DirectX9.Message, sizeof(MSG));

        while (DirectX9.Message.message != WM_QUIT) {

            // peek hwnd message
            if (PeekMessage(&DirectX9.Message, hWnd, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&DirectX9.Message);
                DispatchMessage(&DirectX9.Message);
            }

            // handle input
            ImGuiIO& io = ImGui::GetIO();

            POINT point;
            GetCursorPos(&point);
            io.MousePos.x = point.x;
            io.MousePos.y = point.y;

            if (GetAsyncKeyState(VK_LBUTTON)) {
                io.MouseDown[0] = true;
                io.MouseClicked[0] = true;
                io.MouseClickedPos[0].x = io.MousePos.x;
                io.MouseClickedPos[0].y = io.MousePos.y;
            }
            else {
                io.MouseDown[0] = false;
            }

            // one time setup window
            if (bExecuteOnce) {
                pParamsInfo.BackBufferWidth = CenterX * 2;
                pParamsInfo.BackBufferHeight = CenterY * 2;
                SetWindowPos(hWnd, (HWND)0, 0, 0, CenterX * 2, CenterY * 2, SWP_NOREDRAW);
                DirectX9.pDevice->Reset(&pParamsInfo);
                auto io = ImGui::GetIO();
                Fonts::TextureFont = io.Fonts->AddFontFromMemoryTTF((void*)shTextureFont, 40.f, 40.f);
                Fonts::StandardFont = io.Fonts->AddFontDefault();
                Fonts::Verdana = io.Fonts->AddFontFromMemoryTTF((void*)shVerdanaFont, 14.f, 14.f);
                Fonts::FortniteFont = io.Fonts->AddFontFromMemoryTTF((void*)shFortniteFont, 14.f, 14.f);
                Fonts::GTAFont = io.Fonts->AddFontFromMemoryTTF((void*)shGTAFont, 14.f, 14.f);
                Fonts::Arial = io.Fonts->AddFontFromMemoryTTF((void*)shArialFont, 14.f, 14.f);
                Fonts::Rajdhani = io.Fonts->AddFontFromMemoryTTF((void*)shRajdhani, 15.5f, 15.5f);
                
                bExecuteOnce = false;
            }

            // setup imgui frame
            ImGui_ImplDX9_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();            

            if (!bIsGameHijacked) {
                HijackGame(); bIsGameHijacked = true;
            }
            pDevice = DirectX9.pDevice;
            RenderHijackedGame(hWnd);

            // end imgui frame
            ImGui::EndFrame();

            // clear window
            DirectX9.pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

            // initialize scene
            if (DirectX9.pDevice->BeginScene() >= 0) {
                ImGui::Render();
                ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
                DirectX9.pDevice->EndScene();
            }

            // call original
            DirectX9.pDevice->Present(NULL, NULL, NULL, NULL);
        }

        // shutdown imgui frame
        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        // clear present
        if (DirectX9.pDevice != NULL) {
            DirectX9.pDevice->EndScene();
            DirectX9.pDevice->Release();
        }
        if (DirectX9.IDirect3D9 != NULL) {
            DirectX9.IDirect3D9->Release();
        }

        DestroyWindow(hWnd);
        //Unload();
    }
}