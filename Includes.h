#pragma once

#include <iostream>
#include <windows.h>
#include <vcruntime.h>
#include <tlhelp32.h>
#include <uxtheme.h>
#include <dwmapi.h>
#include <winternl.h>
#include <thread>
#include <vector>
#include <array>
#include <WinInet.h>
#include <urlmon.h>
#include "Auth.h"

#include <d3d9.h>
#include <d3dx9tex.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "D3dx9")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Wininet.lib")

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

using namespace std;

#define FN_OFFSET ptrdiff_t
#define FN_POINTER uintptr_t
#define FN_TEXT string
#define FN_VECTOR Vector
#define FN_STORAGE_I int
#define FN_STORAGE_F float
#define FN_STORAGE_D double
#define BOPTION bool
#define FOPTION float
#define IOPTION int
#define C_FREEZE Sleep
#define TO_HEX hex
#define END_THIS endl
#define GET_KEY GetAsyncKeyState
#define __START CreateThread
#define RENDER_BACKGROUND ImGui::GetBackgroundDrawList
#define RENDER_FOREGROUND ImGui::GetForegroundDrawList
#define M_PI (double)3.1415926535

string RoleName = TEXT("User");
ImVec4 LocalRoleColor = ImVec4(0, 255, 71, 255);

ImVec4 Color_User = ImVec4(0, 255, 71, 255);
ImVec4 Color_Tester = ImVec4(0, 255, 255, 255);
ImVec4 Color_Reseller = ImVec4(200, 0, 255, 255);
ImVec4 Color_Staff = ImVec4(0, 150, 210, 255);
ImVec4 Color_Admin = ImVec4(255, 0, 0, 255);
ImVec4 Color_Developer = ImVec4(0, 255, 255, 255);
ImVec4 Color_Owner = ImVec4(255, 135, 255, 255);

float CenterX = GetSystemMetrics(0) / 2 - 1;
float CenterY = GetSystemMetrics(1) / 2 - 1;

IDirect3DDevice9Ex* pDevice = NULL;

FN_POINTER BaseAddress = (FN_POINTER)NULL;
FN_POINTER ProcessID = (FN_POINTER)NULL;

BOPTION bWriteAllowed = true;
BOPTION bReadAllowed = true;
BOPTION bProtectAllowed = true;
BOPTION bExploitsUnprotected = false;
BOPTION bValidatePlayers = true;
BOPTION bDoPlayerChecks = true;
BOPTION bGetPlayerData = true;
BOPTION bDefinePointers = true;
BOPTION bGetCameraPosition = true;
BOPTION bGetCameraRotation = true;
BOPTION bGetCameraFOV = true;
BOPTION bIsMenuOpen = true;
BOPTION bExploitsEnabled = false;
BOPTION bRunCheat = false;
BOPTION bShowVisualButtons = true;
BOPTION bCheckOnScreen = true;

using namespace Security;

std::string name = TEXT("test123");
std::string ownerid = TEXT("JwBrOBvq5Z");
std::string secret = Security::encryption::encode(TEXT("80461e652b392556f5ab05bea62fbf35460e0de25aabc0b1b6aad4ff0075149c"));
std::string version = TEXT("1.0");

api KeyAuthApp(name, ownerid, secret, version);

template<typename T2, typename T1>
inline T2 lexical_cast(const T1& in) {
	T2 out;
	std::stringstream ss;
	ss << in;
	ss >> out;
	return out;
}

template <typename ElemT>
struct HexTo {
	ElemT value;
	operator ElemT() const { return value; }
	friend std::istream& operator>>(std::istream& in, HexTo& out) {
		in >> std::hex >> out.value;
		return in;
	}
};