#pragma once

#include "Includes.h"
#include "Math.h"
#include "Structs.h"
#include "Helper.h"
#include "CheatDriver.h"
#include "Offsets.h"

namespace Camera {
	Vector Location;
	Vector Rotation;
	float FOV;
}

void ResetAngles() {
	FN_STORAGE_F ViewPitchMin = -89.9999f;
	FN_STORAGE_F ViewPitchMax = 89.9999f;
	FN_STORAGE_F ViewYawMin = 0.0000f;
	FN_STORAGE_F ViewYawMax = 359.9999f;

	write_virtual<FN_STORAGE_F>(FortPointer::LocalCameraManager + Offsets::ViewPitchMin, ViewPitchMin);
	write_virtual<FN_STORAGE_F>(FortPointer::LocalCameraManager + Offsets::ViewPitchMax, ViewPitchMax);
	write_virtual<FN_STORAGE_F>(FortPointer::LocalCameraManager + Offsets::ViewYawMin, ViewYawMin);
	write_virtual<FN_STORAGE_F>(FortPointer::LocalCameraManager + Offsets::ViewYawMax, ViewYawMax);
}

void SetAngles(Vector CameraLocation, Vector TargetLocation) {
	Vector VectorPos = TargetLocation - CameraLocation;

	float distance = (double)(sqrtf(VectorPos.x * VectorPos.x + VectorPos.y * VectorPos.y + VectorPos.z * VectorPos.z));

	float x, y, z;
	x = -((acosf(VectorPos.z / distance) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510)) - 90.f);
	y = atan2f(VectorPos.y, VectorPos.x) * (float)(180.0f / 3.14159265358979323846264338327950288419716939937510);
	z = 0;

	write_virtual<FN_STORAGE_F>(FortPointer::LocalCameraManager + Offsets::ViewPitchMin, x);
	write_virtual<FN_STORAGE_F>(FortPointer::LocalCameraManager + Offsets::ViewPitchMax, x);
	write_virtual<FN_STORAGE_F>(FortPointer::LocalCameraManager + Offsets::ViewYawMin, y);
	write_virtual<FN_STORAGE_F>(FortPointer::LocalCameraManager + Offsets::ViewYawMax, y);
}

VOID GetCurrentCamera() {
	if (bGetCameraPosition) {
		FN_POINTER UWorld = read_virtual<FN_POINTER>(BaseAddress + Offsets::UWorld);
		FN_POINTER GameState = read_virtual<FN_POINTER>(UWorld + Offsets::GameState);

		double LocX = read_virtual<double>(GameState + 0x4B0);
		double LocY = read_virtual<double>(GameState + 0x4B8);
		double LocZ = read_virtual<double>(GameState + 0x4C0);

		FortCamera::Location.x = LocX; FortCamera::Location.y = LocY; FortCamera::Location.z = LocZ;
	}

	if (bGetCameraRotation) {
		FN_POINTER UWorld = read_virtual<FN_POINTER>(BaseAddress + Offsets::UWorld);
		FN_POINTER GameState = read_virtual<FN_POINTER>(UWorld + Offsets::GameState);

		double RotX = read_virtual<double>(GameState + 0x4C8);
		double RotY = read_virtual<double>(GameState + 0x4D0);
		double RotZ = read_virtual<double>(GameState + 0x4D8);

		if (RotY < 0)
			RotY = 360 + RotY;

		FortCamera::Rotation.x = RotX;
		FortCamera::Rotation.y = RotY;
		FortCamera::Rotation.z = RotZ;
	}

	if (bGetCameraFOV) {
		FN_POINTER GVP = read_virtual<FN_POINTER>(BaseAddress + 0xc5fa690);
		float RealFov = read_virtual<float>(GVP + 0x47C);

		FortCamera::FOV = RealFov;
	}
}

Vector BoneMatrix(FN_STORAGE_I BoneIndex, FN_POINTER Mesh, FN_POINTER BonePointer) {
	FTransform FirstBone = read_virtual<FTransform>(BonePointer + (BoneIndex * 0x60));
	FTransform ComponentToWorld = read_virtual<FTransform>(Mesh + 0x240);

	D3DMATRIX Matrix;
	Matrix = MatrixMultiplication(FirstBone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

	return Vector(Matrix._41, Matrix._42, Matrix._43);
}

Vector W2S(Vector WorldLocation)
{
	Vector ScreenLocation;
	D3DMATRIX tempMatrix = Matrix(Camera::Rotation);
	Vector vAxisX, vAxisY, vAxisZ;
	vAxisX = Vector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
	Vector vDelta = WorldLocation - Camera::Location;
	Vector vTransformed = Vector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
	if (vTransformed.z < .1f)
		vTransformed.z = .1f;
	double ScreenCenterX = CenterX;
	double ScreenCenterY = CenterY;
	ScreenLocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(Camera::FOV * (double)M_PI / 360.f)) / vTransformed.z;
	ScreenLocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(Camera::FOV * (double)M_PI / 360.f)) / vTransformed.z;
	return ScreenLocation;
}