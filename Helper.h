#pragma once

#include "Includes.h"

namespace FortPointer {
	int ActorCount;
	int MyObjectID;
	int LocalWeaponTier;
	std::string LocalWeaponName;
	FN_POINTER UWorld;
	FN_POINTER CurrentVehicle;
	FN_POINTER LocalWeapon;
	FN_POINTER AActors;
	FN_POINTER LocalPlayerState;
	FN_POINTER LocalPlayerPawn;
	FN_POINTER LocalPlayerPawnOld;
	FN_POINTER LocalPlayerController;
	FN_POINTER LocalPlayerRootComponent;
	FN_POINTER LocalCameraManager;
	FN_POINTER LocalPlayerMesh;
	FN_POINTER LocalPlayerBonePointer;
	FN_POINTER LocalPlayer;
}

namespace FortCamera {
	Vector Location;
	Vector Rotation;
	double FOV;
}

void Mouse(float x, float y, float smooth)
{
	float ScreenCenterX = CenterX;
	float ScreenCenterY = CenterY;
	int AimSpeed = smooth;
	float TargetX = 0;
	float TargetY = 0;

	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	mouse_event(MOUSEEVENTF_MOVE, static_cast<int>((float)TargetX), static_cast<int>((float)TargetY), NULL, NULL);
}

DWORD FindProcessID(std::string name) {
	PROCESSENTRY32 ProcessEntry;
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &ProcessEntry) == (int)1) {
		while (Process32Next(snapshot, &ProcessEntry) == (int)1) {
			if (std::string(ProcessEntry.szExeFile) == name)
				return ProcessEntry.th32ProcessID;
		}
	}

	CloseHandle(snapshot);
	return NULL;
}

boolean bIsInRectangle(double centerX, double centerY, double radius, double x, double y) {
	return x >= centerX - radius && x <= centerX + radius &&
		y >= centerY - radius && y <= centerY + radius;
}

void MenuWindow(HWND hWindow) {
	SetWindowLong(hWindow, GWL_EXSTYLE, WS_EX_TOOLWINDOW);
	UpdateWindow(hWindow);
}

void GameWindow(HWND hWindow) {
	SetWindowLong(hWindow, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
	UpdateWindow(hWindow);
}