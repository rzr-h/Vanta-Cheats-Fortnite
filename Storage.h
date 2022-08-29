#pragma once

#include "Includes.h"
#include "Math.h"

struct PlayerPawnData {
	std::string FName;
	float Distance;
	bool IsVisible;
	bool IsOnScreen;
	bool IsEquipping;
	bool IsCharging;
	bool IsCarrying;
	bool IsGliding;
	bool IsSkydiving;
	bool IsKnocked;
	bool IsReloading;
	bool IsTargetting;
	bool IsBot;
	bool IsValid;
	int ItemTier;
	float R;
	float G;
	float B;
	float A;
	FN_POINTER FortPawn;
	FN_POINTER Mesh;
	FN_POINTER PlayerStateAthena;
	FN_POINTER BonePointer;
	FN_POINTER RootComponent;
	FN_TEXT EquippedItem;
	FN_TEXT UserName;
	int AmmoCount;
	Vector Location;
	Vector Rotation;
	bool IsTeammate;
	float Team_R;
	float Team_G;
	float Team_B;
	float Team_A;
} _PlayerPawnData;

struct FortPickupData {
	Vector Location;
	std::string FName;
	bool IsOnScreen;
	std::string Name;
	int Tier;
	bool IsValid;
	bool bPickedUp;
	FN_POINTER FortPawn;
	FN_POINTER Mesh;
	FN_POINTER RootComponent;
	double R;
	double G;
	double B;
	double A;
};

inline bool operator==(const PlayerPawnData& a, const PlayerPawnData& b) {
	if (a.FortPawn == b.FortPawn)
		return true;
	return false;
}

inline bool operator==(const FortPickupData& a, const FortPickupData& b) {
	if (a.FortPawn == b.FortPawn)
		return true;
	return false;
}