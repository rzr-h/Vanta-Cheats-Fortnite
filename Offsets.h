#pragma once

#include "Includes.h"

namespace Offsets {
	//Offsets
	FN_OFFSET UWorld = 0xcbf38b8;
	FN_OFFSET ObjectID = 0x18;

	//UWorld
	FN_OFFSET OwningGameInstance = 0x1a8; //UGameInstance*
	FN_OFFSET Levels = 0x160; //TArray<ULevel*>
	FN_OFFSET GameState = 0x148; //AGameStateBase*
	FN_OFFSET PersistentLevel = 0x30; //ULevel*

	//UWorld -> PersistentLevel (ULevel)
	FN_OFFSET AActors = 0x98;
	FN_OFFSET ActorCount = 0xA0;

	//UGameInstance
	FN_OFFSET LocalPlayers = 0x38; //TArray<ULocalPlayer*>

	//UPlayer
	FN_OFFSET PlayerController = 0x30; //APlayerController*

	//APlayerController
	FN_OFFSET AcknowledgedPawn = 0x310; //APawn*
	FN_OFFSET PlayerCameraManager = 0x328; //APlayerCameraManager*

	//APlayerCameraManager
	FN_OFFSET ViewPitchMin = 0x3174; //float
	FN_OFFSET ViewPitchMax = 0x3178; //float
	FN_OFFSET ViewYawMin = 0x317c; //float
	FN_OFFSET ViewYawMax = 0x3180; //float

	//AFortWeaponRanged
	FN_OFFSET TimeHeatWasLastAdded = 0x1414; //float
	FN_OFFSET TimeOverheatedBegan = 0x1418; //float
	FN_OFFSET OverheatValue = 0x140c; //float
	FN_OFFSET WeaponOverheatedAnimation = 0x1400; //UAnimMontage*

	//AActor
	FN_OFFSET bHidden = 0x58; //char
	FN_OFFSET RootComponent = 0x188; //USceneComponent*
	FN_OFFSET CustomTimeDilation = 0x64; //float

	//ACharacter
	FN_OFFSET Mesh = 0x2f0; //USkeletalMeshComponent*

	//USceneComponent
	FN_OFFSET bHiddenInGame = 0x189; //char
	FN_OFFSET RelativeLocation = 0x128; //FVector
	FN_OFFSET RelativeRotation = 0x140; //FRotator

	//APawn
	FN_OFFSET PlayerState = 0x290; //APlayerState*

	//AFortPlayerController
	FN_OFFSET DamageNumbersActor = 0x19a0; //AFortDamageNumbersActor*

	//AFortDamageNumbersActor
	FN_OFFSET HitPlayerColor = 0x2d4; //FLinearColor
	FN_OFFSET CriticalHitPlayerColor = 0x2e4; //FLinearColor
	FN_OFFSET HitEnemyColor = 0x2f4; //FLinearColor
	FN_OFFSET CriticalHitEnemyColor = 0x304; //FLinearColor
	FN_OFFSET HitBuildingColor = 0x314; //FLinearColor
	FN_OFFSET CriticalHitBuildingColor = 0x324; //FLinearColor
	FN_OFFSET ShieldHitColor = 0x334; //FLinearColor
	FN_OFFSET CriticalHitShieldColor = 0x344; //FLinearColor

	//AFortPlayerPawn
	FN_OFFSET CurrentVehicle = 0x21b8; //AActor*
	FN_OFFSET bIsDBNOCarrying = 0x32cf; //bool
	FN_OFFSET bIsSkydiving = 0x1a1d; //bool
	FN_OFFSET bIsParachuteOpen = 0x1a1e; //bool

	//AFortPawn
	FN_OFFSET bIsDBNO = 0x74a; //char
	FN_OFFSET bIsDying = 0x6d8; //char
	FN_OFFSET CurrentWeapon = 0x7f0; //AFortWeapon*

	//AFortPickup
	FN_OFFSET bPickedUp = 0x590; //bool
	FN_OFFSET PrimaryPickupItemEntry = 0x2f8; //FFortItemEntry

	//UFortItemDefinition
	FN_OFFSET DisplayName = 0x90; //FText
	FN_OFFSET Tier = 0x74; //EFortItemTier
	FN_OFFSET MaxTier = 0x75; //EFortItemTier

	//AFortPlayerStateAthena
	FN_OFFSET KillScore = 0x1084; //int32_t
	FN_OFFSET TeamKillScore = 0xfcc; //int32_t
	FN_OFFSET TeamIndex = 0x1070; //char

	//AFortWeapon
	FN_OFFSET WeaponData = 0x3d8; //UFortWeaponItemDefinition*
	FN_OFFSET TriggerType = 0xb7c; //EFortWeaponTriggerType
	FN_OFFSET bIsChargingWeapon = 0x312; //bool
	FN_OFFSET bIsEquippingWeapon = 0x310; //bool
	FN_OFFSET bIsTargeting = 0xa85; //bool
	FN_OFFSET bIsReloadingWeapon = 0x311; //bool
	FN_OFFSET AmmoCount = 0xb24; //int32_t
	FN_OFFSET ReticleDefaultColor = 0x5b0; //FColor
	FN_OFFSET ReticleEnemyColor = 0x5b4; //FColor
	FN_OFFSET ReticleBuildingColor = 0x5b8; //FColor
	FN_OFFSET ReticleNoTargetColor = 0x5bc; //FColor

	//ABuildingContainer
	FN_OFFSET bAlreadySearched = 0xfa9; //char	

	//AFortAthenaVehicle
	FN_OFFSET bPlayedDying = 0x6d8; //char
}