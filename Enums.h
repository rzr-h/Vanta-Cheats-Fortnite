#pragma once

#include "Includes.h"

enum class EFortItemTier
{
	No_Tier = 0,
	I = 1, //uncommon
	II = 2, //common
	III = 3, //rare
	IV = 4, //epic
	V = 5, //legandary
	VI = 6,
	VII = 7,
	VIII = 8,
	IX = 9,
	X = 10,
	NumItemTierValues = 11,
	EFortItemTier_MAX = 12,
};

enum Assembly : DWORD
{
	JMP_REL8 = 0xEB,
	CALL = 0xE8,
	LEA = 0x8D,
	CDQ = 0x99,
	CMOVL = 0x4C,
	CMOVS = 0x48,
	INT3 = 0xCC,
	RET = 0xC3
};

enum class EFortWeaponTriggerType
{
	OnPress = 0,
	Automatic = 1,
	OnRelease = 2,
	OnPressAndRelease = 3,
	EFortWeaponTriggerType_MAX = 4,
};