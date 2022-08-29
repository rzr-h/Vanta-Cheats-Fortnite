#pragma once

#include "Includes.h"
#include "Math.h"

struct FVector {
	double X;
	double Y;
	double Z;
};

struct FRotator {
	double Pitch;
	double Yaw;
	double Roll;
};

struct FColor {
	double R = 0;
	double G = 0;
	double B = 0;
	double A = 0;
};

struct FLinearColor
{
	float R;
	float G;
	float B;
	float A;
};

struct FPawnHighlight {
	double Priority_28_E2E1B5344846E187B9C11B863A7F0698;
	FLinearColor Inner_21_4CC2801147EA190DE16F59B34F36853E;
	FLinearColor Outer_22_5A1D7D0543D303E8B54B66A7F7BD2E2E;
	double FresnelBrightness_23_52B0F96447FF640F47DF2895B0602E92;
	double FresnelExponent_24_B427CF0C441AA37ED49833BF7579DE6D;
	double UsesPulse_25_E29229F64E540F0617E4C4987AD77605;
};