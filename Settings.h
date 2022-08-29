#pragma once

#include "Includes.h"

namespace Options {
	//Aimbot
	namespace AssaultRifle {
		bool bAimbot = false;
		bool bBacktrack = false;
		bool bRenderFOV = false;
		bool bLineToTarget = false;
		bool bVisibleOnly = false;
		bool bKnockedPlayers = false;
		float fAimLineThickness = 0.f;
		float fAimbotSmooth = 0.f;
		float fAimbotFOV = 0.f;
		float fMaxAimbotDistance = 0.f;
		namespace AimbotMode {
			bool bMemory = false;
			bool bMouse = true;
		}
		namespace AimTarget {
			bool bClosestBone = true;
			bool bHead = false;
			bool bNeck = false;
			bool bBody = false;
		}
		namespace Aimkey {
			bool bUniversal = true;
			bool bLMouse = false;
			bool bRMouse = false;
			bool bShift = false;
		}
	}
	namespace SMG {
		bool bAimbot = false;
		bool bBacktrack = false;
		bool bRenderFOV = false;
		bool bLineToTarget = false;
		bool bVisibleOnly = false;
		bool bKnockedPlayers = false;
		float fAimLineThickness = 0.f;
		float fAimbotSmooth = 0.f;
		float fAimbotFOV = 0.f;
		float fMaxAimbotDistance = 0.f;
		namespace AimbotMode {
			bool bMemory = false;
			bool bMouse = true;
		}
		namespace AimTarget {
			bool bClosestBone = true;
			bool bHead = false;
			bool bNeck = false;
			bool bBody = false;
		}
		namespace Aimkey {
			bool bUniversal = true;
			bool bLMouse = false;
			bool bRMouse = false;
			bool bShift = false;
		}
	}
	namespace Shotgun {
		bool bAimbot = false;
		bool bBacktrack = false;
		bool bRenderFOV = false;
		bool bLineToTarget = false;
		bool bVisibleOnly = false;
		bool bKnockedPlayers = false;
		float fAimLineThickness = 0.f;
		float fAimbotSmooth = 0.f;
		float fAimbotFOV = 0.f;
		float fMaxAimbotDistance = 0.f;
		namespace AimbotMode {
			bool bMemory = false;
			bool bMouse = true;
		}
		namespace AimTarget {
			bool bClosestBone = true;
			bool bHead = false;
			bool bNeck = false;
			bool bBody = false;
		}
		namespace Aimkey {
			bool bUniversal = true;
			bool bLMouse = false;
			bool bRMouse = false;
			bool bShift = false;
		}
	}
	namespace Sniper {
		bool bAimbot = false;
		bool bBacktrack = false;
		bool bRenderFOV = false;
		bool bLineToTarget = false;
		bool bVisibleOnly = false;
		bool bKnockedPlayers = false;
		float fAimLineThickness = 0.f;
		float fAimbotSmooth = 0.f;
		float fAimbotFOV = 0.f;
		float fMaxAimbotDistance = 0.f;
		namespace AimbotMode {
			bool bMemory = false;
			bool bMouse = true;
		}
		namespace AimTarget {
			bool bClosestBone = true;
			bool bHead = false;
			bool bNeck = false;
			bool bBody = false;
		}
		namespace Aimkey {
			bool bUniversal = true;
			bool bLMouse = false;
			bool bRMouse = false;
			bool bShift = false;
		}
	}
	namespace OtherWeapons {
		bool bAimbot = false;
		bool bBacktrack = false;
		bool bRenderFOV = false;
		bool bLineToTarget = false;
		bool bVisibleOnly = false;
		bool bKnockedPlayers = false;
		float fAimLineThickness = 0.f;
		float fAimbotSmooth = 0.f;
		float fAimbotFOV = 0.f;
		float fMaxAimbotDistance = 0.f;
		namespace AimbotMode {
			bool bMemory = false;
			bool bMouse = true;
		}
		namespace AimTarget {
			bool bClosestBone = true;
			bool bHead = false;
			bool bNeck = false;
			bool bBody = false;
		}
		namespace Aimkey {
			bool bUniversal = true;
			bool bLMouse = false;
			bool bRMouse = false;
			bool bShift = false;
		}
	}

	//Exploits
	bool bNoBloom = false;
	bool bNoSpread = false;
	bool bNoReload = false;
	bool bNoCooldown = false;
	bool bSpinbot = false;
	bool bBoatBoost = false;
	bool bNoMinigunCooldown = false;
	bool bFullAuto = false;
	bool bFastWeapons = false;
	bool bDoublePump = false;
	bool bAllowAds = false;
	bool bAirstuck = false;
	bool bFovChanger = false;
	bool bInstaRes = false;
	bool bInstaReboot = false;
	bool bInstaActions = false;
	bool bSpeedHack = false;
	float fPublicFov = 80.f;
	float fSpeedMultiplier = 2.f;

	//Radar
	bool bRadar = true;
	bool bCircle = true;
	bool bRectangle = false;
	bool bUseTeamColor = true;
	bool bUseVisibleColor = false;
	bool bUseDistanceText = false;
	bool bUseTriangle = false;
	bool bShowLocalPlayer = false;
	bool bShowLineOfSight = false;
	bool bRadarOutline = false;
	bool bRadarDisplayLoot = false;
	bool bRadarDisplayPlayers = false;
	float fPositionX = 100.f;
	float fPositionY = 400.f;
	float fSize = 250.f;
	float fTransparency = 230.f;
	float fRadarRange = 10.f;

	//Player
	bool bCharacters = true;
	bool bPlayerInfo = true;
	bool bViewAngles = true;
	bool bSkeleton = true;
	bool bSnapline = true;
	bool bAmmoCount = true;
	bool bCurrentWeapon = true;
	bool bPlayerDistance = true;
	bool bOnBots = false;
	bool bOnTeammate = false;
	bool bTeamBar = false;
	
	float fMaxPlayerDistance = 200.f;
	namespace PlayerFonts {
		bool bStandardFont = false;
		bool bGTAFont = false;
		bool bFortniteFont = false;
		bool bArial = true;
		bool bRajdhani = false;
		bool bVerdana = false;
	}
	namespace PlayerFeatures {
		bool OutlinedText = true;
		bool TextBackground = false;
	}
	namespace PlayerColor {
		float BoxVisible[4];
		float BoxNotVisible[4];

		float SkeletonVisible[4];
		float SkeletonNotVisible[4];

		float SnaplineVisible[4];
		float SnaplineNotVisible[4];

		float TopTextVisible[4];
		float TopTextNotVisible[4];

		float BottomTextVisible[4];
		float BottomTextNotVisible[4];
	}
	namespace CharacterModes {
		bool b3D = false;
		bool b2D = true;
		bool bCorner = false;
		bool bFill2DBox = false;
	}
	namespace SnaplineStart {
		bool bTop = true;
		bool bBottom = false;
	}

	//Environment
	bool bVehicles = true;
	bool bSupplyDrop = false;
	bool bLLama = false;
	bool bChest = true;
	bool bAmmoBox = false;
	bool bFloppaSpawns = false;
	bool bShieldSources = false;
	bool bWeakspotAimbot = false;
	bool bItems = false;
	float fMaxItemDistance = 200.f;
	namespace ItemFonts {
		bool bStandardFont = true;
		bool bGTAFont = false;
		bool bFortniteFont = false;
		bool bArial = false;
		bool bRajdhani = false;
		bool bVerdana = false;
	}
	namespace ItemFeatures {
		bool bCornerBox = false;
		bool bSnapline;
		bool bOutline = false;
		bool bDistance = false;
	}
	namespace ItemTiers {
		bool bUncommon = false;
		bool bCommon = false;
		bool bRare = false;
		bool bEpic = true;
		bool bLegendary = true;
		bool bMythic = true;
	}

	//Misc
	bool bStreamProof = false;
	bool bCrosshair = true;
	bool bDisableGameCrosshair = false;
}

namespace Fonts
{
	ImFont* StandardFont;
	ImFont* GTAFont;
	ImFont* FortniteFont;
	ImFont* Arial;
	ImFont* Rajdhani;
	ImFont* Verdana;

	ImFont* TextureFont;
	/*ImFont* NormalFont;
	ImFont* VantaFont;
	ImFont* TextureFont;*/

}

namespace Settings
{
	namespace Misc {
		float Inner = 15;
		float Outer = 20;
	}

	namespace Aimbot
	{
		namespace AssaultRifle
		{
			bool Enable = false;
			bool LineToTarget = false;
			bool DrawAimFov = false;
			bool VisibleOnly = false;
			bool BackTrack = false;
			bool BackTrackOnShoot = false;
			bool ResetRotation = false;

			namespace AimPos
			{
				bool Head = true;
				bool Neck = false;
				bool Chest = false;
				bool Pelvis = false;
			}

			namespace AimKey
			{
				bool LeftMouseButton = true;
				bool RightMouseButton = false;
				bool SideMouseButton = false;
				bool Capslock = false;
				bool Shift = false;
				bool LeftAlt = false;
			}

			namespace AimType
			{
				bool Memory = true;
				bool Mouse = false;
				bool Arduino = false;
				bool Logitech = false;
			}

			float AimbotFOV = 0.0f;
			float AimbotSmooth = 0.0f;
		}
		namespace SMG
		{
			bool Enable = false;
			bool LineToTarget = false;
			bool DrawAimFov = false;
			bool VisibleOnly = false;
			bool BackTrack = false;
			bool BackTrackOnShoot = false;
			bool ResetRotation = false;

			namespace AimPos
			{
				bool Head = true;
				bool Neck = false;
				bool Chest = false;
				bool Pelvis = false;
			}

			namespace AimKey
			{
				bool LeftMouseButton = true;
				bool RightMouseButton = false;
				bool SideMouseButton = false;
				bool Capslock = false;
				bool Shift = false;
				bool LeftAlt = false;
			}

			namespace AimType
			{
				bool Memory = true;
				bool Mouse = false;
				bool Arduino = false;
				bool Logitech = false;
			}

			float AimbotFOV = 0.0f;
			float AimbotSmooth = 0.0f;
		}
		namespace ShotGun
		{
			bool Enable = false;
			bool LineToTarget = false;
			bool DrawAimFov = false;
			bool VisibleOnly = false;
			bool BackTrack = false;
			bool BackTrackOnShoot = false;
			bool ResetRotation = false;

			namespace AimPos
			{
				bool Head = true;
				bool Neck = false;
				bool Chest = false;
				bool Pelvis = false;
			}

			namespace AimKey
			{
				bool LeftMouseButton = true;
				bool RightMouseButton = false;
				bool SideMouseButton = false;
				bool Capslock = false;
				bool Shift = false;
				bool LeftAlt = false;
			}

			namespace AimType
			{
				bool Memory = true;
				bool Mouse = false;
				bool Arduino = false;
				bool Logitech = false;
			}

			float AimbotFOV = 0.0f;
			float AimbotSmooth = 0.0f;
		}
		namespace SniperRifle
		{
			bool Enable = false;
			bool LineToTarget = false;
			bool DrawAimFov = false;
			bool VisibleOnly = false;
			bool BackTrack = false;
			bool BackTrackOnShoot = false;
			bool ResetRotation = false;

			namespace AimPos
			{
				bool Head = true;
				bool Neck = false;
				bool Chest = false;
				bool Pelvis = false;
			}

			namespace AimKey
			{
				bool LeftMouseButton = true;
				bool RightMouseButton = false;
				bool SideMouseButton = false;
				bool Capslock = false;
				bool Shift = false;
				bool LeftAlt = false;
			}

			namespace AimType
			{
				bool Memory = true;
				bool Mouse = false;
				bool Arduino = false;
				bool Logitech = false;
			}

			float AimbotFOV = 0.0f;
			float AimbotSmooth = 0.0f;
		}
		namespace Other
		{
			bool Enable = false;
			bool LineToTarget = false;
			bool DrawAimFov = false;
			bool VisibleOnly = false;
			bool BackTrack = false;
			bool BackTrackOnShoot = false;
			bool ResetRotation = false;

			namespace AimPos
			{
				bool Head = true;
				bool Neck = false;
				bool Chest = false;
				bool Pelvis = false;
			}

			namespace AimKey
			{
				bool LeftMouseButton = true;
				bool RightMouseButton = false;
				bool SideMouseButton = false;
				bool Capslock = false;
				bool Shift = false;
				bool LeftAlt = false;
			}

			namespace AimType
			{
				bool Memory = true;
				bool Mouse = false;
				bool Arduino = false;
				bool Logitech = false;
			}

			float AimbotFOV = 0.0f;
			float AimbotSmooth = 0.0f;
		}
	}

	namespace Visuals
	{
		namespace Player
		{
			bool OutlinedText = false;
			bool Characters = true;
			bool Skeleton = true;
			bool Snaplines = true;
			bool Distance = true;
			bool Platform = true;
			bool Username = false;
			bool EquippedWeapon = true;
			bool AmmoCount = true;
			bool ViewAngles = true;
			bool ShowAI = false;
			bool ShowTeammates = false;
			float MaxDistance = 200.f;
			float ViewAngleLineLenght = 0.f;
			namespace BoxMode {
				bool Box3D = false;
				bool BoxCornered = false;
				bool Box2D = true;
				bool Option_Filled = true;
			}
			namespace Color {
				float BoxVisible[4];
				float BoxNotVisible[4];
				float BoxTarget[4];
				float BoxTeammate[4];

				float SkeletonVisible[4];
				float SkeletonNotVisible[4];
				float SkeletonTarget[4];
				float SkeletonTeammate[4];

				float SnaplineVisible[4];
				float SnaplineNotVisible[4];
				float SnaplineTarget[4];
				float SnaplineTeammate[4];

				float TopTextVisible[4];
				float TopTextNotVisible[4];
				float TopTextTarget[4];
				float TopTextTeammate[4];

				float BottomTextVisible[4];
				float BottomTextNotVisible[4];
				float BottomTextTarget[4];
				float BottomTextTeammate[4];
			}
		}
		namespace Environment
		{
			bool Chest = false;
			bool AmmoBox = false;
			bool SupplyDrop = false;
			bool LLama = false;
			bool UpgradeBench = false;
			bool Petrol = false;
			bool ShieldThing = false;
			bool Floppas = false;
			bool SpiderBouncer = false;
			bool Campfire = false;
			bool RebootVan = false;
			bool Rifts = false;

			bool bEnable = false;
			bool Box = false;
			bool Outlined = false;
			bool bEnableBox = false;
			bool ShowName = false;
			bool ShowDistance = false;
			namespace BoxMode {
				bool Box3D = false;
				bool BoxCornered = false;
				bool Box2D = true;
				bool Option_Filled = true;
			}
			float DistanceLimit = 200.f;
		}
	}

	namespace Exploits
	{
		bool VehicleFly = false;
		bool VehicleTp = false;
		bool Rapidfire = false;
		bool FirstPerson = false;
		bool oRapidfireOnlyWithSupportedGuns = false;
		bool RocketLeague = false;
		bool Spinbot = false;
		bool bSpinbotOnlyOnAimbot = false;
		bool InstantReload = false;
		bool SpeedHack = false;
		bool FovChanger = false;
		bool InstantWeapon = false;
		bool BigPlayers = false;
		bool BigPlayersOnLocalPlayer = false;
		bool PlayerFly = false;
		bool PickaxeTeleport = false;

		float CameraFOV = 100.f;
		float SpeedMultiplier = 5.f;
		float PlayerSizeMultiplier = 5.f;
		float SpinbotSpeed = 10.f;
		float PickaxeTeleportRange = 10.f;
	}

	namespace Renderer {
		bool Streamproof = false;
	}
}