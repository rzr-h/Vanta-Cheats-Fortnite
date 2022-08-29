#include "Includes.h"
#include "Storage.h"
#include "Helper.h"
#include "CheatDriver.h"
#include "Offsets.h"
#include "FNamePool.h"
#include "CheatEncryption.h"
#include "Settings.h"
#include "DrawMenu.h"
#include "GameFunctions.h"
#include "PatternScan.h"
#include "KernelDriver.h"
#include "RenderHelper.h"
#include "Enums.h"
#include "Structs.h"
#include "Definitions.h"
#include "Streamproof.h"

namespace Cheat {
    vector<PlayerPawnData> PlayerPawns;
    vector<FortPickupData> ItemPawns;

    namespace LocalPlayer {
        VOID ValidateInfo(LPVOID lpParameter) {
            while (true) {
                if (FortPointer::LocalPlayerPawn) {
                    uintptr_t CurrentWeapon = read_virtual<uintptr_t>(FortPointer::LocalPlayerPawn + Offsets::CurrentWeapon);
                    uintptr_t WeaponData = read_virtual<uintptr_t>(CurrentWeapon + Offsets::WeaponData); //UFortWeaponItemDefinition*
                    uintptr_t DisplayName = read_virtual<uintptr_t>(WeaponData + Offsets::DisplayName); // DisplayName (FText)
                    uint32_t WeaponLength = read_virtual<uint32_t>(DisplayName + 0x38); // FText -> Length
                    wchar_t* WeaponName = new wchar_t[uintptr_t(WeaponLength) + 1];
                    //memory::read_virtual_memory(read_virtual<PVOID>(DisplayName + 0x30), WeaponName, WeaponLength * sizeof(wchar_t)); // FText -> Name
                    std::wstring wWeaponName(WeaponName);
                    std::string sWeaponName(wWeaponName.begin(), wWeaponName.end());

                    FortPointer::LocalWeaponName = sWeaponName;
                    FortPointer::LocalWeapon = CurrentWeapon;
                }
                
                Sleep(100);
            }
        }

        bool IsHoldingAssaultRifle() {
            if (FortPointer::LocalWeaponName == TEXT("Combat Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Assault Rifle  ") ||
                FortPointer::LocalWeaponName == TEXT("Light Machine Gun") ||
                FortPointer::LocalWeaponName == TEXT("Scoped Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Makeshift Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Sideways Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Heavy Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Infantry Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Suppressed Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Ranger Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Burst Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Primal Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Striker Burst Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Tactical Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Sideways Minigun") ||
                FortPointer::LocalWeaponName == TEXT("Burst Pulse Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Jules' Drum Gun") ||
                FortPointer::LocalWeaponName == TEXT("Brutus' Minigun") ||
                FortPointer::LocalWeaponName == TEXT("Spire Guardian's Primal Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Drum Gun") ||
                FortPointer::LocalWeaponName == TEXT("Shadow Midas' Drum Gun") ||
                FortPointer::LocalWeaponName == TEXT("MK-Seven Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Slone's Burst Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Thermal Scoped Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Skye's Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Minigun") ||
                FortPointer::LocalWeaponName == TEXT("Meowscle's Peow Peow Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Slone's Pulse Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Combat Assault Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Ocean's Burst Assault Rifle"))
                return true;

            return false;
        }

        bool IsHoldingShotgun() {
            if (FortPointer::LocalWeaponName == TEXT("Lever Action Shotgun") ||
                FortPointer::LocalWeaponName == TEXT("Combat Shotgun") ||
                FortPointer::LocalWeaponName == TEXT("Striker Pump Shotgun") ||
                FortPointer::LocalWeaponName == TEXT("Tactical Shotgun") ||
                FortPointer::LocalWeaponName == TEXT("Ranger Shotgun") ||
                FortPointer::LocalWeaponName == TEXT("Primal Shotgun") ||
                FortPointer::LocalWeaponName == TEXT("Pump Shotgun") ||
                FortPointer::LocalWeaponName == TEXT("Auto Shotgun") ||
                FortPointer::LocalWeaponName == TEXT("Charge Shotgun") ||
                FortPointer::LocalWeaponName == TEXT("Drum Shotgun") ||
                FortPointer::LocalWeaponName == TEXT("Dragon's Breath Shotgun") ||
                FortPointer::LocalWeaponName == TEXT("Spire Assassin's Primal Shotgun") ||
                FortPointer::LocalWeaponName == TEXT("Kit's Charge Shotgun"))
                return true;

            return false;
        }

        bool IsHoldingSMG() {
            if (FortPointer::LocalWeaponName == TEXT("Combat SMG") ||
                FortPointer::LocalWeaponName == TEXT("Burst SMG") ||
                FortPointer::LocalWeaponName == TEXT("Primal SMG") ||
                FortPointer::LocalWeaponName == TEXT("Tactical Submachine Gun") ||
                FortPointer::LocalWeaponName == TEXT("Rapid Fire SMG") ||
                FortPointer::LocalWeaponName == TEXT("Suppressed Submachine Gun") ||
                FortPointer::LocalWeaponName == TEXT("Makeshift Submachine Gun") ||
                FortPointer::LocalWeaponName == TEXT("Compact SMG") ||
                FortPointer::LocalWeaponName == TEXT("Kymera Ray Gun") ||
                FortPointer::LocalWeaponName == TEXT("Zyg and Choppy's Ray Gun"))
                return true;

            return false;
        }

        bool IsHoldingSniper() {
            if (FortPointer::LocalWeaponName == TEXT("Storm Scout") ||
                FortPointer::LocalWeaponName == TEXT("Dragon's Breath Sniper") ||
                FortPointer::LocalWeaponName == TEXT("Boom Sniper Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Storm Scout Sniper Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Hunter Bolt-Action Sniper") ||
                FortPointer::LocalWeaponName == TEXT("Rail Gun") ||
                FortPointer::LocalWeaponName == TEXT("Heavy Sniper Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Suppressed Sniper Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Bolt-Action Sniper Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Lever Action Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Automatic Sniper Rifle") ||
                FortPointer::LocalWeaponName == TEXT("Semi-Auto Sniper Rifle   "))
                return true;

            return false;
        }
    }

    namespace Radar {
        void RadarRange(float* x, float* y, float range)
        {
            if (fabs((*x)) > range || fabs((*y)) > range)
            {
                if ((*y) > (*x))
                {
                    if ((*y) > -(*x))
                    {
                        (*x) = range * (*x) / (*y);
                        (*y) = range;
                    }
                    else
                    {
                        (*y) = -range * (*y) / (*x);
                        (*x) = -range;
                    }
                }
                else
                {
                    if ((*y) > -(*x))
                    {
                        (*y) = range * (*y) / (*x);
                        (*x) = range;
                    }
                    else
                    {
                        (*x) = -range * (*x) / (*y);
                        (*y) = -range;
                    }
                }
            }
        }

        void CalcRadarPoint(Vector vOrigin, int& screenx, int& screeny)
        {
            FRotator vAngle = FRotator{ FortCamera::Rotation.x, FortCamera::Rotation.y, FortCamera::Rotation.z };
            auto fYaw = vAngle.Yaw * M_PI / 180.0f;
            float dx = vOrigin.x - FortCamera::Location.x;
            float dy = vOrigin.y - FortCamera::Location.y;

            //x' = x * cos(p) - y * sin(p)
            //y' = y * sin(p) - y * -cos(p)
            float fsin_yaw = sinf(fYaw);
            float fminus_cos_yaw = -cosf(fYaw);

            float x = dy * fminus_cos_yaw + dx * fsin_yaw;
            x = -x;
            float y = dx * fminus_cos_yaw - dy * fsin_yaw;

            float range = (float)Options::fRadarRange * 1000.f;

            RadarRange(&x, &y, range);

            mvec DrawPos = mvec(Options::fPositionX, Options::fPositionY);
            mvec DrawSize = mvec(Options::fSize, Options::fSize);

            int rad_x = (int)DrawPos.x;
            int rad_y = (int)DrawPos.y;

            float r_siz_x = DrawSize.x;
            float r_siz_y = DrawSize.y;

            int x_max = (int)r_siz_x + rad_x - 5;
            int y_max = (int)r_siz_y + rad_y - 5;

            screenx = rad_x + ((int)r_siz_x / 2 + int(x / range * r_siz_x));
            screeny = rad_y + ((int)r_siz_y / 2 + int(y / range * r_siz_y));

            if (screenx > x_max)
                screenx = x_max;

            if (screenx < rad_x)
                screenx = rad_x;

            if (screeny > y_max)
                screeny = y_max;

            if (screeny < rad_y)
                screeny = rad_y;
        }

        VOID DrawRadarBackground() {
            mvec RadarCenter = mvec(Options::fPositionX + (Options::fSize / 2), Options::fPositionY + (Options::fSize / 2));
            mvec TopLeftRadar = mvec(Options::fPositionX, Options::fPositionY);
            mvec TopRightRadar = mvec(Options::fPositionX + Options::fSize, Options::fPositionY);
            mvec BottomRadar = mvec(RadarCenter.x, Options::fPositionY + Options::fSize);

            ImGui::GetForegroundDrawList()->AddRectFilled(mvec(Options::fPositionX, Options::fPositionY), mvec(Options::fPositionX + Options::fSize, Options::fPositionY + Options::fSize), IM_COL32(35, 35, 35, Options::fTransparency), 0.f, 0);

            if (Options::bShowLineOfSight) {
                ImGui::GetForegroundDrawList()->AddLine(RadarCenter, TopLeftRadar, ImGui::GetColorU32({ 0.8f, 0.8f, 0.8f, 1.0f }), 1.f);
                ImGui::GetForegroundDrawList()->AddLine(RadarCenter, TopRightRadar, ImGui::GetColorU32({ 0.8f, 0.8f, 0.8f, 1.0f }), 1.f);
                ImGui::GetForegroundDrawList()->AddLine(RadarCenter, BottomRadar, ImGui::GetColorU32({ 0.8f, 0.8f, 0.8f, 1.0f }), 1.f);
            }

            if (Options::bRadarOutline) {
                ImGui::GetForegroundDrawList()->AddRect(mvec(Options::fPositionX, Options::fPositionY), mvec(Options::fPositionX + Options::fSize, Options::fPositionY + Options::fSize), IM_COL32(0, 0, 0, 255), 0.f, 0, 1.f);
            }

            if (Options::bShowLocalPlayer) {
                if (Options::bRectangle) {
                    ImGui::GetForegroundDrawList()->AddRectFilled(mvec(RadarCenter.x - 2.5, RadarCenter.y - 2.5), mvec(RadarCenter.x + 2.5, RadarCenter.y + 2.5), ImGui::GetColorU32({ 0.0f, 0.4f, 1.0f, 1.0f }), 0.f, 0);
                }
                else if (Options::bCircle) {
                    ImGui::GetForegroundDrawList()->AddCircleFilled(RadarCenter, 3.f, ImGui::GetColorU32({ 0.0f, 0.4f, 1.0f, 1.0f }), 12);
                }
            }
        }

        VOID AddToRadar(ImU32 Color, Vector WorldLocation, float fDistance) {
            int ScreenX, ScreenY = 0;
            CalcRadarPoint(WorldLocation, ScreenX, ScreenY);

            if (Options::bRectangle) {
                ImGui::GetForegroundDrawList()->AddRectFilled(mvec((float)ScreenX - 2.5, (float)ScreenY - 2.5), mvec((float)ScreenX + 2.5, (float)ScreenY + 2.5), Color);
            }
            else if (Options::bCircle) {
                ImGui::GetForegroundDrawList()->AddCircleFilled(mvec(ScreenX, ScreenY), 3, Color, 12);
            }

            if (Options::bUseDistanceText) {
                char Dist[256];
                sprintf_s(Dist, TEXT("(%.fm)"), fDistance);
                mvec SizeOfText = ImGui::CalcTextSize(Dist);
                if (Options::bRadarOutline) {
                    int iX = (float)ScreenX - (SizeOfText.x / 2);
                    int iY = ScreenY;
                    ImGui::GetForegroundDrawList()->AddText(mvec(iX + 1, iY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), Dist);
                    ImGui::GetForegroundDrawList()->AddText(mvec(iX - 1, iY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), Dist);
                    ImGui::GetForegroundDrawList()->AddText(mvec(iX + 1, iY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), Dist);
                    ImGui::GetForegroundDrawList()->AddText(mvec(iX - 1, iY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), Dist);
                }
                ImGui::GetForegroundDrawList()->AddText(mvec((float)ScreenX - (SizeOfText.x / 2), ScreenY), Color, Dist);
            }
        }
    }

    namespace Exploits {
        VOID ApplyGameData() {
            while (true) 
                if (bExploitsUnprotected) {
                    //bNoBloom
                    {
                        static bool bWroteNoBloom = false;
                        if (Options::bNoBloom)
                        {
                            for (int x = 0; x < 8; x++) {
                                write_virtual<BYTE>(BaseAddress + 0x4691A1 + x, 0x90);
                            }

                            bWroteNoBloom = true;
                        }
                        else {
                            if (bWroteNoBloom)
                            {
                                write_virtual<BYTE>(BaseAddress + 0x4691A1 + 0, 0xF3);
                                write_virtual<BYTE>(BaseAddress + 0x4691A1 + 1, 0xF);
                                write_virtual<BYTE>(BaseAddress + 0x4691A1 + 2, 0x10);
                                write_virtual<BYTE>(BaseAddress + 0x4691A1 + 3, 0x80);
                                write_virtual<BYTE>(BaseAddress + 0x4691A1 + 4, 0x4C);
                                write_virtual<BYTE>(BaseAddress + 0x4691A1 + 5, 0x1);
                                write_virtual<BYTE>(BaseAddress + 0x4691A1 + 6, 0x0);
                                write_virtual<BYTE>(BaseAddress + 0x4691A1 + 7, 0x0);
                                bWroteNoBloom = false;
                            }
                        }
                    }

                    //bNoReload
                    {
                        static bool bWroteNoReload = false;
                        if (Options::bNoReload)
                        {
                            BYTE Verify = read_virtual<BYTE>(BaseAddress + 0x70EEBC1);
                            if (Verify != 0x90) {
                                for (int x = 0; x < 8; x++) {
                                    write_virtual<BYTE>(BaseAddress + 0x70EEBC1 + x, 0x90);
                                }
                                bWroteNoReload = true;
                            }
                        }
                        else {
                            if (bWroteNoReload)
                            {
                                write_virtual<BYTE>(BaseAddress + 0x70EEBC1 + 0, 0xF3);
                                write_virtual<BYTE>(BaseAddress + 0x70EEBC1 + 1, 0xF);
                                write_virtual<BYTE>(BaseAddress + 0x70EEBC1 + 2, 0x10);
                                write_virtual<BYTE>(BaseAddress + 0x70EEBC1 + 3, 0x90);
                                write_virtual<BYTE>(BaseAddress + 0x70EEBC1 + 4, 0xE8);
                                write_virtual<BYTE>(BaseAddress + 0x70EEBC1 + 5, 0x0);
                                write_virtual<BYTE>(BaseAddress + 0x70EEBC1 + 6, 0x0);
                                write_virtual<BYTE>(BaseAddress + 0x70EEBC1 + 7, 0x0);
                                bWroteNoReload = false;
                            }
                        }
                    }

                    //bCooldown
                    {
                        static bool bWroteNoCooldown = false;
                        if (Options::bNoCooldown)
                        {
                            BYTE Verify = read_virtual<BYTE>(BaseAddress + 0x7129464);
                            if (Verify != 0x90) {
                                for (int x = 0; x < 9; x++) {
                                    write_virtual<BYTE>(BaseAddress + 0x7129464 + x, 0x90);
                                }
                                bWroteNoCooldown = true;
                            }
                        }
                        else {
                            if (bWroteNoCooldown)
                            {
                                write_virtual<BYTE>(BaseAddress + 0x7129464 + 0, 0xF3);
                                write_virtual<BYTE>(BaseAddress + 0x7129464 + 1, 0x41);
                                write_virtual<BYTE>(BaseAddress + 0x7129464 + 2, 0xF);
                                write_virtual<BYTE>(BaseAddress + 0x7129464 + 3, 0x5C);
                                write_virtual<BYTE>(BaseAddress + 0x7129464 + 4, 0xBE);
                                write_virtual<BYTE>(BaseAddress + 0x7129464 + 5, 0x60);
                                write_virtual<BYTE>(BaseAddress + 0x7129464 + 6, 0xA);
                                write_virtual<BYTE>(BaseAddress + 0x7129464 + 7, 0x0);
                                write_virtual<BYTE>(BaseAddress + 0x7129464 + 8, 0x0);
                                bWroteNoCooldown = false;
                            }
                        }
                    }

                    //bNoSpread
                    {
                        static BYTE OldSpread;
                        if (!OldSpread)
                            OldSpread = read_virtual<BYTE>(BaseAddress + 0xD70554);

                        static bool bWroteNoSpread = false;
                        BYTE bIsTargeting = read_virtual<BYTE>(FortPointer::LocalPlayerPawn + Offsets::bIsTargeting);
                        bool IsAiming = bIsTargeting == 0x40;

                        if (Options::bNoSpread && (GetAsyncKeyState(VK_RBUTTON) || GetAsyncKeyState(VK_LBUTTON) || IsAiming))
                        {
                            BYTE Verify = read_virtual<BYTE>(BaseAddress + 0xD70554);
                            if (Verify != 0xC3) {
                                write_virtual<BYTE>(BaseAddress + 0xD70554, 0xC3);
                                bWroteNoSpread = true;
                            }
                        }
                        else {
                            if (bWroteNoSpread)
                            {
                                write_virtual<BYTE>(BaseAddress + 0xD70554, OldSpread);
                                bWroteNoSpread = false;
                            }
                        }
                    }
                }
                
                Sleep(100);
            }
        }
    }

    namespace Camera {
        VOID ValidateCamera(LPVOID lpParameter) {
            while (true) {
                GetCurrentCamera();
            }
        }
    }

    namespace Player {
        //Find and filter all players
        VOID FindPlayers(LPVOID lpParameter) {
            while (true) {
                FN_POINTER UWorld = read_virtual<FN_POINTER>(BaseAddress + Offsets::UWorld);
                if (!UWorld)
                    continue;

                FN_POINTER GameInstance = read_virtual<FN_POINTER>(UWorld + Offsets::OwningGameInstance);
                if (!GameInstance)
                    continue;

                FN_POINTER PersistentLevel = read_virtual<FN_POINTER>(UWorld + Offsets::PersistentLevel);
                if (!PersistentLevel)
                    continue;

                FN_POINTER LocalPlayers = read_virtual<FN_POINTER>(GameInstance + Offsets::LocalPlayers);
                if (!LocalPlayers)
                    continue;

                FN_POINTER LocalPlayer = read_virtual<FN_POINTER>(LocalPlayers);
                if (!LocalPlayer)
                    continue;

                FN_POINTER PlayerController = read_virtual<FN_POINTER>(LocalPlayer + Offsets::PlayerController);
                if (!PlayerController)
                    continue;

                FN_POINTER CameraManager = read_virtual<FN_POINTER>(PlayerController + Offsets::PlayerCameraManager);
                if (!CameraManager)
                    continue;
                FortPointer::LocalCameraManager = CameraManager; //xcxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
                FN_POINTER AcknowledgedPawn = read_virtual<FN_POINTER>(PlayerController + Offsets::AcknowledgedPawn);
                if ((AcknowledgedPawn != FortPointer::LocalPlayerPawnOld)) {
                    if (!PlayerPawns.empty())
                        PlayerPawns.clear();
                    if (!ItemPawns.empty())
                        ItemPawns.clear();
                    FortPointer::LocalPlayerPawnOld = AcknowledgedPawn;
                    continue;
                }
                if (!AcknowledgedPawn) {
                    FortPointer::LocalPlayerPawn = 0;
                    continue;
                }
                else {
                    FortPointer::LocalPlayerPawn = AcknowledgedPawn;
                }                

                FN_POINTER AActors = read_virtual<FN_POINTER>(PersistentLevel + Offsets::AActors);
                if (!AActors)
                    continue;

                FN_STORAGE_I ActorCount = read_virtual<FN_STORAGE_I>(PersistentLevel + Offsets::ActorCount);
                if (!ActorCount)
                    continue;

                FN_STORAGE_I MyObjectID = read_virtual<FN_STORAGE_I>(AcknowledgedPawn + Offsets::ObjectID);

                FN_POINTER LocalRootComponent = read_virtual<FN_POINTER>(AcknowledgedPawn + Offsets::RootComponent);

                FN_POINTER LocalPlayerState = read_virtual<FN_POINTER>(AcknowledgedPawn + Offsets::PlayerState);

                FN_POINTER LocalPlayerMesh = read_virtual<FN_POINTER>(AcknowledgedPawn + Offsets::Mesh);

                FN_POINTER LocalPlayerBonePointer = read_virtual<FN_POINTER>(LocalPlayerMesh + 0x590);

                if (bDefinePointers) {
                    FortPointer::UWorld = UWorld;
                    FortPointer::ActorCount = ActorCount;
                    FortPointer::AActors = AActors;
                    FortPointer::MyObjectID = MyObjectID;
                    FortPointer::LocalPlayerMesh = LocalPlayerMesh;
                    FortPointer::LocalPlayerBonePointer = LocalPlayerBonePointer;
                    FortPointer::LocalPlayerState = LocalPlayerState;
                    FortPointer::LocalPlayer = LocalPlayer;
                    FortPointer::LocalPlayerRootComponent = LocalRootComponent;
                    FortPointer::LocalPlayerController = PlayerController;
                    FortPointer::LocalCameraManager = CameraManager;
                    FortPointer::LocalPlayerPawn = AcknowledgedPawn;
                }
                
                for (FN_STORAGE_I Actor = NULL; Actor < ActorCount; Actor++) {
                    FN_POINTER CurrentActor = read_virtual<FN_POINTER>(AActors + (Actor * sizeof(FN_POINTER)));
                    if ((!CurrentActor) || (CurrentActor == AcknowledgedPawn))
                        continue;

                    FN_STORAGE_I ObjectID = read_virtual<FN_STORAGE_I>(CurrentActor + Offsets::ObjectID);
                    if (!ObjectID || (ObjectID == MyObjectID))
                        continue;
                    std::string ActorFName = GetFNameByObjectID(ObjectID);

                    if (ActorFName.find(TEXT("PlayerPawn")) != string::npos) {
                        float TeamR, TeamG, TeamB, TeamA = 0;

                        bool IsBot = true;
                        if (ActorFName.find(TEXT("Athena")) != string::npos)
                            IsBot = false;

                        if (IsBot)
                            continue;

                        FN_POINTER Mesh = read_virtual<FN_POINTER>(CurrentActor + Offsets::Mesh);
                        if (!Mesh)
                            continue;

                        FN_POINTER PlayerState = read_virtual<FN_POINTER>(CurrentActor + Offsets::PlayerState);
                        if (!PlayerState)
                            continue;

                        FN_POINTER RootComponent = read_virtual<FN_POINTER>(CurrentActor + Offsets::RootComponent);
                        if (!RootComponent)
                            continue;

                        FN_POINTER BonePointer = read_virtual<FN_POINTER>(Mesh + 0x590);
                        if (!BonePointer)
                            continue;

                        BYTE bIsDying = read_virtual<BYTE>(CurrentActor + Offsets::bIsDying);
                        bool bIsDead = bIsDying == 0x30;
                        if (bIsDead)
                            continue;

                        BYTE bIsDBNO = read_virtual<BYTE>(CurrentActor + Offsets::bIsDBNO);
                        bool UnSpawned = bIsDBNO == 0xCD;

                        bool IsTeammate = false;
                        FN_STORAGE_I MyTeamId = read_virtual<FN_STORAGE_I>(LocalPlayerState + Offsets::TeamIndex);
                        FN_STORAGE_I TeamId = read_virtual<FN_STORAGE_I>(PlayerState + Offsets::TeamIndex);
                        if (TeamId == MyTeamId)
                            IsTeammate = true;
                        if (IsTeammate)
                            continue;

                     
                        {
                            if (TeamId > 20) {
                                TeamId -= 20;
                                if (TeamId > 20) {
                                    TeamId -= 20;
                                    if (TeamId > 20) {
                                        TeamId -= 20;
                                        if (TeamId > 20) {
                                            TeamId -= 20;
                                        }
                                    }
                                }
                            }
                            TeamR = 30.f; TeamG = 230.f; TeamB = 30.f; TeamA = 255.f;
                            if (TeamId == 0) {
                                TeamR = 255.f; TeamG = 0.f; TeamB = 0.f; TeamA = 255.f;
                            }
                            else if (TeamId == 1) {
                                TeamR = 255.f; TeamG = 140.f; TeamB = 0.f; TeamA = 255.f;
                            }
                            else if (TeamId == 2) {
                                TeamR = 255.f; TeamG = 220.f; TeamB = 0.f; TeamA = 255.f;
                            }
                            else if (TeamId == 3) {
                                TeamR = 0.f; TeamG = 220.f; TeamB = 0.f; TeamA = 255.f;
                            }
                            else if (TeamId == 4) {
                                TeamR = 0.f; TeamG = 120.f; TeamB = 0.f; TeamA = 255.f;
                            }
                            else if (TeamId == 5) {
                                TeamR = 0.f; TeamG = 50.f; TeamB = 0.f; TeamA = 255.f;
                            }
                            else if (TeamId == 6) {
                                TeamR = 100.f; TeamG = 0.f; TeamB = 100.f; TeamA = 255.f;
                            }
                            else if (TeamId == 7) {
                                TeamR = 0.f; TeamG = 0.f; TeamB = 100.f; TeamA = 255.f;
                            }
                            else if (TeamId == 8) {
                                TeamR = 0.f; TeamG = 0.f; TeamB = 205.f; TeamA = 255.f;
                            }
                            else if (TeamId == 9) {
                                TeamR = 0.f; TeamG = 125.f; TeamB = 205.f; TeamA = 255.f;
                            }
                            else if (TeamId == 10) {
                                TeamR = 0.f; TeamG = 205.f; TeamB = 205.f; TeamA = 255.f;
                            }
                            else if (TeamId == 11) {
                                TeamR = 0.f; TeamG = 100.f; TeamB = 100.f; TeamA = 255.f;
                            }
                            else if (TeamId == 12) {
                                TeamR = 255.f; TeamG = 0.f; TeamB = 255.f; TeamA = 255.f;
                            }
                            else if (TeamId == 13) {
                                TeamR = 140.f; TeamG = 0.f; TeamB = 140.f; TeamA = 255.f;
                            }
                            else if (TeamId == 14) {
                                TeamR = 100.f; TeamG = 0.f; TeamB = 245.f; TeamA = 255.f;
                            }
                            else if (TeamId == 15) {
                                TeamR = 173.f; TeamG = 98.f; TeamB = 17.f; TeamA = 255.f;
                            }
                            else if (TeamId == 16) {
                                TeamR = 168.f; TeamG = 168.f; TeamB = 168.f; TeamA = 255.f;
                            }
                            else if (TeamId == 17) {
                                TeamR = 125.f; TeamG = 200.f; TeamB = 125.f; TeamA = 255.f;
                            }
                            else if (TeamId == 18) {
                                TeamR = 255.f; TeamG = 175.f; TeamB = 255.f; TeamA = 255.f;
                            }
                            else if (TeamId == 19) {
                                TeamR = 135.f; TeamG = 135.f; TeamB = 255.f; TeamA = 255.f;
                            }
                            else if (TeamId == 20) {
                                TeamR = 200.f; TeamG = 30.f; TeamB = 70.f; TeamA = 255.f;
                            }
                        }

                        Vector PlayerPosition = GetBoneMatrix(0, Mesh, BonePointer);
                        double Distance = FortCamera::Location.Distance(PlayerPosition) / 100;
                        if (Distance > Options::fMaxPlayerDistance)
                            continue;

                        PlayerPawnData PlayerPawn {
                            ActorFName,                                  // FName
                            Distance,                                    // Distance
                            false,                                       // IsVisible
                            false,                                       // IsOnScreen
                            false,                                       // IsEquipping
                            false,                                       // IsCharging
                            false,                                       // IsCarrying
                            false,                                       // IsGliding
                            false,                                       // IsSkydiving
                            false,                                       // IsKnocked
                            false,                                       // IsReloading
                            false,                                       // IsTargetting
                            IsBot,                                       // IsBot
                            true,                                        // IsValid
                            0,                                           // ItemTier 
                            150,                                         // R
                            152,                                         // G
                            154,                                         // B
                            255,                                         // A
                            CurrentActor,                                // FortPawn
                            Mesh,                                        // Mesh
                            PlayerState,                                 // PlayerState
                            BonePointer,                                 // BonePointer
                            RootComponent,                               // RootComponent
                            TEXT("(Unknown)"),                           // EquippedItem
                            TEXT("(Unknown)"),                           // UserName
                            NULL,                                        // AmmoCount
                            Vector(NULL, NULL, NULL),                    // Location
                            Vector(NULL, NULL, NULL),                    // Rotation
                            IsTeammate,                                  // IsTeammate
                            TeamR,                                       // TeamR
                            TeamG,                                       // TeamG
                            TeamB,                                       // TeamB
                            TeamA,                                       // TeamA
                        };

                        if (!PlayerPawns.empty()) {
                            auto Found = std::find(PlayerPawns.begin(), PlayerPawns.end(), PlayerPawn);
                            if (Found == PlayerPawns.end())
                                PlayerPawns.push_back(PlayerPawn);
                        }
                        else
                            PlayerPawns.push_back(PlayerPawn);
                    }
                }
                C_FREEZE(100);
            }
        }

        bool WasRecentlyRendered(FN_POINTER Mesh) {
            float fLastSubmitTime = read_virtual<float>(Mesh + 0x330);
            float fLastRenderTimeOnScreen = read_virtual<float>(Mesh + 0x338);
            const float fVisionTick = 0.06f;
            return fLastRenderTimeOnScreen + fVisionTick >= fLastSubmitTime;
        }

        VOID ValidatePlayers(LPVOID lpParameter) {
            while (true) {
                if (Options::bBoatBoost) {
                    FN_POINTER CurrentVehicle = read_virtual<FN_POINTER>(FortPointer::LocalPlayerPawn + Offsets::CurrentVehicle);
                    if (CurrentVehicle) {
                        write_virtual<float>(CurrentVehicle + 0xc64, 3); //CachedSpeed
                        write_virtual<float>(CurrentVehicle + 0x8d8, 3); //TopSpeedCurrentMultiplier
                        write_virtual<float>(CurrentVehicle + 0x8dc, 3); //PushForceCurrentMultiplier
                        write_virtual<float>(CurrentVehicle + 0x768, 100); //WaterEffectsVehicleMaxSpeedKmh
                    }
                }
                if (Options::bAllowAds) {

                }
                if (Options::bFastWeapons) {

                }
                if (Options::bAirstuck) {
                    float CustomTimeDilation = read_virtual<float>(FortPointer::LocalPlayerPawn + Offsets::CustomTimeDilation);
                    if (GET_KEY(VK_CAPITAL)) {
                        if (CustomTimeDilation != 0.1f) {
                            write_virtual<float>(FortPointer::LocalPlayerPawn + Offsets::CustomTimeDilation, 0.1f);
                        }
                    }
                    else {
                        if (CustomTimeDilation != 1.f) {
                            write_virtual<float>(FortPointer::LocalPlayerPawn + Offsets::CustomTimeDilation, 1.f);
                        }
                    }
                }
                if (Options::bInstaRes) {
                    //AFortPlayerPawnAthena	ReviveFromDBNOTime	0x3f60	float

                    float ReviveFromDBNOTime = read_virtual<float>(FortPointer::LocalPlayerPawn + 0x3f60);
                    if (ReviveFromDBNOTime != 0.001f) {
                        write_virtual<float>(FortPointer::LocalPlayerPawn + 0x3f60, 0.001f);
                    }
                }
                if (Options::bDoublePump) {
                    //AFortWeapon	bIgnoreTryToFireSlotCooldownRestriction	0xf41	bool

                    bool bIgnoreTryToFireSlotCooldownRestriction = read_virtual<bool>(FortPointer::LocalPlayerPawn + 0xf41);
                    if (!bIgnoreTryToFireSlotCooldownRestriction) {
                        write_virtual<bool>(FortPointer::LocalPlayerPawn + 0xf41, true);
                    }
                }
                if (Options::bInstaReboot) {

                    //AFortPlayerStateAthena	InteractingRebootVan	0x1680	ABuildingGameplayActorSpawnMachine*
                    //ABuildingGameplayActorSpawnMachine	ResurrectionStartDelay	0x990	FScalableFloat
                    
                    float ResurrectionStartDelay = read_virtual<float>(FortPointer::LocalPlayerPawn + 0x1680 + 0x990);
                    if (ResurrectionStartDelay != 0.001f) {
                        write_virtual<float>(FortPointer::LocalPlayerPawn + 0x1680 + 0x990, 0.001f);
                    }
                }
                if (Options::bNoMinigunCooldown) {

                    float TimeHeatWasLastAdded = read_virtual<float>(FortPointer::LocalPlayerPawn + Offsets::TimeHeatWasLastAdded);
                    if (TimeHeatWasLastAdded != 0.f) {
                        write_virtual<float>(FortPointer::LocalPlayerPawn + Offsets::TimeHeatWasLastAdded, 0.f);
                    }

                    float TimeOverheatedBegan = read_virtual<float>(FortPointer::LocalPlayerPawn + Offsets::TimeOverheatedBegan);
                    if (TimeOverheatedBegan != 0.f) {
                        write_virtual<float>(FortPointer::LocalPlayerPawn + Offsets::TimeOverheatedBegan, 0.f);
                    }

                    float OverheatValue = read_virtual<float>(FortPointer::LocalPlayerPawn + Offsets::OverheatValue);
                    if (OverheatValue != 0.f) {
                        write_virtual<float>(FortPointer::LocalPlayerPawn + Offsets::OverheatValue, 0.f);
                    }

                    float WeaponOverheatedAnimation = read_virtual<float>(FortPointer::LocalPlayerPawn + Offsets::WeaponOverheatedAnimation);
                    if (WeaponOverheatedAnimation != 0.f) {
                        write_virtual<float>(FortPointer::LocalPlayerPawn + Offsets::WeaponOverheatedAnimation, 0.f);
                    }
                }
                if (Options::bFullAuto) {
                    FN_POINTER UFortWeaponItemDefinition = read_virtual<FN_POINTER>(FortPointer::LocalWeapon + Offsets::WeaponData);
                    EFortWeaponTriggerType TriggerType = read_virtual<EFortWeaponTriggerType>(UFortWeaponItemDefinition + Offsets::TriggerType);
                    if (TriggerType != EFortWeaponTriggerType::Automatic) {
                        write_virtual<EFortWeaponTriggerType>(UFortWeaponItemDefinition + Offsets::TriggerType, EFortWeaponTriggerType::Automatic);
                    }
                }

                for (int x = 0; x < PlayerPawns.size(); x++) {
                    FN_POINTER Mesh = read_virtual<FN_POINTER>(PlayerPawns[x].FortPawn + Offsets::Mesh);
                    if ((!Mesh) || (Mesh != PlayerPawns[x].Mesh)) {
                        PlayerPawns[x].IsValid = false;
                        continue;
                    }

                    FN_POINTER PlayerState = read_virtual<FN_POINTER>(PlayerPawns[x].FortPawn + Offsets::PlayerState);
                    if ((!PlayerState) || (PlayerState != PlayerPawns[x].PlayerStateAthena)) {
                        PlayerPawns[x].IsValid = false;
                        continue;
                    }

                    BYTE bIsDying = read_virtual<BYTE>(PlayerPawns[x].FortPawn + Offsets::bIsDying);
                    bool bIsDead = bIsDying == 0x30;
                    if (bIsDead) {
                        PlayerPawns[x].IsValid = false;
                        continue;
                    }

                    Vector BoneZero = GetBoneMatrix(0, PlayerPawns[x].Mesh, PlayerPawns[x].BonePointer);
                    double Distance = FortCamera::Location.Distance(BoneZero) / 100;
                    if (Distance > Options::fMaxPlayerDistance) {
                        PlayerPawns[x].IsValid = false;
                        continue;
                    }

                    PlayerPawns[x].Distance = Distance;

                    Vector BoneHead = GetBoneMatrix(98, PlayerPawns[x].Mesh, PlayerPawns[x].BonePointer);
                    if ((BoneHead.Distance(BoneZero) / 100) > 50) {
                        PlayerPawns[x].IsValid = false;
                        continue;
                    }

                    if (bCheckOnScreen) {
                        Vector Screen_v1 = W2S(BoneHead);
                        Vector Screen_v2 = W2S(BoneZero);
                        if (bIsInRectangle(CenterX, CenterY, 850, Screen_v1.x, Screen_v1.y) && bIsInRectangle(960, 540, 850, Screen_v2.x, Screen_v2.y)) {
                            PlayerPawns[x].IsOnScreen = true;
                        }
                        else {
                            PlayerPawns[x].IsOnScreen = false;
                        }
                    }

                    if (bGetPlayerData) {
                        FN_POINTER Weapon = read_virtual<FN_POINTER>(PlayerPawns[x].FortPawn + Offsets::CurrentWeapon);

                        int AmmoCountTemp = read_virtual<int32_t>(Weapon + Offsets::AmmoCount);
                        if (AmmoCountTemp > 9999)
                            PlayerPawns[x].AmmoCount = 999;
                        else
                            PlayerPawns[x].AmmoCount = AmmoCountTemp;

                        PlayerPawns[x].IsVisible = WasRecentlyRendered(PlayerPawns[x].Mesh);

                        PlayerPawns[x].IsReloading = read_virtual<bool>(Weapon + Offsets::bIsReloadingWeapon);

                        PlayerPawns[x].IsTargetting = read_virtual<bool>(Weapon + Offsets::bIsTargeting);

                        PlayerPawns[x].IsGliding = read_virtual<bool>(PlayerPawns[x].FortPawn + Offsets::bIsParachuteOpen);

                        PlayerPawns[x].IsSkydiving = read_virtual<bool>(PlayerPawns[x].FortPawn + Offsets::bIsSkydiving);

                        PlayerPawns[x].IsEquipping = read_virtual<bool>(Weapon + Offsets::bIsEquippingWeapon);

                        PlayerPawns[x].IsCharging = read_virtual<bool>(Weapon + Offsets::bIsChargingWeapon);

                        PlayerPawns[x].IsCarrying = read_virtual<bool>(PlayerPawns[x].FortPawn + Offsets::bIsDBNOCarrying);

                        PlayerPawns[x].Rotation = read_virtual<Vector>(PlayerPawns[x].RootComponent + Offsets::RelativeRotation);

                        BYTE bIsDBNO = read_virtual<BYTE>(PlayerPawns[x].FortPawn + Offsets::bIsDBNO);
                        PlayerPawns[x].IsKnocked = bIsDBNO == 0x5D;

                        uintptr_t CurrentWeapon = read_virtual<uintptr_t>(PlayerPawns[x].FortPawn + Offsets::CurrentWeapon);
                        if (!CurrentWeapon)
                            continue;
                        uintptr_t WeaponData = read_virtual<uintptr_t>(CurrentWeapon + Offsets::WeaponData);
                        if (!WeaponData)
                            continue;
                        uintptr_t DisplayName = read_virtual<uintptr_t>(WeaponData + Offsets::DisplayName);
                        if (!DisplayName)
                            continue;
                        uint32_t WeaponLength = read_virtual<uint32_t>(DisplayName + 0x38);
                        if (!WeaponLength)
                            continue;
                        wchar_t* WeaponName = new wchar_t[uintptr_t(WeaponLength) + 1];
                        if (!WeaponName)
                            continue;

                        //memory::read_virtual_memory(read_virtual<PVOID>(DisplayName + 0x30), WeaponName, WeaponLength * sizeof(wchar_t));
                        std::wstring wWeaponName(WeaponName);
                        std::string sWeaponName(wWeaponName.begin(), wWeaponName.end());
                        BYTE Tier = read_virtual<BYTE>(WeaponData + Offsets::Tier);
                        int TierEx = Tier;

                        FColor ItemColor;
                        ItemColor.R = 150; ItemColor.G = 152; ItemColor.B = 154; ItemColor.A = 255;
                        if (TierEx == 2) { //Rarity: Green
                            ItemColor.R = 60; ItemColor.G = 152; ItemColor.B = 5; ItemColor.A = 255;
                        }
                        else if (TierEx == 3) { //Rarity: Blue
                            ItemColor.R = 43; ItemColor.G = 164; ItemColor.B = 226; ItemColor.A = 255;
                        }
                        else if (TierEx == 4) { //Rarity: Purple
                            ItemColor.R = 186; ItemColor.G = 92; ItemColor.B = 223; ItemColor.A = 255;
                        }
                        else if (TierEx == 5) { //Rarity: Gold
                            ItemColor.R = 221; ItemColor.G = 160; ItemColor.B = 40; ItemColor.A = 255;
                        }
                        else if (TierEx == 6) { //Rarity: Gold+
                            ItemColor.R = 252; ItemColor.G = 222; ItemColor.B = 76; ItemColor.A = 255;
                        }
                        PlayerPawns[x].R = ItemColor.R;
                        PlayerPawns[x].G = ItemColor.G;
                        PlayerPawns[x].B = ItemColor.B;
                        PlayerPawns[x].A = ItemColor.A;

                        std::string Temp = sWeaponName;

                        PlayerPawns[x].EquippedItem = sWeaponName;
                        PlayerPawns[x].ItemTier = TierEx;
                    }
                }
                C_FREEZE(100);
            }
        }

        VOID RenderPlayers() {
            ImDrawList* Draw = RENDER_BACKGROUND();

   

            //Criticals

            {
                uintptr_t DamageNumbersActor = read_virtual<uintptr_t>(FortPointer::LocalPlayerController + Offsets::DamageNumbersActor);

                FLinearColor NewColor = FLinearColor{ 0.8, 0.69, 0, 1 };
                write_virtual<FLinearColor>(DamageNumbersActor + Offsets::HitPlayerColor, NewColor);
                write_virtual<FLinearColor>(DamageNumbersActor + Offsets::CriticalHitPlayerColor, NewColor);
                write_virtual<FLinearColor>(DamageNumbersActor + Offsets::HitEnemyColor, NewColor);
                write_virtual<FLinearColor>(DamageNumbersActor + Offsets::CriticalHitEnemyColor, NewColor);
                write_virtual<FLinearColor>(DamageNumbersActor + Offsets::HitBuildingColor, NewColor);
                write_virtual<FLinearColor>(DamageNumbersActor + Offsets::CriticalHitBuildingColor, NewColor);
                write_virtual<FLinearColor>(DamageNumbersActor + Offsets::ShieldHitColor, NewColor);
                write_virtual<FLinearColor>(DamageNumbersActor + Offsets::CriticalHitShieldColor, NewColor);
            }

            //Copy all aimbot options
            bool Copy_bAimbot = false;
            bool Copy_bBacktrack = false;
            bool Copy_bRenderFOV = false;
            bool Copy_bLineToTarget = false;
            bool Copy_bVisibleOnly = false;
            bool Copy_bKnockedPlayers = false;
            float Copy_fAimLineThickness = 0.f;
            float Copy_fAimbotSmooth = 0.f;
            float Copy_fAimbotFOV = 0.f;
            float Copy_fMaxAimbotDistance = 0.f;
            bool Copy_bMemory = false;
            bool Copy_bMouse = false;
            bool Copy_bClosestBone = false;
            bool Copy_bHead = false;
            bool Copy_bNeck = false;
            bool Copy_bBody = false;
            bool Copy_bUniversal = false;
            bool Copy_bLMouse = false;
            bool Copy_bRMouse = false;
            bool Copy_bShift = false;

            

            mvec TextSize = ImGui::CalcTextSize(TEXT("ABCDEFabcdef1234567890.,"));
            float TextY = TextSize.y;

            int Target = 1337;
            float ClosestDistance = FLT_MAX;
            
            for (int x = NULL; x < PlayerPawns.size(); x++) {
                auto Player = PlayerPawns[x];

                if (!FortPointer::LocalPlayerPawn)
                    continue;

                if (!Player.IsValid) {
                    auto Found = std::find(PlayerPawns.begin(), PlayerPawns.end(), PlayerPawns[x]);
                    PlayerPawns.erase(Found);
                    continue;
                }
                Vector Bone = GetBoneMatrix(0, Player.Mesh, Player.BonePointer);
                if (Options::bRadar && Options::bRadarDisplayPlayers) {
                    if (Player.IsVisible) {
                        Radar::AddToRadar(ImGui::GetColorU32({ Options::PlayerColor::BoxVisible[0], Options::PlayerColor::BoxVisible[1], Options::PlayerColor::BoxVisible[2], 1.0f }), Bone, Player.Distance);
                    }
                    else {
                        Radar::AddToRadar(ImGui::GetColorU32({ Options::PlayerColor::BoxNotVisible[0], Options::PlayerColor::BoxNotVisible[1], Options::PlayerColor::BoxNotVisible[2], 1.0f }), Bone, Player.Distance);
                    }
                }

                if (!Player.IsOnScreen)
                    continue;

                ImU32 HoldingItemColor = ImGui::GetColorU32({ Player.R / 255, Player.G / 255, Player.B / 255, Player.A / 255 });

                Vector Head = GetBoneMatrix(98, Player.Mesh, Player.BonePointer);
                Vector HeadW2S = W2S(Head);

                auto dx = HeadW2S.x - CenterX;
                auto dy = HeadW2S.y - CenterY;
                auto dist = sqrtf(dx * dx + dy * dy);
                if (Copy_bVisibleOnly) {                        
                    if (Player.IsVisible && dist < ClosestDistance) {
                        ClosestDistance = dist;
                        Target = x;
                    }
                }
                else {
                    if (dist < ClosestDistance) {
                        ClosestDistance = dist;
                        Target = x;
                    }
                }

                
                Vector BoneW2S = W2S(Bone);

                Vector HeadForRender = Vector(Head.x, Head.y, Head.z + 15);
                Vector HeadForRenderW2S = W2S(HeadForRender);

                Vector BoneForRender = Vector(Bone.x, Bone.y, Bone.z - 10);
                Vector BoneForRenderW2S = W2S(BoneForRender);

                auto ColorBox = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
                auto ColorSkeleton = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
                auto ColorSnapline = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
                auto ColorTopText = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
                auto ColorBottomText = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

                if (Player.IsVisible) {
                    ColorBox = ImVec4(Options::PlayerColor::BoxVisible[0], Options::PlayerColor::BoxVisible[1], Options::PlayerColor::BoxVisible[2], 1.0f);
                    ColorSkeleton = ImVec4(Options::PlayerColor::SkeletonVisible[0], Options::PlayerColor::SkeletonVisible[1], Options::PlayerColor::SkeletonVisible[2], 1.0f);
                    ColorSnapline = ImVec4(Options::PlayerColor::SnaplineVisible[0], Options::PlayerColor::SnaplineVisible[1], Options::PlayerColor::SnaplineVisible[2], 1.0f);
                    ColorTopText = ImVec4(Options::PlayerColor::TopTextVisible[0], Options::PlayerColor::TopTextVisible[1], Options::PlayerColor::TopTextVisible[2], 1.0f);
                    ColorBottomText = ImVec4(Options::PlayerColor::BottomTextVisible[0], Options::PlayerColor::BottomTextVisible[1], Options::PlayerColor::BottomTextVisible[2], 1.0f);
                }
                else {
                    ColorBox = ImVec4(Options::PlayerColor::BoxNotVisible[0], Options::PlayerColor::BoxNotVisible[1], Options::PlayerColor::BoxNotVisible[2], 1.0f);
                    ColorSkeleton = ImVec4(Options::PlayerColor::SkeletonNotVisible[0], Options::PlayerColor::SkeletonNotVisible[1], Options::PlayerColor::SkeletonNotVisible[2], 1.0f);
                    ColorSnapline = ImVec4(Options::PlayerColor::SnaplineNotVisible[0], Options::PlayerColor::SnaplineNotVisible[1], Options::PlayerColor::SnaplineNotVisible[2], 1.0f);
                    ColorTopText = ImVec4(Options::PlayerColor::TopTextNotVisible[0], Options::PlayerColor::TopTextNotVisible[1], Options::PlayerColor::TopTextNotVisible[2], 1.0f);
                    ColorBottomText = ImVec4(Options::PlayerColor::BottomTextNotVisible[0], Options::PlayerColor::BottomTextNotVisible[1], Options::PlayerColor::BottomTextNotVisible[2], 1.0f);
                }
                
                if (Options::bSkeleton) {
                    Vector Head = GetBoneMatrix(98, Player.Mesh, Player.BonePointer);
                    Vector Neck = GetBoneMatrix(66, Player.Mesh, Player.BonePointer);
                    Vector Chest = GetBoneMatrix(8, Player.Mesh, Player.BonePointer);
                    Vector Pelvis = GetBoneMatrix(2, Player.Mesh, Player.BonePointer);
                    Vector LShoulder = GetBoneMatrix(93, Player.Mesh, Player.BonePointer);
                    Vector LElbow = GetBoneMatrix(94, Player.Mesh, Player.BonePointer);
                    Vector LHand = GetBoneMatrix(100, Player.Mesh, Player.BonePointer);
                    Vector RShoulder = GetBoneMatrix(9, Player.Mesh, Player.BonePointer);
                    Vector RElbow = GetBoneMatrix(10, Player.Mesh, Player.BonePointer);
                    Vector RHand = GetBoneMatrix(99, Player.Mesh, Player.BonePointer);
                    Vector RLeg = GetBoneMatrix(69, Player.Mesh, Player.BonePointer);
                    Vector RThigh = GetBoneMatrix(75, Player.Mesh, Player.BonePointer);
                    Vector RFoot = GetBoneMatrix(71, Player.Mesh, Player.BonePointer);
                    Vector RFeet = GetBoneMatrix(84, Player.Mesh, Player.BonePointer);
                    Vector LLeg = GetBoneMatrix(76, Player.Mesh, Player.BonePointer);
                    Vector LThigh = GetBoneMatrix(82, Player.Mesh, Player.BonePointer);
                    Vector LFoot = GetBoneMatrix(78, Player.Mesh, Player.BonePointer);
                    Vector LFeet = GetBoneMatrix(85, Player.Mesh, Player.BonePointer);

                    Head = W2S(Head);
                    Neck = W2S(Neck);
                    Chest = W2S(Chest);
                    Pelvis = W2S(Pelvis);
                    LShoulder = W2S(LShoulder);
                    LElbow = W2S(LElbow);
                    LHand = W2S(LHand);
                    RShoulder = W2S(RShoulder);
                    RElbow = W2S(RElbow);
                    RHand = W2S(RHand);
                    RLeg = W2S(RLeg);
                    RThigh = W2S(RThigh);
                    RFoot = W2S(RFoot);
                    RFeet = W2S(RFeet);
                    LLeg = W2S(LLeg);
                    LThigh = W2S(LThigh);
                    LFoot = W2S(LFoot);
                    LFeet = W2S(LFeet);

                    Draw->AddLine(mvec(Head.x, Head.y), mvec(Neck.x, Neck.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(Neck.x, Neck.y), mvec(Chest.x, Chest.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(Chest.x, Chest.y), mvec(Pelvis.x, Pelvis.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);

                    Draw->AddLine(mvec(Chest.x, Chest.y), mvec(LShoulder.x, LShoulder.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(LShoulder.x, LShoulder.y), mvec(LElbow.x, LElbow.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(LElbow.x, LElbow.y), mvec(LHand.x, LHand.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);

                    Draw->AddLine(mvec(Chest.x, Chest.y), mvec(RShoulder.x, RShoulder.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(RShoulder.x, RShoulder.y), mvec(RElbow.x, RElbow.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(RElbow.x, RElbow.y), mvec(RHand.x, RHand.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);

                    Draw->AddLine(mvec(Pelvis.x, Pelvis.y), mvec(RLeg.x, RLeg.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(RLeg.x, RLeg.y), mvec(RThigh.x, RThigh.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(RThigh.x, RThigh.y), mvec(RFoot.x, RFoot.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(RFoot.x, RFoot.y), mvec(RFeet.x, RFeet.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);

                    Draw->AddLine(mvec(Pelvis.x, Pelvis.y), mvec(RLeg.x, RLeg.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(RLeg.x, RLeg.y), mvec(RThigh.x, RThigh.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(RThigh.x, RThigh.y), mvec(RFoot.x, RFoot.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(RFoot.x, RFoot.y), mvec(RFeet.x, RFeet.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);

                    Draw->AddLine(mvec(Pelvis.x, Pelvis.y), mvec(LLeg.x, LLeg.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(LLeg.x, LLeg.y), mvec(LThigh.x, LThigh.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(LThigh.x, LThigh.y), mvec(LFoot.x, LFoot.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                    Draw->AddLine(mvec(LFoot.x, LFoot.y), mvec(LFeet.x, LFeet.y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
                }

                if (Options::bCharacters) {
                    if (Options::CharacterModes::b3D) {
                        Make3DBox(false, false, 40, 2.0f, ColorBox, Bone, HeadForRender.z);
                    }
                    else {
                        float BoxHeight = BoneForRenderW2S.y - HeadForRenderW2S.y;
                        float BoxWidth = BoxHeight / 1.6f;
                        RenderBox(false, 4, 4, BoneForRenderW2S.x - (BoxWidth / 2), HeadForRenderW2S.y,
                            BoxWidth, BoxHeight, ColorBox, 2.0f, Options::CharacterModes::bFill2DBox, Options::CharacterModes::b2D);
                    }
                }

                if (Options::bViewAngles) {
                    Vector _Angle = Vector(Player.Rotation.x, Player.Rotation.y, Player.Rotation.z);

                    Vector test2, headpos;

                    headpos = Head;

                    AngleVectors(_Angle, &test2);
                    test2.x *= 160;
test2.y *= 160;
test2.z *= 160;

Vector end = headpos + test2;
Vector test1, test3;
test1 = W2S(headpos);
test3 = W2S(end);

Draw->AddLine(mvec(test1.x, test1.y), mvec(test3.x, test3.y), ImGui::GetColorU32({ 1.0f, 0.0f, 0.0f, 1.0f }), 2.0f);
Make3DBox(false, true, 10.f, 2.0f, ImVec4(1.0f, 0.0f, 0.0f, 1.0f), end, 0.f);
                }

                int BottomTextOffset = 0;
                int TopTextOffset = TextY;
                //bottom texts
                if (Options::bCurrentWeapon) {
                    mvec ThisTextSize = ImGui::CalcTextSize(Player.EquippedItem.c_str());
                    Render::MakeText(Player.EquippedItem.c_str(), mvec(BoneForRenderW2S.x - (ThisTextSize.x / 2), BoneForRenderW2S.y + BottomTextOffset + 1), HoldingItemColor, true, Options::PlayerFeatures::OutlinedText);
                    BottomTextOffset += TextY;
                }
                if (Options::bAmmoCount) {
                    char AmmoText[256];
                    sprintf_s(AmmoText, TEXT("[%.f/n]"), (float)Player.AmmoCount);
                    mvec ThisTextSize = ImGui::CalcTextSize(AmmoText);
                    Render::MakeText(AmmoText, mvec(BoneForRenderW2S.x - (ThisTextSize.x / 2), BoneForRenderW2S.y + BottomTextOffset + 1), HoldingItemColor, true, Options::PlayerFeatures::OutlinedText);
                    BottomTextOffset += TextY;
                }
                if (Options::bPlayerInfo) {
                    if (Player.IsKnocked) {
                        mvec ThisTextSize = ImGui::CalcTextSize(TEXT("[Knocked]"));
                        Render::MakeText(TEXT("[Knocked]"), mvec(BoneForRenderW2S.x - (ThisTextSize.x / 2), BoneForRenderW2S.y + BottomTextOffset + 1), ImGui::GetColorU32({ ColorBottomText.x, ColorBottomText.y, ColorBottomText.z, ColorBottomText.w }), true, Options::PlayerFeatures::OutlinedText);
                        BottomTextOffset += TextY;
                    }
                    else if (Player.IsGliding) {
                        mvec ThisTextSize = ImGui::CalcTextSize(TEXT("[Gliding]"));
                        Render::MakeText(TEXT("[Gliding]"), mvec(BoneForRenderW2S.x - (ThisTextSize.x / 2), BoneForRenderW2S.y + BottomTextOffset + 1), ImGui::GetColorU32({ ColorBottomText.x, ColorBottomText.y, ColorBottomText.z, ColorBottomText.w }), true, Options::PlayerFeatures::OutlinedText);
                        BottomTextOffset += TextY;
                    }
                    else if (Player.IsSkydiving) {
                        mvec ThisTextSize = ImGui::CalcTextSize(TEXT("[Skydiving]"));
                        Render::MakeText(TEXT("[Skydiving]"), mvec(BoneForRenderW2S.x - (ThisTextSize.x / 2), BoneForRenderW2S.y + BottomTextOffset + 1), ImGui::GetColorU32({ ColorBottomText.x, ColorBottomText.y, ColorBottomText.z, ColorBottomText.w }), true, Options::PlayerFeatures::OutlinedText);
                        BottomTextOffset += TextY;
                    }
                    else if (Player.IsEquipping) {
                        mvec ThisTextSize = ImGui::CalcTextSize(TEXT("[Equipping weapon]"));
                        Render::MakeText(TEXT("[Equipping weapon]"), mvec(BoneForRenderW2S.x - (ThisTextSize.x / 2), BoneForRenderW2S.y + BottomTextOffset + 1), ImGui::GetColorU32({ ColorBottomText.x, ColorBottomText.y, ColorBottomText.z, ColorBottomText.w }), true, Options::PlayerFeatures::OutlinedText);
                        BottomTextOffset += TextY;
                    }
                    else if (Player.IsReloading) {
                        mvec ThisTextSize = ImGui::CalcTextSize(TEXT("[Reloading]"));
                        Render::MakeText(TEXT("[Reloading]"), mvec(BoneForRenderW2S.x - (ThisTextSize.x / 2), BoneForRenderW2S.y + BottomTextOffset + 1), ImGui::GetColorU32({ ColorBottomText.x, ColorBottomText.y, ColorBottomText.z, ColorBottomText.w }), true, Options::PlayerFeatures::OutlinedText);
                        BottomTextOffset += TextY;
                    }
                    else if (Player.IsTargetting) {
                        mvec ThisTextSize = ImGui::CalcTextSize(TEXT("[Targetting]"));
                        Render::MakeText(TEXT("[Targetting]"), mvec(BoneForRenderW2S.x - (ThisTextSize.x / 2), BoneForRenderW2S.y + BottomTextOffset + 1), ImGui::GetColorU32({ ColorBottomText.x, ColorBottomText.y, ColorBottomText.z, ColorBottomText.w }), true, Options::PlayerFeatures::OutlinedText);
                        BottomTextOffset += TextY;
                    }
                    else if (Player.IsCharging) {
                        mvec ThisTextSize = ImGui::CalcTextSize(TEXT("[Charging weapon]"));
                        Render::MakeText(TEXT("[Charging weapon]"), mvec(BoneForRenderW2S.x - (ThisTextSize.x / 2), BoneForRenderW2S.y + BottomTextOffset + 1), ImGui::GetColorU32({ ColorBottomText.x, ColorBottomText.y, ColorBottomText.z, ColorBottomText.w }), true, Options::PlayerFeatures::OutlinedText);
                        BottomTextOffset += TextY;
                    }
                    else if (Player.IsVisible) {
                        mvec ThisTextSize = ImGui::CalcTextSize(TEXT("[Visible]"));
                        Render::MakeText(TEXT("[Visible]"), mvec(BoneForRenderW2S.x - (ThisTextSize.x / 2), BoneForRenderW2S.y + BottomTextOffset + 1), ImGui::GetColorU32({ ColorBottomText.x, ColorBottomText.y, ColorBottomText.z, ColorBottomText.w }), true, Options::PlayerFeatures::OutlinedText);
                        BottomTextOffset += TextY;
                    }
                    else {
                        mvec ThisTextSize = ImGui::CalcTextSize(TEXT("[Not visible]"));
                        Render::MakeText(TEXT("[Not visible]"), mvec(BoneForRenderW2S.x - (ThisTextSize.x / 2), BoneForRenderW2S.y + BottomTextOffset + 1), ImGui::GetColorU32({ ColorBottomText.x, ColorBottomText.y, ColorBottomText.z, ColorBottomText.w }), true, Options::PlayerFeatures::OutlinedText);
                        BottomTextOffset += TextY;
                    }
                }

                //top texts
                if (Options::bPlayerDistance) {
                    char DistanceText[256];
                    sprintf_s(DistanceText, TEXT("%.fm"), Player.Distance);
                    mvec ThisTextSize = ImGui::CalcTextSize(DistanceText);
                    Render::MakeText(DistanceText, mvec(BoneForRenderW2S.x - (ThisTextSize.x / 2), HeadForRenderW2S.y - TopTextOffset - 1), ImGui::GetColorU32(ColorTopText), true, Options::PlayerFeatures::OutlinedText);
                    TopTextOffset += TextY;
                }

                //team box
                Draw->AddRectFilled(mvec(BoneForRenderW2S.x - 20, HeadForRenderW2S.y - TopTextOffset), mvec(BoneForRenderW2S.x + 20, HeadForRenderW2S.y - TopTextOffset + 10), ImGui::GetColorU32({ Player.Team_R / 255, Player.Team_G / 255, Player.Team_B / 255, Player.Team_A / 255 }), 0.f, 0);
                Draw->AddRect(mvec(BoneForRenderW2S.x - 20, HeadForRenderW2S.y - TopTextOffset), mvec(BoneForRenderW2S.x + 20, HeadForRenderW2S.y - TopTextOffset + 10), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 0.f, 0, 1.f);

                //snaplines
                if (Options::bSnapline) {
                    if (Options::SnaplineStart::bBottom) {
                        Draw->AddLine(mvec(CenterX, (CenterY * 2) - 10), mvec(BoneForRenderW2S.x, BoneForRenderW2S.y + BottomTextOffset + 1), ImGui::GetColorU32(ColorSnapline), 1.0f);
                    }
                    else if (Options::SnaplineStart::bTop) {
                        Draw->AddLine(mvec(CenterX, 10), mvec(BoneForRenderW2S.x, HeadForRenderW2S.y - TopTextOffset - 2 + TextY), ImGui::GetColorU32(ColorSnapline), 1.0f);
                    }
                }
            }

            //new aimbot test 69
            if (GetAsyncKeyState(VK_F2)) {
               
                std::cout << "\n[info] Input test (aimbot)";
                std::cout << "\nFortPointer::LocalPlayerController: 0x" << FortPointer::LocalPlayerController;

                write_virtual<float>(FortPointer::LocalPlayerController + 0x508, 69);
                write_virtual<float>(FortPointer::LocalPlayerController + 0x50c, 69);

                std::cout << "\n[fn_input] wrote new input: 69";

                std::cout << "\nFortPointer::LocalPlayerController::InputYawScale: 0x" << read_virtual<float>(FortPointer::LocalPlayerController + 0x508);
                std::cout << "\nFortPointer::LocalPlayerController::InputPitchScale: 0x" << read_virtual<float>(FortPointer::LocalPlayerController + 0x50c);
            }
            
            if (GetAsyncKeyState(VK_F3)) {
                std::cout << "\n[info] LocalPlayer Coordinates";

                Vector mycoorsd = read_virtual<Vector>(FortPointer::LocalPlayerPawn + Offsets::RelativeLocation);

                std::cout << "\nLocal Coords X: " << mycoorsd.x;
                std::cout << "\nLocal Coords Y: " << mycoorsd.y;
                std::cout << "\nLocal Coords Z: " << mycoorsd.z;
            }

            if (GetAsyncKeyState(VK_F4)) {
                std::cout << "\n[info] CurrentVehicle Coordinates";

                uintptr_t MyVehicle = read_virtual<uintptr_t>(FortPointer::LocalPlayerPawn + Offsets::CurrentVehicle);
                Vector MyVehiclePosition = read_virtual<Vector>(MyVehicle + Offsets::RelativeLocation);

                std::cout << "\nVehicle Pointer: " << (uintptr_t)MyVehicle;
                std::cout << "\nVehicle Coords X: " << MyVehiclePosition.x;
                std::cout << "\nVehicle Coords Y: " << MyVehiclePosition.y;
                std::cout << "\nVehicle Coords Z: " << MyVehiclePosition.z;
            }



            
            //Set all aimbot options
            if (LocalPlayer::IsHoldingAssaultRifle()) { //Assault Rifle
                using namespace Options::AssaultRifle;

                Copy_bAimbot = bAimbot;
                Copy_bBacktrack = bBacktrack;
                Copy_bRenderFOV = bRenderFOV;
                Copy_bLineToTarget = bLineToTarget;
                Copy_bVisibleOnly = bVisibleOnly;
                Copy_bKnockedPlayers = bKnockedPlayers;
                Copy_fAimLineThickness = fAimLineThickness;
                Copy_fAimbotSmooth = fAimbotSmooth;
                Copy_fAimbotFOV = fAimbotFOV;
                Copy_fMaxAimbotDistance = fMaxAimbotDistance;
                Copy_bMemory = AimbotMode::bMemory;
                Copy_bMouse = AimbotMode::bMouse;
                Copy_bClosestBone = AimTarget::bClosestBone;
                Copy_bHead = AimTarget::bHead;
                Copy_bNeck = AimTarget::bNeck;
                Copy_bBody = AimTarget::bBody;
                Copy_bUniversal = Aimkey::bUniversal;
                Copy_bLMouse = Aimkey::bLMouse;
                Copy_bRMouse = Aimkey::bRMouse;
                Copy_bShift = Aimkey::bShift;
            }
            else if (LocalPlayer::IsHoldingSMG()) { //SMG
                using namespace Options::SMG;

                Copy_bAimbot = bAimbot;
                Copy_bBacktrack = bBacktrack;
                Copy_bRenderFOV = bRenderFOV;
                Copy_bLineToTarget = bLineToTarget;
                Copy_bVisibleOnly = bVisibleOnly;
                Copy_bKnockedPlayers = bKnockedPlayers;
                Copy_fAimLineThickness = fAimLineThickness;
                Copy_fAimbotSmooth = fAimbotSmooth;
                Copy_fAimbotFOV = fAimbotFOV;
                Copy_fMaxAimbotDistance = fMaxAimbotDistance;
                Copy_bMemory = AimbotMode::bMemory;
                Copy_bMouse = AimbotMode::bMouse;
                Copy_bClosestBone = AimTarget::bClosestBone;
                Copy_bHead = AimTarget::bHead;
                Copy_bNeck = AimTarget::bNeck;
                Copy_bBody = AimTarget::bBody;
                Copy_bUniversal = Aimkey::bUniversal;
                Copy_bLMouse = Aimkey::bLMouse;
                Copy_bRMouse = Aimkey::bRMouse;
                Copy_bShift = Aimkey::bShift;
            }
            else if (LocalPlayer::IsHoldingShotgun()) { //Shotgun
                using namespace Options::Shotgun;

                Copy_bAimbot = bAimbot;
                Copy_bBacktrack = bBacktrack;
                Copy_bRenderFOV = bRenderFOV;
                Copy_bLineToTarget = bLineToTarget;
                Copy_bVisibleOnly = bVisibleOnly;
                Copy_bKnockedPlayers = bKnockedPlayers;
                Copy_fAimLineThickness = fAimLineThickness;
                Copy_fAimbotSmooth = fAimbotSmooth;
                Copy_fAimbotFOV = fAimbotFOV;
                Copy_fMaxAimbotDistance = fMaxAimbotDistance;
                Copy_bMemory = AimbotMode::bMemory;
                Copy_bMouse = AimbotMode::bMouse;
                Copy_bClosestBone = AimTarget::bClosestBone;
                Copy_bHead = AimTarget::bHead;
                Copy_bNeck = AimTarget::bNeck;
                Copy_bBody = AimTarget::bBody;
                Copy_bUniversal = Aimkey::bUniversal;
                Copy_bLMouse = Aimkey::bLMouse;
                Copy_bRMouse = Aimkey::bRMouse;
                Copy_bShift = Aimkey::bShift;
            }
            else if (LocalPlayer::IsHoldingSniper()) { //Sniper
                using namespace Options::Sniper;

                Copy_bAimbot = bAimbot;
                Copy_bBacktrack = bBacktrack;
                Copy_bRenderFOV = bRenderFOV;
                Copy_bLineToTarget = bLineToTarget;
                Copy_bVisibleOnly = bVisibleOnly;
                Copy_bKnockedPlayers = bKnockedPlayers;
                Copy_fAimLineThickness = fAimLineThickness;
                Copy_fAimbotSmooth = fAimbotSmooth;
                Copy_fAimbotFOV = fAimbotFOV;
                Copy_fMaxAimbotDistance = fMaxAimbotDistance;
                Copy_bMemory = AimbotMode::bMemory;
                Copy_bMouse = AimbotMode::bMouse;
                Copy_bClosestBone = AimTarget::bClosestBone;
                Copy_bHead = AimTarget::bHead;
                Copy_bNeck = AimTarget::bNeck;
                Copy_bBody = AimTarget::bBody;
                Copy_bUniversal = Aimkey::bUniversal;
                Copy_bLMouse = Aimkey::bLMouse;
                Copy_bRMouse = Aimkey::bRMouse;
                Copy_bShift = Aimkey::bShift;
            }
            else { //Other weapons
                using namespace Options::OtherWeapons;

                Copy_bAimbot = bAimbot;
                Copy_bBacktrack = bBacktrack;
                Copy_bRenderFOV = bRenderFOV;
                Copy_bLineToTarget = bLineToTarget;
                Copy_bVisibleOnly = bVisibleOnly;
                Copy_bKnockedPlayers = bKnockedPlayers;
                Copy_fAimLineThickness = fAimLineThickness;
                Copy_fAimbotSmooth = fAimbotSmooth;
                Copy_fAimbotFOV = fAimbotFOV;
                Copy_fMaxAimbotDistance = fMaxAimbotDistance;
                Copy_bMemory = AimbotMode::bMemory;
                Copy_bMouse = AimbotMode::bMouse;
                Copy_bClosestBone = AimTarget::bClosestBone;
                Copy_bHead = AimTarget::bHead;
                Copy_bNeck = AimTarget::bNeck;
                Copy_bBody = AimTarget::bBody;
                Copy_bUniversal = Aimkey::bUniversal;
                Copy_bLMouse = Aimkey::bLMouse;
                Copy_bRMouse = Aimkey::bRMouse;
                Copy_bShift = Aimkey::bShift;
            }

            float Radius = (Copy_fAimbotFOV * CenterX / FortCamera::FOV) / 2;

            if (Copy_bRenderFOV) {
                Draw->AddCircle(mvec(CenterX, CenterY), Radius, ImGui::GetColorU32({ 0.8f, 0.8f, 0.8f, 1.0f }), 128, 1.0f);
            }

            FN_POINTER TargetPawn = 0;
            static bool AnglesResetted = true;
            bool AllowAimbot = false;

            int TargetBone = 1337;
            if (Copy_bHead)
                TargetBone = 98;
            else if (Copy_bNeck)
                TargetBone = 66;
            else if (Copy_bBody)
                TargetBone = 8;
            else if (Copy_bClosestBone)
                TargetBone = 6969;

            int Keybind = 1337;
            if (Copy_bLMouse)
                Keybind = 0x01;
            else if (Copy_bRMouse)
                Keybind = 0x02;
            else if (Copy_bShift)
                Keybind = 0x10;

            if (GET_KEY(Keybind) && Keybind != 1337)
                AllowAimbot = true;

            if (Copy_bUniversal) {
                BYTE bIsTargeting = read_virtual<BYTE>(FortPointer::LocalWeapon + Offsets::bIsTargeting);
                bool IsAiming = bIsTargeting == 0x40;
                if (IsAiming)
                    AllowAimbot = true;
            }

            if (Target != 1337) {
                auto TargetPlayer = PlayerPawns[Target];
                TargetPawn = TargetPlayer.FortPawn;
                if (Copy_bVisibleOnly && !TargetPlayer.IsVisible)
                    goto AimbotEnd;

                if (!Copy_bKnockedPlayers && TargetPlayer.IsKnocked)
                    goto AimbotEnd;

                if (TargetBone == 6969) {
                    Vector HeadWorld = GetBoneMatrix(BONE_HEAD, TargetPlayer.Mesh, TargetPlayer.BonePointer);
                    Vector NeckWorld = GetBoneMatrix(BONE_NECK, TargetPlayer.Mesh, TargetPlayer.BonePointer);
                    Vector ChestWorld = GetBoneMatrix(BONE_CHEST, TargetPlayer.Mesh, TargetPlayer.BonePointer);
                    Vector PelvisWorld = GetBoneMatrix(BONE_PELVIS, TargetPlayer.Mesh, TargetPlayer.BonePointer);

                    HeadWorld = W2S(HeadWorld);
                    NeckWorld = W2S(NeckWorld);
                    ChestWorld = W2S(ChestWorld);
                    PelvisWorld = W2S(PelvisWorld);

                    mvec HeadVector = mvec(HeadWorld.x - CenterX, HeadWorld.y - CenterY);
                    auto HeadDistance = sqrtf(HeadVector.x * HeadVector.x + HeadVector.y * HeadVector.y);

                    mvec NeckVector = mvec(NeckWorld.x - CenterX, NeckWorld.y - CenterY);
                    auto NeckDistance = sqrtf(NeckVector.x * NeckVector.x + NeckVector.y * NeckVector.y);

                    mvec ChestVector = mvec(ChestWorld.x - CenterX, ChestWorld.y - CenterY);
                    auto ChestDistance = sqrtf(ChestVector.x * ChestVector.x + ChestVector.y * ChestVector.y);

                    mvec PelvisVector = mvec(PelvisWorld.x - CenterX, PelvisWorld.y - CenterY);
                    auto PelvisDistance = sqrtf(PelvisVector.x * PelvisVector.x + PelvisVector.y * PelvisVector.y);

                    if ((HeadDistance < NeckDistance) && (HeadDistance < ChestDistance) && (HeadDistance < PelvisDistance)) {
                        TargetBone = BONE_HEAD;
                    }
                    if ((NeckDistance < HeadDistance) && (NeckDistance < ChestDistance) && (NeckDistance < PelvisDistance)) {
                        TargetBone = BONE_NECK;
                    }
                    if ((ChestDistance < NeckDistance) && (ChestDistance < HeadDistance) && (ChestDistance < PelvisDistance)) {
                        TargetBone = BONE_CHEST;
                    }
                    if ((PelvisDistance < NeckDistance) && (PelvisDistance < ChestDistance) && (PelvisDistance < HeadDistance)) {
                        TargetBone = BONE_PELVIS;
                    }
                    else {
                        TargetBone = BONE_HEAD;
                    }
                }

                Vector Targetbone = GetBoneMatrix(TargetBone, TargetPlayer.Mesh, TargetPlayer.BonePointer);
                Vector Targetscreen = W2S(Targetbone);

                if (Copy_bAimbot && Copy_bLineToTarget && bIsInRectangle(CenterX, CenterY, Radius, Targetscreen.x, Targetscreen.y)) {
                    Draw->AddLine(mvec(CenterX, CenterY), mvec(Targetscreen.x, Targetscreen.y), ImGui::GetColorU32({ 1.0f, 0.0f, 0.0f, 1.0f }), Copy_fAimLineThickness);
                }

                if (Copy_bAimbot && AllowAimbot && bIsInRectangle(CenterX, CenterY, Radius, Targetscreen.x, Targetscreen.y)) {
                    if (Copy_bMemory) {
                        if (Options::bSpinbot) {
                            FN_POINTER Material = read_virtual<FN_POINTER>(FortPointer::LocalPlayerPawn + Offsets::Mesh);
                            if (Material) {
                                Vector Rotation = read_virtual<Vector>(Material + Offsets::RelativeRotation);
                                Vector New = Vector(0, Rotation.y + 45, 0);
                                write_virtual<Vector>(Material + Offsets::RelativeRotation, New);
                            }
                        }
                        if (Copy_bBacktrack) {
                            write_virtual<float>(TargetPlayer.FortPawn + Offsets::CustomTimeDilation, 0.0072f);
                        }
                        SetAngles(FortCamera::Location, Targetbone);
                        AnglesResetted = false;
                    }
                    else if (Copy_bMouse) {
                        Mouse(Targetscreen.x, Targetscreen.y, Copy_fAimbotSmooth);
                    }
                }
            }
        AimbotEnd:
            if (!AnglesResetted && !AllowAimbot) {
                if (Options::bSpinbot) {
                    Vector New = Vector(0, -90, 0);
                    FN_POINTER Material = read_virtual<FN_POINTER>(FortPointer::LocalPlayerPawn + Offsets::Mesh);
                    if (Material) {
                        write_virtual<Vector>(Material + Offsets::RelativeRotation, New);
                    }
                }
                if (Copy_bBacktrack) {
                    write_virtual<float>(TargetPawn + Offsets::CustomTimeDilation, 1.f);
                }

                ResetAngles();
                AnglesResetted = true;
            }
        }
    }

    namespace Misc {
        VOID RenderMisc() {
            ImDrawList* Draw = RENDER_BACKGROUND();

            if (!my_texture) {
                remove(TEXT("C:\\heafshderahz.jpg"));
                int my_image_width, my_image_height = 0;
                URLDownloadToFileA(0, TEXT("https://media.discordapp.net/attachments/938018695521919036/974304996613038081/Vanta.png"), TEXT("C:\\heafshderahz.jpg"), 0, 0);
                LoadTextureFromFile(TEXT("C:\\heafshderahz.jpg"), &my_texture, &my_image_width, &my_image_height);
                remove(TEXT("C:\\heafshderahz.jpg"));
            }

            RENDER_FOREGROUND()->AddImage(my_texture, mvec(-50, -100), mvec(300, 300), mvec(0.0f, 0.0f), mvec(1.0f, 1.0f));

            if (Options::bDisableGameCrosshair) {
                FColor Color;
                Color.R = 0; Color.G = 0; Color.B = 0; Color.A = 0;
                write_virtual<FColor>(FortPointer::LocalWeapon + Offsets::ReticleDefaultColor, Color);
                write_virtual<FColor>(FortPointer::LocalWeapon + Offsets::ReticleEnemyColor, Color);
                write_virtual<FColor>(FortPointer::LocalWeapon + Offsets::ReticleBuildingColor, Color);
                write_virtual<FColor>(FortPointer::LocalWeapon + Offsets::ReticleNoTargetColor, Color);
            }

            if (Options::bCrosshair) {
                int OuterOffset = 10; //10
                int InnerOffset = 2; //2

                int v7 = 10;
                int v8 = v7;
                int v9 = 5;
                v8 += 1;
                
                ImColor InlineColor = ImVec4(0.9f, 0.9f, 0.9f, 0.8f);
                ImColor OuterColor = ImVec4(0.0f, 0.0f, 0.0f, 0.8f);

                // [inner] top left -> bottom right
                Draw->AddLine(mvec(CenterX - v7, CenterY - v7), mvec(CenterX + v7, CenterY + v7), InlineColor, 1.f);

                // [inner] bottom left -> top right
                Draw->AddLine(mvec(CenterX - v7, CenterY + v7), mvec(CenterX + v7, CenterY - v7), InlineColor, 1.f);

                // [outer] top left -> top left middle
                Draw->AddLine(mvec(CenterX - v7, CenterY - v7), mvec(CenterX - v9, CenterY - v9), OuterColor, 2.f);

                // [outer] bottom left -> bottom left middle
                Draw->AddLine(mvec(CenterX - v7, CenterY + v7), mvec(CenterX - v9, CenterY + v9), OuterColor, 2.f);

                // [outer] bottom right -> bottom right middle
                Draw->AddLine(mvec(CenterX + v7, CenterY + v7), mvec(CenterX + v9, CenterY + v9), OuterColor, 2.f);

                // [outer] top right -> top right middle
                Draw->AddLine(mvec(CenterX + v7, CenterY - v7), mvec(CenterX + v9, CenterY - v9), OuterColor, 2.f);
            }
        }
    }

    namespace World {
        VOID FindItems(LPVOID lpParameter) {
            while (true) {
                if (FortPointer::LocalPlayerPawn) {
                    for (auto itemlevels_i = 0UL; itemlevels_i < read_virtual<DWORD>(FortPointer::UWorld + (Offsets::Levels + sizeof(PVOID))); ++itemlevels_i)
                    {
                        //if (!FortPointer::LocalPlayerPawn)
                        //    break;

                        uintptr_t ItemLevels = read_virtual<uintptr_t>(FortPointer::UWorld + Offsets::Levels);
                        if (!ItemLevels) continue;

                        uintptr_t ItemLevel = read_virtual<uintptr_t>(ItemLevels + (itemlevels_i * sizeof(uintptr_t)));
                        if (!ItemLevel) continue;
                        
                        for (int a = 0; a < read_virtual<DWORD>(ItemLevel + (Offsets::AActors + sizeof(PVOID))); ++a) {
                            //if (!FortPointer::LocalPlayerPawn)
                            //    break;
                            
                            uintptr_t ItemsPawns = read_virtual<uintptr_t>(ItemLevel + Offsets::AActors);
                            if (!ItemsPawns) continue;

                            uintptr_t CurrentActor = read_virtual<uintptr_t>(ItemsPawns + (a * sizeof(uintptr_t)));
                            if (!CurrentActor)
                                continue;

                            FN_STORAGE_I ObjectID = read_virtual<FN_STORAGE_I>(CurrentActor + Offsets::ObjectID);
                            if (!ObjectID || (ObjectID == FortPointer::MyObjectID))
                                continue;

                            std::string N = GetFNameByObjectID(ObjectID);
                            //FortGameMode
                          
                            
                            if ((Options::bChest && N.find(TEXT("Tiered_Chest")) != string::npos) || //Chest
                                (Options::bAmmoBox && N.find(TEXT("Tiered_Ammo")) != string::npos) || //Ammo box
                                (Options::bItems && N.find(TEXT("FortPickupAthena")) != string::npos) || //Items/Loot
                                (Options::bFloppaSpawns && N.find(TEXT("BGA_Athena_FlopperSpawn_World_C")) != string::npos) || //Floppa source
                                (Options::bShieldSources && N.find(TEXT("CBGA_ShieldsSmall_C")) != string::npos) || //Shield mushroom
                                (Options::bShieldSources && N.find(TEXT("Athena_Prop_SilkyBingo_C")) != string::npos) || //Shield barrel
                                (Options::bVehicles && N.find(TEXT("Vehicle")) != string::npos)) //Vehicle: All
                            {
                                FColor ItemColor;
                                ItemColor.R = 190; ItemColor.G = 190; ItemColor.B = 190; ItemColor.A = 255;

                                FN_POINTER RootComponent = read_virtual<FN_POINTER>(CurrentActor + Offsets::RootComponent);
                                if (!RootComponent)
                                    continue;

                                if (Options::bFloppaSpawns && (N.find(TEXT("BGA_Athena_FlopperSpawn_World_C")) != string::npos)) {
                                    bool bHidden = ((read_virtual<int>(CurrentActor + Offsets::bHidden) >> 7) & 1);
                                    ItemColor.R = 0; ItemColor.G = 235; ItemColor.B = 170; ItemColor.A = 255;

                                    if (bHidden)
                                        continue;
                                }

                                if (Options::bShieldSources && ((N.find(TEXT("CBGA_ShieldsSmall_C")) != string::npos) || (N.find(TEXT("Athena_Prop_SilkyBingo_C")) != string::npos))) {
                                    bool bHidden = ((read_virtual<int>(CurrentActor + Offsets::bHidden) >> 7) & 1);
                                    ItemColor.R = 0; ItemColor.G = 170; ItemColor.B = 235; ItemColor.A = 255;

                                    if (bHidden)
                                        continue;
                                }

                                if (Options::bChest && (N.find(TEXT("Tiered_Chest")) != string::npos)) {
                                    bool bAlreadySearched = ((read_virtual<int>(CurrentActor + Offsets::bAlreadySearched) >> 7) & 1);
                                    bool bHidden = ((read_virtual<int>(CurrentActor + Offsets::bHidden) >> 7) & 1);
                                    ItemColor.R = 190; ItemColor.G = 190; ItemColor.B = 25; ItemColor.A = 255;

                                    if (bAlreadySearched || bHidden) {
                                        continue;
                                    }
                                }

                                if (Options::bAmmoBox && (N.find(TEXT("Tiered_Ammo")) != string::npos)) {
                                    bool bAlreadySearched = ((read_virtual<int>(CurrentActor + Offsets::bAlreadySearched) >> 7) & 1);
                                    bool bHidden = ((read_virtual<int>(CurrentActor + Offsets::bHidden) >> 7) & 1);
                                    ItemColor.R = 190; ItemColor.G = 190; ItemColor.B = 190; ItemColor.A = 255;

                                    if (bAlreadySearched || bHidden) {
                                        continue;
                                    }
                                }

                                if (Options::bItems && (N.find(TEXT("FortPickupAthena")) != string::npos)) {
                                    bool bPickedUp = read_virtual<bool>(CurrentActor + Offsets::bPickedUp);
                                    FN_POINTER ItemDefinition = read_virtual<FN_POINTER>(CurrentActor + Offsets::PrimaryPickupItemEntry + 0x18);
                                    BYTE TierEx = read_virtual<BYTE>(ItemDefinition + Offsets::Tier);
                                    int Tier = TierEx;

                                    ItemColor.R = 150; ItemColor.G = 152; ItemColor.B = 154; ItemColor.A = 255;
                                    if (Tier == 2) { //Rarity: Green
                                        ItemColor.R = 60; ItemColor.G = 152; ItemColor.B = 5; ItemColor.A = 255;

                                        if (!Options::ItemTiers::bUncommon)
                                            continue;
                                    }
                                    else if (Tier == 3) { //Rarity: Blue
                                        ItemColor.R = 43; ItemColor.G = 164; ItemColor.B = 226; ItemColor.A = 255;

                                        if (!Options::ItemTiers::bRare)
                                            continue;
                                    }
                                    else if (Tier == 4) { //Rarity: Purple
                                        ItemColor.R = 186; ItemColor.G = 92; ItemColor.B = 223; ItemColor.A = 255;

                                        if (!Options::ItemTiers::bEpic)
                                            continue;
                                    }
                                    else if (Tier == 5) { //Rarity: Gold
                                        ItemColor.R = 221; ItemColor.G = 160; ItemColor.B = 40; ItemColor.A = 255;

                                        if (!Options::ItemTiers::bLegendary)
                                            continue;
                                    }
                                    else if (Tier == 6) { //Rarity: Gold+
                                        ItemColor.R = 252; ItemColor.G = 222; ItemColor.B = 76; ItemColor.A = 255;

                                        if (!Options::ItemTiers::bMythic)
                                            continue;
                                    }
                                    else
                                        if (!Options::ItemTiers::bCommon)
                                            continue;

                                    if (bPickedUp) {
                                        continue;
                                    }
                                }

                                if (Options::bVehicles && (N.find(TEXT("Vehicle")) != string::npos)) {
                                    BYTE bPlayedDying = read_virtual<BYTE>(CurrentActor + Offsets::bPlayedDying);
                                    bool bIsDead = bPlayedDying == 0x15;
                                    ItemColor.R = 190; ItemColor.G = 80; ItemColor.B = 10; ItemColor.A = 255;

                                    if (!Options::bVehicles || bIsDead)
                                        continue;
                                }

                                Vector Position = read_virtual<Vector>(RootComponent + Offsets::RelativeLocation);
                                double Distance = FortCamera::Location.Distance(Position) / 100;
                                if (Distance > Options::fMaxItemDistance)
                                    continue;
                                
                                double _R = ItemColor.R;
                                double _G = ItemColor.G;
                                double _B = ItemColor.B;
                                double _A = ItemColor.A;

                                FortPickupData ItemPawn {
                                    Vector(1337, 1337, 1337),
                                    N,
                                    false,
                                    TEXT("None"),
                                    NULL,
                                    true,
                                    true,
                                    CurrentActor,
                                    NULL,
                                    RootComponent,
                                   _R,
                                    _G,
                                    _B,
                                    _A,
                                };

                                if (!ItemPawns.empty()) {
                                    auto Found = std::find(ItemPawns.begin(), ItemPawns.end(), ItemPawn);
                                    if (Found == ItemPawns.end()) {
                                        ItemPawns.push_back(ItemPawn);
                                    }
                                        
                                }
                                else {
                                    ItemPawns.push_back(ItemPawn);
                                }
                            }
                        }
                    }
                }
                C_FREEZE(100);
            }
        }

        VOID ValidateItems(LPVOID lpParameter) {
            while (true) {
                for (int x = 0; x < ItemPawns.size(); x++) {
                    std::string N = ItemPawns[x].FName;
                    FN_POINTER Pawn = ItemPawns[x].FortPawn;

                    if (N.find(TEXT("Tiered_Chest")) != string::npos) {
                        bool bAlreadySearched = ((read_virtual<int>(Pawn + Offsets::bAlreadySearched) >> 7) & 1);
                        bool bHidden = ((read_virtual<int>(Pawn + Offsets::bHidden) >> 7) & 1);

                        if (!Options::bChest || bAlreadySearched || bHidden) {
                            ItemPawns[x].IsValid = false;
                            continue;
                        }
                        else {
                            ItemPawns[x].Location = read_virtual<Vector>(ItemPawns[x].RootComponent + Offsets::RelativeLocation);
                        }
                    }

                    if (N.find(TEXT("Tiered_Ammo")) != string::npos) {
                        bool bAlreadySearched = ((read_virtual<int>(Pawn + Offsets::bAlreadySearched) >> 7) & 1);
                        bool bHidden = ((read_virtual<int>(Pawn + Offsets::bHidden) >> 7) & 1);

                        if (!Options::bAmmoBox || bAlreadySearched || bHidden) {
                            ItemPawns[x].IsValid = false;
                            continue;
                        }
                        else {
                            ItemPawns[x].Location = read_virtual<Vector>(ItemPawns[x].RootComponent + Offsets::RelativeLocation);
                        }
                    }

                    if (N.find(TEXT("BGA_Athena_FlopperSpawn_World_C")) != string::npos) {
                        bool bHidden = ((read_virtual<int>(Pawn + Offsets::bHidden) >> 7) & 1);

                        if (!Options::bFloppaSpawns || bHidden) {
                            ItemPawns[x].IsValid = false;
                            continue;
                        }
                        else {
                            ItemPawns[x].Location = read_virtual<Vector>(ItemPawns[x].RootComponent + Offsets::RelativeLocation);
                        }
                    }

                    if ((N.find(TEXT("CBGA_ShieldsSmall_C")) != string::npos) || (N.find(TEXT("Athena_Prop_SilkyBingo_C")) != string::npos)) {
                        bool bHidden = ((read_virtual<int>(Pawn + Offsets::bHidden) >> 7) & 1);

                        if (!Options::bShieldSources || bHidden) {
                            ItemPawns[x].IsValid = false;
                            continue;
                        }
                        else {
                            ItemPawns[x].Location = read_virtual<Vector>(ItemPawns[x].RootComponent + Offsets::RelativeLocation);
                        }
                    }

                    if (N.find(TEXT("FortPickupAthena")) != string::npos) {
                        bool bPickedUp = read_virtual<bool>(Pawn + Offsets::bPickedUp);

                        if (!Options::bItems || bPickedUp) {
                            ItemPawns[x].IsValid = false;
                            continue;
                        }
                        else {
                            ItemPawns[x].Location = read_virtual<Vector>(ItemPawns[x].RootComponent + Offsets::RelativeLocation);

                            FN_POINTER ItemDefinition = read_virtual<FN_POINTER>(Pawn + Offsets::PrimaryPickupItemEntry + 0x18);
                            FN_POINTER DisplayName = read_virtual<FN_POINTER>(ItemDefinition + Offsets::DisplayName);
                            uint32_t WeaponLength = read_virtual<uint32_t>(DisplayName + 0x38);
                            wchar_t* WeaponName = new wchar_t[FN_POINTER(WeaponLength) + 1];
                            //memory::read_virtual_memory(read_virtual<PVOID>(DisplayName + 0x30), WeaponName, WeaponLength * sizeof(wchar_t));
                            std::wstring wWeaponName(WeaponName);
                            std::string sWeaponName(wWeaponName.begin(), wWeaponName.end());
                            BYTE Tier = read_virtual<BYTE>(ItemDefinition + Offsets::Tier);

                            int TierEx = Tier;
                            if (TierEx == 2) { //Rarity: Green
                                if (!Options::ItemTiers::bUncommon) {
                                    ItemPawns[x].IsValid = false;
                                    continue;
                                }
                            }
                            else if (TierEx == 3) { //Rarity: Blue
                                if (!Options::ItemTiers::bRare) {
                                    ItemPawns[x].IsValid = false;
                                    continue;
                                }
                                    
                            }
                            else if (TierEx == 4) { //Rarity: Purple
                                if (!Options::ItemTiers::bEpic) {
                                    ItemPawns[x].IsValid = false;
                                    continue;
                                }
                            }
                            else if (TierEx == 5) { //Rarity: Gold
                                if (!Options::ItemTiers::bLegendary) {
                                    ItemPawns[x].IsValid = false;
                                    continue;
                                }
                            }
                            else if (TierEx == 6) { //Rarity: Gold+
                                if (!Options::ItemTiers::bMythic) {
                                    ItemPawns[x].IsValid = false;
                                    continue;
                                }
                            }
                            else {
                                if (!Options::ItemTiers::bCommon) {
                                    ItemPawns[x].IsValid = false;
                                    continue;
                                }
                            }
                            ItemPawns[x].Name = sWeaponName;
                            ItemPawns[x].Tier = Tier;
                        }
                    }

                    if (N.find(TEXT("Vehicle")) != string::npos) {
                        BYTE bPlayedDying = read_virtual<BYTE>(Pawn + Offsets::bPlayedDying);
                        bool bIsDead = bPlayedDying == 0x15;

                        if (!Options::bVehicles || bIsDead) {
                           ItemPawns[x].IsValid = false;
                           continue;
                        }
                        else {
                            ItemPawns[x].Location = read_virtual<Vector>(ItemPawns[x].RootComponent + Offsets::RelativeLocation);
                        }
                    }

                    if (N.find(TEXT("BGA_Athena_FlopperSpawn_World_C")) != string::npos) {
                        bool bHidden = ((read_virtual<int>(Pawn + Offsets::bHidden) >> 7) & 1);

                        if (!Options::bFloppaSpawns || bHidden) {
                            ItemPawns[x].IsValid = false;
                            continue;
                        }
                        else {
                            ItemPawns[x].Location = read_virtual<Vector>(ItemPawns[x].RootComponent + Offsets::RelativeLocation);
                        }
                    }

                    Vector World = read_virtual<Vector>(ItemPawns[x].RootComponent + Offsets::RelativeLocation);
                    double Distance = FortCamera::Location.Distance(World) / 100;
                    if (Distance > Options::fMaxItemDistance) {
                        ItemPawns[x].IsValid = false;
                        continue;
                    }

                    if (bCheckOnScreen) {
                        Vector Screen = W2S(World);
                        if (bIsInRectangle(CenterX, CenterY, 850, Screen.x, Screen.y)) {
                            ItemPawns[x].IsOnScreen = true;
                        }
                        else {
                            ItemPawns[x].IsOnScreen = false;
                        }
                    }
                }
                C_FREEZE(100);
            }
        }
        
        VOID RenderItems() {
            ImDrawList* Draw = RENDER_BACKGROUND();

            int ClosestWeakSpot = 1337;
            float ClosestWeakSpotDistance = FLT_MAX;
            int ClosestZipline = 1337;
            float ClosestZiplineDistance = FLT_MAX;
            for (int x = 0; x < ItemPawns.size(); x++) {
                auto CurrentItem = ItemPawns[x];

                if (!CurrentItem.IsValid) {
                    auto Found = std::find(ItemPawns.begin(), ItemPawns.end(), ItemPawns[x]);
                    ItemPawns.erase(Found);
                    continue;
                }

                if (Options::bRadar && Options::bRadarDisplayLoot) {
                    float Distance = FortCamera::Location.Distance(CurrentItem.Location) / 100;
                    Radar::AddToRadar(ImGui::GetColorU32({ 1.0f, 1.0f, 0.0f, 1.0f }), CurrentItem.Location, Distance);
                }

                if (!CurrentItem.IsOnScreen)
                    continue;

                ImColor Color = ImVec4(CurrentItem.R / 255, CurrentItem.G / 255, CurrentItem.B / 255, CurrentItem.A / 255);

                
                if ((CurrentItem.FName.find(TEXT("Vehicle")) != string::npos)) {
                    Vector ScreenPosition = W2S(CurrentItem.Location);

                    char DisplayName[256];
                    if (Options::ItemFeatures::bDistance) {
                        float Distance = FortCamera::Location.Distance(CurrentItem.Location) / 100;
                        sprintf_s(DisplayName, TEXT("Vehicle (%.fm)"), Distance);
                    }
                    else {
                        sprintf_s(DisplayName, TEXT("Vehicle"));
                    }

                    auto Size = ImGui::CalcTextSize(DisplayName);
                    int ScreenX = ScreenPosition.x - (Size.x / 2);
                    int ScreenY = ScreenPosition.y;
                    if (Options::ItemFeatures::bOutline) {
                        Draw->AddText(mvec(ScreenX + 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX - 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX + 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX - 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                    }

                    Draw->AddText(mvec(ScreenX, ScreenY), Color, DisplayName);

                    if (Options::ItemFeatures::bSnapline) {
                        Draw->AddLine(mvec(CenterX, CenterY), mvec(ScreenPosition.x, ScreenPosition.y + 14), Color, 1.f);
                    }
                }
                else if ((CurrentItem.FName.find(TEXT("Tiered_Chest")) != string::npos)) {
                    Vector ScreenPosition = W2S(CurrentItem.Location);

                    char DisplayName[256];
                    if (Options::ItemFeatures::bDistance) {
                        float Distance = FortCamera::Location.Distance(CurrentItem.Location) / 100;
                        sprintf_s(DisplayName, TEXT("Loot crate (%.fm)"), Distance);
                    }
                    else {
                        sprintf_s(DisplayName, TEXT("Loot crate"));
                    }

                    auto Size = ImGui::CalcTextSize(DisplayName);
                    int ScreenX = ScreenPosition.x - (Size.x / 2);
                    int ScreenY = ScreenPosition.y;
                    if (Options::ItemFeatures::bOutline) {
                        Draw->AddText(mvec(ScreenX + 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX - 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX + 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX - 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                    }

                    Draw->AddText(mvec(ScreenX, ScreenY), Color, DisplayName);

                    if (Options::ItemFeatures::bSnapline) {
                        Draw->AddLine(mvec(CenterX, CenterY), mvec(ScreenPosition.x, ScreenPosition.y + 14), Color, 1.f);
                    }
                }
                else if ((CurrentItem.FName.find(TEXT("Tiered_Ammo")) != string::npos)) {
                    Vector ScreenPosition = W2S(CurrentItem.Location);

                    char DisplayName[256];
                    if (Options::ItemFeatures::bDistance) {
                        float Distance = FortCamera::Location.Distance(CurrentItem.Location) / 100;
                        sprintf_s(DisplayName, TEXT("Ammo box (%.fm)"), Distance);
                    }
                    else {
                        sprintf_s(DisplayName, TEXT("Ammo box"));
                    }

                    auto Size = ImGui::CalcTextSize(DisplayName);
                    int ScreenX = ScreenPosition.x - (Size.x / 2);
                    int ScreenY = ScreenPosition.y;
                    if (Options::ItemFeatures::bOutline) {
                        Draw->AddText(mvec(ScreenX + 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX - 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX + 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX - 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                    }

                    Draw->AddText(mvec(ScreenX, ScreenY), Color, DisplayName);

                    if (Options::ItemFeatures::bSnapline) {
                        Draw->AddLine(mvec(CenterX, CenterY), mvec(ScreenPosition.x, ScreenPosition.y + 14), Color, 1.f);
                    }
                }
                else if ((CurrentItem.FName.find(TEXT("BGA_Athena_FlopperSpawn_World_C")) != string::npos)) {
                    Vector ScreenPosition = W2S(CurrentItem.Location);

                    char DisplayName[256];
                    if (Options::ItemFeatures::bDistance) {
                        float Distance = FortCamera::Location.Distance(CurrentItem.Location) / 100;
                        sprintf_s(DisplayName, TEXT("Fishing spot (%.fm)"), Distance);
                    }
                    else {
                        sprintf_s(DisplayName, TEXT("Fishing spot"));
                    }

                    auto Size = ImGui::CalcTextSize(DisplayName);
                    int ScreenX = ScreenPosition.x - (Size.x / 2);
                    int ScreenY = ScreenPosition.y;
                    if (Options::ItemFeatures::bOutline) {
                        Draw->AddText(mvec(ScreenX + 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX - 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX + 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX - 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                    }

                    Draw->AddText(mvec(ScreenX, ScreenY), Color, DisplayName);

                    if (Options::ItemFeatures::bSnapline) {
                        Draw->AddLine(mvec(CenterX, CenterY), mvec(ScreenPosition.x, ScreenPosition.y + 14), Color, 1.f);
                    }
                }
                else if ((CurrentItem.FName.find(TEXT("CBGA_ShieldsSmall_C")) != string::npos)) {
                Vector ScreenPosition = W2S(CurrentItem.Location);

                char DisplayName[256];
                if (Options::ItemFeatures::bDistance) {
                    float Distance = FortCamera::Location.Distance(CurrentItem.Location) / 100;
                    sprintf_s(DisplayName, TEXT("Shield mushroom (%.fm)"), Distance);
                }
                else {
                    sprintf_s(DisplayName, TEXT("Shield mushroom"));
                }

                auto Size = ImGui::CalcTextSize(DisplayName);
                int ScreenX = ScreenPosition.x - (Size.x / 2);
                int ScreenY = ScreenPosition.y;
                if (Options::ItemFeatures::bOutline) {
                    Draw->AddText(mvec(ScreenX + 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                    Draw->AddText(mvec(ScreenX - 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                    Draw->AddText(mvec(ScreenX + 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                    Draw->AddText(mvec(ScreenX - 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                }

                Draw->AddText(mvec(ScreenX, ScreenY), Color, DisplayName);

                if (Options::ItemFeatures::bSnapline) {
                    Draw->AddLine(mvec(CenterX, CenterY), mvec(ScreenPosition.x, ScreenPosition.y + 14), Color, 1.f);
                }
                }
                else if ((CurrentItem.FName.find(TEXT("Athena_Prop_SilkyBingo_C")) != string::npos)) {
                    Vector ScreenPosition = W2S(CurrentItem.Location);

                    char DisplayName[256];
                    if (Options::ItemFeatures::bDistance) {
                        float Distance = FortCamera::Location.Distance(CurrentItem.Location) / 100;
                        sprintf_s(DisplayName, TEXT("Shield barrel (%.fm)"), Distance);
                    }
                    else {
                        sprintf_s(DisplayName, TEXT("Shield barrel"));
                    }

                    auto Size = ImGui::CalcTextSize(DisplayName);
                    int ScreenX = ScreenPosition.x - (Size.x / 2);
                    int ScreenY = ScreenPosition.y;
                    if (Options::ItemFeatures::bOutline) {
                        Draw->AddText(mvec(ScreenX + 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX - 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX + 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX - 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                    }

                    Draw->AddText(mvec(ScreenX, ScreenY), Color, DisplayName);

                    if (Options::ItemFeatures::bSnapline) {
                        Draw->AddLine(mvec(CenterX, CenterY), mvec(ScreenPosition.x, ScreenPosition.y + 14), Color, 1.f);
                    }
                }
                else if ((CurrentItem.FName.find(TEXT("FortPickupAthena")) != string::npos)) {
                    Vector ScreenPosition = W2S(CurrentItem.Location);

                    char DisplayName[256];
                    if (Options::ItemFeatures::bDistance) {
                        float Distance = FortCamera::Location.Distance(CurrentItem.Location) / 100;
                        sprintf_s(DisplayName, TEXT("%s (%.fm)"), CurrentItem.Name.c_str(), Distance);
                    }
                    else {
                        sprintf_s(DisplayName, TEXT("%s"), CurrentItem.Name.c_str());
                    }

                    auto Size = ImGui::CalcTextSize(DisplayName);
                    int ScreenX = ScreenPosition.x - (Size.x / 2);
                    int ScreenY = ScreenPosition.y;
                    if (Options::ItemFeatures::bOutline) {
                        Draw->AddText(mvec(ScreenX + 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX - 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX + 1, ScreenY - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                        Draw->AddText(mvec(ScreenX - 1, ScreenY + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), DisplayName);
                    }

                    Draw->AddText(mvec(ScreenX, ScreenY), Color, DisplayName);

                    if (Options::ItemFeatures::bSnapline) {
                        Draw->AddLine(mvec(CenterX, CenterY), mvec(ScreenPosition.x, ScreenPosition.y + 14), Color, 1.f);
                    }
                }
            }
        }
    }
}*/

namespace Cheat {
    namespace Actor {
        struct Player {
            uintptr_t Actor;
            uintptr_t Mesh;
            uintptr_t PlayerState;
            uintptr_t RootComponent;
            uintptr_t BoneArray;

            std::string WeaponName;

            INT32 AmmoCount;
            INT32 KillCount;
            INT32 TeamKillCount;

            Vector Location;
            Vector Rotation;

            double Distance;

            ImVec4 WeaponColor;

            bool IsValid;
        };

        inline bool operator==(const Player& a, const Player& b) {
            if (a.Actor == b.Actor)
                return true;
            return false;
        }

        std::vector<Player> PlayerPawns;
    }

    namespace Pointer {
        uintptr_t _UWorld;
        uintptr_t _Levels;
        uintptr_t _Controller;
        uintptr_t _PlayerState;
        uintptr_t _CameraManager;
        uintptr_t _ViewMatrix;
        uintptr_t _GetViewPoint;
        uintptr_t _CameraLocation;
        uintptr_t _Weapon;
        uintptr_t _LocalPawn;
        uintptr_t _LocalPawnOld;
        uintptr_t _PersistentLevel;

        namespace Sincey {
            void ExecuteExploits() {

            }
        }

        void UpdateCamrea() {
            while (true) {
                Camera::Location = read_virtual<Vector>(_CameraLocation);

                double Sine = read_virtual<uintptr_t>(_ViewMatrix + 0x790);
                double Cosnine = read_virtual<uintptr_t>(_ViewMatrix + 0x7b0);
                double Pitch = asin(read_virtual<double>(_ViewMatrix + 0xAe0)) * (180.0 / M_PI);
                double Yaw = atan2(Sine, Cosnine) * (180.0 / M_PI);
                Yaw *= -1;

                Camera::Rotation.x = Pitch;
                Camera::Rotation.y = Yaw;
                Camera::Rotation.z = 0;

                Camera::FOV = read_virtual<float>(_GetViewPoint + 0x47c);
            }
        }

        void UpdatePointers() {
            while (true) {
                uintptr_t UWorld = read_virtual<uintptr_t>(BaseAddress + Offsets::UWorld);
                if (!UWorld) continue;

                uintptr_t GetViewPoint = read_virtual<uintptr_t>(BaseAddress + 0xCB40E10);
                if (!GetViewPoint) continue;

                uintptr_t PersistentLevel = read_virtual<uintptr_t>(UWorld + Offsets::PersistentLevel);
                if (!PersistentLevel) continue;

                uintptr_t GameInstance = read_virtual<uintptr_t>(UWorld + Offsets::OwningGameInstance);
                if (!GameInstance) continue;

                uintptr_t LocalPlayers = read_virtual<uintptr_t>(GameInstance + Offsets::LocalPlayers);
                if (!LocalPlayers) continue;

                uintptr_t LocalPlayer = read_virtual<uintptr_t>(LocalPlayers);
                if (!LocalPlayer) continue;

                uintptr_t PlayerController = read_virtual<uintptr_t>(LocalPlayer + Offsets::PlayerController);
                if (!PlayerController) continue;

                uintptr_t LocalPawn = read_virtual<uintptr_t>(PlayerController + Offsets::AcknowledgedPawn);
                if (!LocalPawn) continue;

                uintptr_t LocalPlayerState = read_virtual<uintptr_t>(LocalPawn + Offsets::PlayerState);
                if (!LocalPlayerState) continue;

                uintptr_t LocalRootComponent = read_virtual<uintptr_t>(LocalPawn + Offsets::RootComponent);
                if (!LocalRootComponent) continue;

                uintptr_t CameraManager = read_virtual<uintptr_t>(PlayerController + Offsets::PlayerCameraManager);
                if (!CameraManager) continue;

                uintptr_t CameraLocation = read_virtual<uintptr_t>(UWorld + 0x100);
                if (!CameraLocation) continue;

                uintptr_t ViewMatrix_0 = read_virtual<uintptr_t>(LocalPlayer + 0xc8);
                if (!ViewMatrix_0) continue;

                uintptr_t ViewMatrix = read_virtual<uintptr_t>(ViewMatrix_0 + 0x8);
                if (!ViewMatrix) continue;

                uintptr_t ActorArray = read_virtual<uintptr_t>(PersistentLevel + Offsets::AActors);
                if (!ActorArray) continue;

                INT32 ActorCount = read_virtual<INT32>(PersistentLevel + Offsets::ActorCount);
                if (!ActorCount) continue;

                _UWorld = (uintptr_t)UWorld;
                _Controller = (uintptr_t)PlayerController;
                _LocalPawn = (uintptr_t)LocalPawn;
                _CameraManager = (uintptr_t)CameraManager;
                _PlayerState = (uintptr_t)LocalPlayerState;
                _CameraLocation = (uintptr_t)CameraLocation;
                _ViewMatrix = (uintptr_t)ViewMatrix;
                _GetViewPoint = (uintptr_t)GetViewPoint;
                _PersistentLevel = (uintptr_t)PersistentLevel;

                Sincey::ExecuteExploits();

                if (_LocalPawn != _LocalPawnOld) {
                    if (!Actor::PlayerPawns.empty())
                        Actor::PlayerPawns.clear();
                    std::cout << "\n[CLEAR ALL]";
                    _LocalPawnOld = _LocalPawn;
                }

                Sleep(1750);
            }
        }
    }

    namespace ActorLoop {
        namespace Player {
            void FindPlayers() {
                while (true) {
                    uintptr_t ActorArray = read_virtual<uintptr_t>(Pointer::_PersistentLevel + Offsets::AActors);
                    if (!ActorArray) continue;

                    INT32 ActorCount = read_virtual<INT32>(Pointer::_PersistentLevel + Offsets::ActorCount);
                    if (!ActorCount) continue;

                    for (int x = 0; x < ActorCount; x++) {
                        uintptr_t Actor = read_virtual<uintptr_t>(ActorArray + (x * sizeof(uintptr_t)));
                        if (!Actor) continue;
                        
                        INT32 ObjectID = read_virtual<INT32>(Actor + Offsets::ObjectID);
                        if (!ObjectID) continue;
                        
                        std::string Name = find_object_name(ObjectID);
                        if (Name == "") continue;
                        
                        if (Name.find("PlayerPawn") != std::string::npos) {
                            uintptr_t Mesh = read_virtual<uintptr_t>(Actor + Offsets::Mesh);
                            if (!Mesh) continue;
                            if (GetAsyncKeyState(VK_F2)) std::cout << "\n Mesh: " << Mesh;
                            uintptr_t RootComponent = read_virtual<uintptr_t>(Actor + Offsets::RootComponent);
                            if (!RootComponent) continue;
                            if (GetAsyncKeyState(VK_F2)) std::cout << "\n RootComponent: " << RootComponent;
                            uintptr_t BoneArray = read_virtual<uintptr_t>(Mesh + 0x590);
                            if (!BoneArray) continue;
                            if (GetAsyncKeyState(VK_F2)) std::cout << "\n BoneArray: " << BoneArray;
                            uintptr_t PlayerState = read_virtual<uintptr_t>(Actor + Offsets::PlayerState);
                            if (!PlayerState) continue;
                            if (GetAsyncKeyState(VK_F2)) std::cout << "\n PlayerState: " << PlayerState;
                            INT32 TeamID = read_virtual<INT32>(PlayerState + Offsets::TeamIndex);
                            INT32 LocalTeamID = read_virtual<INT32>(Pointer::_PlayerState + Offsets::TeamIndex);
                            if (LocalTeamID == TeamID) continue;
                            if (GetAsyncKeyState(VK_F2)) std::cout << "\n TeamID: " << TeamID;
                            Actor::Player Player
                            {
                                Actor,
                                Mesh,
                                PlayerState,
                                RootComponent,
                                BoneArray,
                                TEXT("Invalid"),
                                0,
                                0,
                                0,
                                Vector(0, 0, 0),
                                Vector(0, 0, 0),
                                0,
                                ImVec4(0, 0, 0, 0),
                                true
                            };

                            if (!Actor::PlayerPawns.empty()) {
                                auto found_player = std::find(Actor::PlayerPawns.begin(), Actor::PlayerPawns.end(), Player);
                                if (found_player == Actor::PlayerPawns.end())
                                    Actor::PlayerPawns.push_back(Player);
                            }
                            else
                                Actor::PlayerPawns.push_back(Player);
                        }
                    }
                }
            }

            void CheckPlayers() {
                while (true) {
                    if (Actor::PlayerPawns.size()) {
                        for (int x = 0; x < Actor::PlayerPawns.size(); x++) {
                            if (!Actor::PlayerPawns[x].IsValid) continue;

                            Vector HeadLocation = BoneMatrix(98, Actor::PlayerPawns[x].Mesh, Actor::PlayerPawns[x].BoneArray);
                            Vector Location = BoneMatrix(0, Actor::PlayerPawns[x].Mesh, Actor::PlayerPawns[x].BoneArray);

                            bool IsDying = read_virtual<BYTE>(Actor::PlayerPawns[x].Actor + 0x6d8) == 0x30;
                            bool IsHidden = read_virtual<BYTE>(Actor::PlayerPawns[x].Actor + 0x58) == 0x60;

                            double Distance = Camera::Location.Distance(Location) / 100;

                            if (IsDying || IsHidden) {
                                Actor::PlayerPawns[x].IsValid = false;
                                continue;
                            }

                            if ((Location.Distance(HeadLocation) / 100) > 10) {
                                Actor::PlayerPawns[x].IsValid = false;
                                continue;
                            }

                            if (Distance > 220) {
                                Actor::PlayerPawns[x].IsValid = false;
                                continue;
                            }
                        }
                    }

                    Sleep(750);
                }
            }
        }
    }

    namespace Renderer {
        void RenderPlayers() {
            if (Actor::PlayerPawns.size()) {
                for (int x = 0; x < Actor::PlayerPawns.size(); x++) {
                    Actor::Player Player = Actor::PlayerPawns[x];

                    if (!Player.IsValid) {
                        auto ThisPlayer = std::find(Actor::PlayerPawns.begin(), Actor::PlayerPawns.end(), Player);
                        Actor::PlayerPawns.erase(ThisPlayer);
                        continue;
                    }

                    Vector GIVEMEHEAD = BoneMatrix(98, Player.Mesh, Player.BoneArray);
                    Vector KEKW = W2S(GIVEMEHEAD);

                    ImGui::GetForegroundDrawList()->AddLine(mvec(CenterX, CenterY * 2), mvec(KEKW.x, KEKW.y), ImGui::GetColorU32({ 1.f, 1.f, 1.f, 1.f }), 1.f);
                }
            }
        }
    }
}

VOID HijackGame() {
    //ptr
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Cheat::Pointer::UpdatePointers, NULL, NULL, NULL); Sleep(200);
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Cheat::Pointer::UpdateCamrea, NULL, NULL, NULL); Sleep(200);

    //find
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Cheat::ActorLoop::Player::FindPlayers, NULL, NULL, NULL); Sleep(200);

    //check
    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Cheat::ActorLoop::Player::CheckPlayers, NULL, NULL, NULL); Sleep(200);
}

VOID RenderHijackedGame(HWND Window) { //jan.ga.n18.09@gmail.com

    //Push player font
    {
        if (Options::PlayerFonts::bArial)
            ImGui::PushFont(Fonts::Arial);
        else if (Options::PlayerFonts::bRajdhani)
            ImGui::PushFont(Fonts::Rajdhani);
        else if (Options::PlayerFonts::bVerdana)
            ImGui::PushFont(Fonts::Verdana);
        else if (Options::PlayerFonts::bFortniteFont)
            ImGui::PushFont(Fonts::FortniteFont);
        else if (Options::PlayerFonts::bGTAFont)
            ImGui::PushFont(Fonts::GTAFont);
        else
            ImGui::PushFont(Fonts::StandardFont);
    }

    if (Options::bRadar) {
        //Cheat::Radar::DrawRadarBackground();
    }
    Cheat::Renderer::RenderPlayers();

    // Cheat::Player::RenderPlayers();

    //char FpsNum[256];
    //sprintf_s(FpsNum, "%.f FPS", ImGui::GetIO().Framerate);
    //ImGui::GetForegroundDrawList()->AddText(mvec(100, 100), ImGui::GetColorU32({ 1.0f, 0.0f, 0.0f, 1.0f }), FpsNum);
    
    ImGui::PopFont();

    //Push environment font
    {
        if (Options::ItemFonts::bArial)
            ImGui::PushFont(Fonts::Arial);
        else if (Options::ItemFonts::bRajdhani)
            ImGui::PushFont(Fonts::Rajdhani);
        else if (Options::ItemFonts::bVerdana)
            ImGui::PushFont(Fonts::Verdana);
        else if (Options::ItemFonts::bFortniteFont)
            ImGui::PushFont(Fonts::FortniteFont);
        else if (Options::ItemFonts::bGTAFont)
            ImGui::PushFont(Fonts::GTAFont);
        else
            ImGui::PushFont(Fonts::StandardFont);
    }

    //Cheat::World::RenderItems();
    ImGui::PopFont();

    //Cheat::Misc::RenderMisc();

    Menu::RenderMenu(Window);
}