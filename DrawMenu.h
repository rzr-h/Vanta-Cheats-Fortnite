#pragma once

#include "Includes.h"
#include "Settings.h"
#include "Helper.h"
#include "Settings.h"
#include "RenderHelper.h"
#include "Auth.h"
#include "KernelDriver.h"
#include "Streamproof.h"

void ApplyColors(ImVec4* colors)
{
	colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.f);
	colors[ImGuiCol_Separator] = ImVec4(0.25f, 0.25f, 0.25f, 1.f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.f);
	colors[ImGuiCol_Border] = ImVec4(0.1f, 0.1f, 0.1f, 1.f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.1f, 0.1f, 0.1f, 1.f);
}

void ApplyStyle(ImGuiStyle& style)
{
	style.WindowRounding = 6.5f;
}

int MenuTab = 3;
int AimbotPage = 0;
int VisualPage = 0;
int ExploitPage = 0;
int SettingPage = 0;

std::string TestText = TEXT("Sincey is a fat man.");
bool ischeking = false;
std::vector<msg> ChatMessages;

void ChatSend() {
	if (!ischeking) {
		ischeking = true;
		std::string MessageTextEx = TEXT("Test");
		if (Auth::Role == 0) {
			std::string NameOfRole = TEXT("(User) ");
			MessageTextEx = NameOfRole + MessageText;
		}
		else if (Auth::Role == 1) {
			std::string NameOfRole = TEXT("(Tester) ");
			MessageTextEx = NameOfRole + MessageText;
		}
		else if (Auth::Role == 2) {
			std::string NameOfRole = TEXT("(Reseller) ");
			MessageTextEx = NameOfRole + MessageText;
		}
		else if (Auth::Role == 3) {
			std::string NameOfRole = TEXT("(Staff) ");
			MessageTextEx = NameOfRole + MessageText;
		}
		else if (Auth::Role == 4) {
			std::string NameOfRole = TEXT("(Admin) ");
			MessageTextEx = NameOfRole + MessageText;
		}
		else if (Auth::Role == 5) {
			std::string NameOfRole = TEXT("(Developer) ");
			MessageTextEx = NameOfRole + MessageText;
		}
		else if (Auth::Role == 1) {
			std::string NameOfRole = TEXT("(Owner) ");
			MessageTextEx = NameOfRole + MessageText;
		}
		else {
			std::string NameOfRole = TEXT("(User) ");
			MessageTextEx = NameOfRole + MessageText;
		}
		char NextText[187];
		sprintf_s(NextText, TEXT("%s"), MessageTextEx);

		KeyAuthApp.chatsend(NextText, TEXT("mainchat"));
		memset(NextText, 0, sizeof NextText);
		ischeking = false;
	}
	else
	{

		while (1) {
			if (!ischeking) {
				ischeking = true;
				std::string MessageTextEx = TEXT("Test");
				if (Auth::Role == 0) {
					std::string NameOfRole = TEXT("(User) ");
					MessageTextEx = NameOfRole + MessageText;
				}
				else if (Auth::Role == 1) {
					std::string NameOfRole = TEXT("(Tester) ");
					MessageTextEx = NameOfRole + MessageText;
				}
				else if (Auth::Role == 2) {
					std::string NameOfRole = TEXT("(Reseller) ");
					MessageTextEx = NameOfRole + MessageText;
				}
				else if (Auth::Role == 3) {
					std::string NameOfRole = TEXT("(Staff) ");
					MessageTextEx = NameOfRole + MessageText;
				}
				else if (Auth::Role == 4) {
					std::string NameOfRole = TEXT("(Admin) ");
					MessageTextEx = NameOfRole + MessageText;
				}
				else if (Auth::Role == 5) {
					std::string NameOfRole = TEXT("(Developer) ");
					MessageTextEx = NameOfRole + MessageText;
				}
				else if (Auth::Role == 1) {
					std::string NameOfRole = TEXT("(Owner) ");
					MessageTextEx = NameOfRole + MessageText;
				}
				else {
					std::string NameOfRole = TEXT("(User) ");
					MessageTextEx = NameOfRole + MessageText;
				}
				char NextText[187];
				sprintf_s(NextText, TEXT("%s"), MessageTextEx);

				KeyAuthApp.chatsend(NextText, TEXT("mainchat"));
				memset(NextText, 0, sizeof NextText);
				ischeking = false;
				break;
			}
			Sleep(100);
		}
	}
}

void ChatThread() {
	while (true)
	{
		Sleep(100);
		if (!ischeking) {
			ischeking = true;
			ChatMessages = KeyAuthApp.chatget(TEXT("mainchat"));
			ischeking = false;
		}
	}
}
namespace Preview
{
	namespace box3d {
		float topleftfront_x = -72.f;
		float topleftfront_y = 82.f;

		float topleftback_x = -54.f;
		float topleftback_y = 61.f;

		float toprightfront_x = 61.f;
		float toprightfront_y = 82.f;

		float toprightback_x = 74.f;
		float toprightback_y = 61.f;

		float bottomleftfront_x = -85.f;
		float bottomleftfront_y = 335.f;

		float bottomleftback_x = -67.f;
		float bottomleftback_y = 305.f;

		float bottomrightfront_x = 49.f;
		float bottomrightfront_y = 342.f;

		float bottomrightback_x = 64.f;
		float bottomrightback_y = 312.f;
	}

	float head_bone_x = 0;
	float head_bone_y = 94;

	float neck_bone_x = 4;
	float neck_bone_y = 114;

	float chest_bone_x = 2;
	float chest_bone_y = 122;

	float left_shoulder_bone_x = -24;
	float left_shoulder_bone_y = 124;

	float left_elbow_bone_x = -37;
	float left_elbow_bone_y = 153;

	float left_hand_bone_x = -51;
	float left_hand_bone_y = 196;

	float right_hand_bone_x = 47;
	float right_hand_bone_y = 190;

	float right_elbow_bone_x = 43;
	float right_elbow_bone_y = 167;

	float right_shoulder_bone_x = 20;
	float right_shoulder_bone_y = 124;

	float pelvis_bone_x = -6;
	float pelvis_bone_y = 184;

	float left_thigh_bone_x = -22;
	float left_thigh_bone_y = 186;

	float right_thigh_bone_x = 12;
	float right_thigh_bone_y = 186;

	float right_knee_bone_x = 25;
	float right_knee_bone_y = 253;

	float left_knee_bone_x = -37;
	float left_knee_bone_y = 245;

	float right_foot_bone_x = 31;
	float right_foot_bone_y = 310;

	float left_foot_bone_x = -47;
	float left_foot_bone_y = 308;

	float right_footfinger_bone_x = 37;
	float right_footfinger_bone_y = 324;

	float left_footfinger_bone_x = -57;
	float left_footfinger_bone_y = 322;

}

bool ColorsApplied = false;

void ApplyCheatColors() {

	//Visible
	{
		Options::PlayerColor::BoxVisible[0] = 1.0f;
		Options::PlayerColor::BoxVisible[1] = 0.0f;
		Options::PlayerColor::BoxVisible[2] = 0.0f;

		Options::PlayerColor::SkeletonVisible[0] = 0.8f;
		Options::PlayerColor::SkeletonVisible[1] = 0.1f;
		Options::PlayerColor::SkeletonVisible[2] = 0.1f;

		Options::PlayerColor::SnaplineVisible[0] = 0.8f;
		Options::PlayerColor::SnaplineVisible[1] = 0.1f;
		Options::PlayerColor::SnaplineVisible[2] = 0.1f;

		Options::PlayerColor::TopTextVisible[0] = 0.9f;
		Options::PlayerColor::TopTextVisible[1] = 0.9f;
		Options::PlayerColor::TopTextVisible[2] = 0.1f;

		Options::PlayerColor::BottomTextVisible[0] = 0.9f;
		Options::PlayerColor::BottomTextVisible[1] = 0.9f;
		Options::PlayerColor::BottomTextVisible[2] = 0.1f;
	}

	//Not Visible
	{
		Options::PlayerColor::BoxNotVisible[0] = 0.85f;
		Options::PlayerColor::BoxNotVisible[1] = 0.85f;
		Options::PlayerColor::BoxNotVisible[2] = 0.85f;

		Options::PlayerColor::SkeletonNotVisible[0] = 0.75f;
		Options::PlayerColor::SkeletonNotVisible[1] = 0.75f;
		Options::PlayerColor::SkeletonNotVisible[2] = 0.75f;

		Options::PlayerColor::SnaplineNotVisible[0] = 0.75f;
		Options::PlayerColor::SnaplineNotVisible[1] = 0.75f;
		Options::PlayerColor::SnaplineNotVisible[2] = 0.75f;

		Options::PlayerColor::TopTextNotVisible[0] = 0.9f;
		Options::PlayerColor::TopTextNotVisible[1] = 0.9f;
		Options::PlayerColor::TopTextNotVisible[2] = 0.1f;

		Options::PlayerColor::BottomTextNotVisible[0] = 0.9f;
		Options::PlayerColor::BottomTextNotVisible[1] = 0.9f;
		Options::PlayerColor::BottomTextNotVisible[2] = 0.1f;
	}

	ColorsApplied = true;
}
void MakeMenu()
{
	using namespace Options;

	if (!ColorsApplied)
		ApplyCheatColors();

	ImGui::PushFont(Fonts::Verdana);
	ImDrawList* m = ImGui::GetForegroundDrawList();
	ImDrawList* u = ImGui::GetBackgroundDrawList();
	u->AddRectFilled(mvec(0, 0), mvec(CenterX * 2, CenterY * 2), IM_COL32(0, 0, 0, 100), 0.0f, 0);
	static bool m_open = true;
	static int m_size_x = 670;
	static int m_size_y = 380;
	static int m_pos_x = CenterX - (m_size_x / 2);
	static int m_pos_y = CenterY - (m_size_y / 2);
	auto m_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;
	auto& m_style = ImGui::GetStyle();
	ImGuiIO& m_io = ImGui::GetIO(); (void)m_io;
	ImVec4* m_colors = ImGui::GetStyle().Colors;
	
	ApplyColors(m_colors);
	ApplyStyle(m_style);

	//help text
	//auto Size = ImGui::CalcTextSize(TestText.c_str());
	//m->AddRectFilled(mvec(CenterX - (Size.x / 2) - 5, m_pos_y - 30), mvec(CenterX + (Size.x / 2) + 5, m_pos_y - 5), ImGui::GetColorU32({ 0.1f, 0.1f, 0.1f, 1.f }), 6.5f, 0);
	//m->AddText(mvec(CenterX - (Size.x / 2), m_pos_y - 25), ImGui::GetColorU32({ 0.92f, 0.92f, 0.92f, 1.0f }), TestText.c_str());

	//buttons
	if (ImGui::Begin(TEXT("vantacheats.com - buttons main"), &m_open, m_flags)) {
		int SizeOfThisX = 63;
		int offset_y = 75;
		int test = 19;

		ImGui::SetWindowPos(mvec(m_pos_x - (SizeOfThisX + 25), m_pos_y + offset_y + (test / 2)));
		ImGui::SetWindowSize(mvec(SizeOfThisX, m_size_y - ((offset_y * 2) + test)));
		ImGui::BeginChild(TEXT("C_Buttons"), mvec(100, (m_size_y - ((offset_y * 2))) - 33.5f), false, m_flags);
		ImGui::PushFont(Fonts::TextureFont);

		ImGui::EpicButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("a"));
		if (ImGui::IsItemClicked())
			MenuTab = 0;

		ImGui::EpicButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("c"));
		if (ImGui::IsItemClicked())
			MenuTab = 1;

		ImGui::EpicButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("b"));
		if (ImGui::IsItemClicked())
			MenuTab = 2;

		ImGui::EpicButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("d"));
		if (ImGui::IsItemClicked())
			MenuTab = 3;

		ImGui::PushFont(Fonts::Verdana);
		ImGui::EndChild();
		ImGui::End();
	}

	//esp preview
	{
		//setup
		int lenght = 250;
		int x1 = m_pos_x + m_size_x + 25;
		int y1 = m_pos_y;
		int x2 = m_pos_x + m_size_x + 25 + lenght;
		int y2 = m_pos_y + m_size_y;
		int x3 = (x1 + lenght) - (lenght / 2);
		auto Color_Vec4 = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
		auto Color_GCU32 = ImGui::GetColorU32({ 1.0f, 0.0f, 0.0f, 1.0f });
		auto Color_U32 = IM_COL32(255, 0, 0, 255);

		//background
		m->AddRectFilled(mvec(x1, y1), mvec(x2, y2), ImGui::GetColorU32({ 0.1f, 0.1f, 0.1f, 1.f }), 6.5f, 0);

		//title
		//auto Size = ImGui::CalcTextSize(TEXT("esp preview"));
		//m->AddText(mvec(x3 - (Size.x / 2), y1 + 7), ImGui::GetColorU32({ 0.92f, 0.92f, 0.92f, 1.0f }), TEXT("esp preview"));

		//setup esp font
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

		//reset
		y1 = y1 - 20;
		auto __top_x = x3 + Preview::head_bone_x;
		auto __top_y = (y1 + Preview::head_bone_y - 20);
		auto __bottom_x = x3 + Preview::head_bone_x;
		auto __bottom_y = (y1 + Preview::right_footfinger_bone_y) + 20;

		auto ColorBox = ImVec4(Options::PlayerColor::BoxVisible[0], Options::PlayerColor::BoxVisible[1], Options::PlayerColor::BoxVisible[2], 1.0f);
		auto ColorSkeleton = ImVec4(Options::PlayerColor::SkeletonVisible[0], Options::PlayerColor::SkeletonVisible[1], Options::PlayerColor::SkeletonVisible[2], 1.0f);
		auto ColorSnapline = ImVec4(Options::PlayerColor::SnaplineVisible[0], Options::PlayerColor::SnaplineVisible[1], Options::PlayerColor::SnaplineVisible[2], 1.0f);
		auto ColorTopText = ImVec4(Options::PlayerColor::TopTextVisible[0], Options::PlayerColor::TopTextVisible[1], Options::PlayerColor::TopTextVisible[2], 1.0f);
		auto ColorBottomText = ImVec4(Options::PlayerColor::BottomTextVisible[0], Options::PlayerColor::BottomTextVisible[1], Options::PlayerColor::BottomTextVisible[2], 1.0f);

		//box
		if (Options::bCharacters)
		{
			if (Options::CharacterModes::b3D)
			{
				using namespace Preview::box3d;
				//top square
				m->AddLine(mvec(x3 + topleftfront_x, y1 + topleftfront_y), mvec(x3 + topleftback_x, y1 + topleftback_y), ImGui::GetColorU32({ ColorBox.x, ColorBox.y, ColorBox.z, 2.0f }));
				m->AddLine(mvec(x3 + topleftfront_x, y1 + topleftfront_y), mvec(x3 + toprightfront_x, y1 + toprightfront_y), ImGui::GetColorU32({ ColorBox.x, ColorBox.y, ColorBox.z, 2.0f }));
				m->AddLine(mvec(x3 + topleftback_x, y1 + topleftback_y), mvec(x3 + toprightback_x, y1 + toprightback_y), ImGui::GetColorU32({ ColorBox.x, ColorBox.y, ColorBox.z, 2.0f }));
				m->AddLine(mvec(x3 + toprightback_x, y1 + toprightback_y), mvec(x3 + toprightfront_x, y1 + toprightfront_y), ImGui::GetColorU32({ ColorBox.x, ColorBox.y, ColorBox.z, 2.0f }));

				//bottom square
				m->AddLine(mvec(x3 + bottomleftfront_x, y1 + bottomleftfront_y), mvec(x3 + bottomleftback_x, y1 + bottomleftback_y), ImGui::GetColorU32({ ColorBox.x, ColorBox.y, ColorBox.z, 2.0f }));
				m->AddLine(mvec(x3 + bottomleftfront_x, y1 + bottomleftfront_y), mvec(x3 + bottomrightfront_x, y1 + bottomrightfront_y), ImGui::GetColorU32({ ColorBox.x, ColorBox.y, ColorBox.z, 2.0f }));
				m->AddLine(mvec(x3 + bottomleftback_x, y1 + bottomleftback_y), mvec(x3 + bottomrightback_x, y1 + bottomrightback_y), ImGui::GetColorU32({ ColorBox.x, ColorBox.y, ColorBox.z, 2.0f }));
				m->AddLine(mvec(x3 + bottomrightback_x, y1 + bottomrightback_y), mvec(x3 + bottomrightfront_x, y1 + bottomrightfront_y), ImGui::GetColorU32({ ColorBox.x, ColorBox.y, ColorBox.z, 2.0f }));

				//top-bottom connection
				m->AddLine(mvec(x3 + topleftfront_x, y1 + topleftfront_y), mvec(x3 + bottomleftfront_x, y1 + bottomleftfront_y), ImGui::GetColorU32({ ColorBox.x, ColorBox.y, ColorBox.z, 2.0f }));
				m->AddLine(mvec(x3 + topleftback_x, y1 + topleftback_y), mvec(x3 + bottomleftback_x, y1 + bottomleftback_y), ImGui::GetColorU32({ ColorBox.x, ColorBox.y, ColorBox.z, 2.0f }));
				m->AddLine(mvec(x3 + toprightfront_x, y1 + toprightfront_y), mvec(x3 + bottomrightfront_x, y1 + bottomrightfront_y), ImGui::GetColorU32({ ColorBox.x, ColorBox.y, ColorBox.z, 2.0f }));
				m->AddLine(mvec(x3 + toprightback_x, y1 + toprightback_y), mvec(x3 + bottomrightback_x, y1 + bottomrightback_y), ImGui::GetColorU32({ ColorBox.x, ColorBox.y, ColorBox.z, 2.0f }));

			}
			else if (Options::CharacterModes::bCorner) {
				float BoxHeight = __bottom_y - __top_y;
				float BoxWidth = BoxHeight / 1.6f;
				RenderBox(true, 4, 4, __bottom_x - (BoxWidth / 2), __top_y,
					BoxWidth, BoxHeight, ColorBox, 2.0f, Options::CharacterModes::bFill2DBox, false);
			}
			else if (Options::CharacterModes::b2D) {
				float BoxHeight = __bottom_y - __top_y;
				float BoxWidth = BoxHeight / 1.6f;
				RenderBox(true, 4, 4, __bottom_x - (BoxWidth / 2), __top_y,
					BoxWidth, BoxHeight, ColorBox, 2.0f, Options::CharacterModes::bFill2DBox, true);
			}

		}

		//top text
		{
			int ThisOffset = 16;
			/*
			//platform
			if (Settings::Visuals::Player::Platform) {
				auto Size = ImGui::CalcTextSize(TEXT("Windows"));
				m->AddText(mvec(__top_x - (Size.x / 2), __top_y - ThisOffset), ImGui::GetColorU32({ ColorTopText.x, ColorTopText.y, ColorTopText.z, 1.0f }), TEXT("Windows"));
				ThisOffset = ThisOffset + 14;
			}


			//Username
			if (Settings::Visuals::Player::Username) {
				auto Size = ImGui::CalcTextSize(TEXT("Xenos1337"));
				m->AddText(mvec(__top_x - (Size.x / 2), __top_y - ThisOffset), ImGui::GetColorU32({ ColorTopText.x, ColorTopText.y, ColorTopText.z, 1.0f }), TEXT("Xenos1337"));
				ThisOffset = ThisOffset + 14;
			}*/

			//distance
			if (Options::bPlayerDistance) {
				auto Size = ImGui::CalcTextSize(TEXT("[13m]"));
				Render::MakeText(TEXT("[13m]"), mvec(__top_x - (Size.x / 2), __top_y - ThisOffset), ImGui::GetColorU32({ ColorTopText.x, ColorTopText.y, ColorTopText.z, 1.0f }), false, Options::PlayerFeatures::OutlinedText);
				//m->AddText(mvec(__top_x - (Size.x / 2), __top_y - ThisOffset), ImGui::GetColorU32({ ColorTopText.x, ColorTopText.y, ColorTopText.z, 1.0f }), TEXT("[13m]"));
				ThisOffset = ThisOffset + 14;
			}

			//snapline
			if (Options::bSnapline) {
				if (Options::SnaplineStart::bTop)
					m->AddLine(mvec(x3 - 7, m_pos_y), mvec(__bottom_x, __top_y - ThisOffset), ImGui::GetColorU32({ ColorSnapline.x, ColorSnapline.y, ColorSnapline.z, 1.0f }), 1.0f);
			}
		}

		//bottom text
		{
			int ThisOffset = 3;

			//weapon
			if (Options::bCurrentWeapon) {
				auto Size = ImGui::CalcTextSize(TEXT("Pump Shotgun"));
				Render::MakeText(TEXT("Pump Shotgun"), mvec(__bottom_x - (Size.x / 2), __bottom_y + ThisOffset), ImGui::GetColorU32({ 0.17f, 0.64f, 0.89f, 1.0f }), false, Options::PlayerFeatures::OutlinedText);
				//m->AddText(mvec(__bottom_x - (Size.x / 2), __bottom_y + ThisOffset), ImGui::GetColorU32({ 0.17f, 0.64f, 0.89f, 1.0f }), TEXT("Pump Shotgun"));
				ThisOffset = ThisOffset + 14;
			}

			//ammo count
			if (Options::bAmmoCount) {
				auto Size = ImGui::CalcTextSize(TEXT("[4/n]"));
				Render::MakeText(TEXT("[4/n]"), mvec(__bottom_x - (Size.x / 2), __bottom_y + ThisOffset), ImGui::GetColorU32({ 0.17f, 0.64f, 0.89f, 1.0f }), false, Options::PlayerFeatures::OutlinedText);
				//m->AddText(mvec(__bottom_x - (Size.x / 2), __bottom_y + ThisOffset), ImGui::GetColorU32({ 0.17f, 0.64f, 0.89f, 1.0f }), TEXT("[4/n]"));
				ThisOffset = ThisOffset + 14;
			}

			//player info
			if (Options::bPlayerInfo) {
				auto Size = ImGui::CalcTextSize(TEXT("[Equipping weapon]"));
				Render::MakeText(TEXT("[Equipping weapon]"), mvec(__bottom_x - (Size.x / 2), __bottom_y + ThisOffset), ImGui::GetColorU32({ ColorBottomText.x, ColorBottomText.y, ColorBottomText.z, 1.0f }), false, Options::PlayerFeatures::OutlinedText);
				//m->AddText(mvec(__bottom_x - (Size.x / 2), __bottom_y + ThisOffset), ImGui::GetColorU32({ ColorBottomText.x, ColorBottomText.y, ColorBottomText.z, 1.0f }), TEXT("[Equipping weapon]"));
				ThisOffset = ThisOffset + 14;
			}

			//snapline
			if (Options::bSnapline) {
				if (Options::SnaplineStart::bBottom)
					m->AddLine(mvec(x3 - 7, m_pos_y + m_size_y), mvec(__bottom_x, __bottom_y + ThisOffset), ImGui::GetColorU32({ ColorSnapline.x, ColorSnapline.y, ColorSnapline.z, 1.0f }), 1.0f);
			}
		}

		//skeleton
		if (Options::bSkeleton)
		{
			//top
			m->AddLine(mvec(x3 + Preview::head_bone_x, y1 + Preview::head_bone_y), mvec(x3 + Preview::neck_bone_x, y1 + Preview::neck_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
			m->AddLine(mvec(x3 + Preview::neck_bone_x, y1 + Preview::neck_bone_y), mvec(x3 + Preview::chest_bone_x, y1 + Preview::chest_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);

			//left arm
			m->AddLine(mvec(x3 + Preview::chest_bone_x, y1 + Preview::chest_bone_y), mvec(x3 + Preview::left_shoulder_bone_x, y1 + Preview::left_shoulder_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
			m->AddLine(mvec(x3 + Preview::left_shoulder_bone_x, y1 + Preview::left_shoulder_bone_y), mvec(x3 + Preview::left_elbow_bone_x, y1 + Preview::left_elbow_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
			m->AddLine(mvec(x3 + Preview::left_elbow_bone_x, y1 + Preview::left_elbow_bone_y), mvec(x3 + Preview::left_hand_bone_x, y1 + Preview::left_hand_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);

			//right arm
			m->AddLine(mvec(x3 + Preview::chest_bone_x, y1 + Preview::chest_bone_y), mvec(x3 + Preview::right_shoulder_bone_x, y1 + Preview::right_shoulder_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
			m->AddLine(mvec(x3 + Preview::right_shoulder_bone_x, y1 + Preview::right_shoulder_bone_y), mvec(x3 + Preview::right_elbow_bone_x, y1 + Preview::right_elbow_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
			m->AddLine(mvec(x3 + Preview::right_elbow_bone_x, y1 + Preview::right_elbow_bone_y), mvec(x3 + Preview::right_hand_bone_x, y1 + Preview::right_hand_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);

			//wtf!
			m->AddLine(mvec(x3 + Preview::chest_bone_x, y1 + Preview::chest_bone_y), mvec(x3 + Preview::pelvis_bone_x, y1 + Preview::pelvis_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);

			//left foot
			m->AddLine(mvec(x3 + Preview::pelvis_bone_x, y1 + Preview::pelvis_bone_y), mvec(x3 + Preview::left_thigh_bone_x, y1 + Preview::left_thigh_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
			m->AddLine(mvec(x3 + Preview::left_thigh_bone_x, y1 + Preview::left_thigh_bone_y), mvec(x3 + Preview::left_knee_bone_x, y1 + Preview::left_knee_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
			m->AddLine(mvec(x3 + Preview::left_knee_bone_x, y1 + Preview::left_knee_bone_y), mvec(x3 + Preview::left_foot_bone_x, y1 + Preview::left_foot_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
			m->AddLine(mvec(x3 + Preview::left_foot_bone_x, y1 + Preview::left_foot_bone_y), mvec(x3 + Preview::left_footfinger_bone_x, y1 + Preview::left_footfinger_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);

			//right foot
			m->AddLine(mvec(x3 + Preview::pelvis_bone_x, y1 + Preview::pelvis_bone_y), mvec(x3 + Preview::right_thigh_bone_x, y1 + Preview::right_thigh_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
			m->AddLine(mvec(x3 + Preview::right_thigh_bone_x, y1 + Preview::right_thigh_bone_y), mvec(x3 + Preview::right_knee_bone_x, y1 + Preview::right_knee_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
			m->AddLine(mvec(x3 + Preview::right_knee_bone_x, y1 + Preview::right_knee_bone_y), mvec(x3 + Preview::right_foot_bone_x, y1 + Preview::right_foot_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
			m->AddLine(mvec(x3 + Preview::right_foot_bone_x, y1 + Preview::right_foot_bone_y), mvec(x3 + Preview::right_footfinger_bone_x, y1 + Preview::right_footfinger_bone_y), ImGui::GetColorU32({ ColorSkeleton.x, ColorSkeleton.y, ColorSkeleton.z, 1.0f }), 1.0f);
		}

		ImGui::PopFont();
	}


	ImGui::PushFont(Fonts::Verdana);

	if (ImGui::Begin(TEXT("C_Renderer_Main"), &m_open, m_flags)) {
		ImGui::SetWindowSize(mvec(m_size_x, m_size_y));
		ImGui::SetWindowPos(mvec(m_pos_x, m_pos_y));
		ImGui::Text(TEXT(""));
		ImGui::Text(TEXT("")); ImGui::SameLine();

		//Players
		{
			if (MenuTab == 0) {
				if (ImGui::BeginChild(TEXT("C_Player_Tab"), mvec(650, 340))) {
					ImGui::Text(TEXT(""));
					if (bShowVisualButtons) {
						if (AimbotPage == 0) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Assault rifle"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Assault rifle"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							AimbotPage = 0;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("Aimbot configuration for assault rifles.");
						}

						ImGui::SameLine();
						if (AimbotPage == 1) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("SMG / MP"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("SMG / MP"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							AimbotPage = 1;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("Aimbot configuration for SMG's.");
						}

						ImGui::SameLine();
						if (AimbotPage == 2) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Shotguns"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Shotguns"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							AimbotPage = 2;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("Aimbot configuration for Shotguns");
						}

						ImGui::SameLine();
						if (AimbotPage == 3) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Sniper rifles"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Sniper rifles"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							AimbotPage = 3;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("Aimbot configuration for sniper rifles.");
						}

						ImGui::SameLine();
						if (AimbotPage == 4) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Other weapons"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Other weapons"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							AimbotPage = 4;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("Aimbot configuration for all other weapons.");
						}
					}
					if (AimbotPage == 0) { //Assault rifle
						using namespace Options::AssaultRifle;
						if (ImGui::BeginChild(TEXT("C_Aimbot_AssaultRifle_Tab_One"), mvec(300, 270))) {
							ImGui::Text(TEXT("Assault rifle aimbot config"));
							ImGui::CoolCheckbox(TEXT("Enable"), &bAimbot);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Enable aimbot for assault rifles.");
							}
							ImGui::CoolCheckbox(TEXT("Knocked players"), &bKnockedPlayers);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Allow the aimbot to target knocked players.");
							}
							ImGui::CoolCheckbox(TEXT("Visible players"), &bVisibleOnly);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Allow the aimbot to target visible players.");
							}
							ImGui::CoolCheckbox(TEXT("Render FOV"), &bRenderFOV);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Draw a circle showing the aimbot field of view.");
							}
							ImGui::CoolCheckbox(TEXT("Backtrack"), &bBacktrack);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Makes the enemy stuck while aimbotting. [RISK!]");
							}
							ImGui::CoolCheckbox(TEXT("Line to target"), &bLineToTarget);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Draws a line to the targetted player.");
							}
							ImGui::SliderFloat(fAimLineThickness, TEXT("Aimline (t)"), &fAimLineThickness, 0.5f, 5.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Thickness of the aimbot line.");
							}
							ImGui::SliderFloat(fAimbotFOV, TEXT("Field of view"), &fAimbotFOV, 0.f, 360.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Aimbot field of view.");
							}
							ImGui::SliderFloat(fAimbotSmooth, TEXT("Slowness"), &fAimbotSmooth, 0.f, 25.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Speed of the aimbot. The higher, the slower (ONLY Mouse aimbot is supported).");
							}
							ImGui::EndChild();
						} ImGui::SameLine();
						if (ImGui::BeginChild(TEXT("C_Aimbot_AssaultRifle_Tab_Two"), mvec(300, 270))) {
							ImGui::Text(TEXT("Target bone"));
							if (ImGui::BeginChild(TEXT("C_Targetbone_One"), mvec(100, 44))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Closest bone"), &AimTarget::bClosestBone);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Closest bone to the targetted player.");
								}
								if (ClickedA && AimTarget::bClosestBone) {
									AimTarget::bHead = false;
									AimTarget::bNeck = false;
									AimTarget::bBody = false;
								}
								else if (ClickedA && !AimTarget::bHead && !AimTarget::bNeck && !AimTarget::bBody) {
									AimTarget::bClosestBone = true;
								}
								bool ClickedC = ImGui::CoolCheckbox(TEXT("Head bone"), &AimTarget::bHead);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Head of targetted player.");
								}
								if (ClickedC && AimTarget::bHead) {
									AimTarget::bClosestBone = false;
									AimTarget::bNeck = false;
									AimTarget::bBody = false;
								}
								else if (ClickedC && !AimTarget::bClosestBone && !AimTarget::bNeck && !AimTarget::bBody) {
									AimTarget::bHead = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Targetbone_Two"), mvec(100, 44))) {
								bool ClickedB = ImGui::CoolCheckbox(TEXT("Neck bone"), &AimTarget::bNeck);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Neck of targetted player.");
								}
								if (ClickedB && AimTarget::bNeck) {
									AimTarget::bHead = false;
									AimTarget::bClosestBone = false;
									AimTarget::bBody = false;
								}
								else if (ClickedB && !AimTarget::bHead && !AimTarget::bClosestBone && !AimTarget::bBody) {
									AimTarget::bNeck = true;
								}
								bool ClickedD = ImGui::CoolCheckbox(TEXT("Body bone"), &AimTarget::bBody);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Body of targetted player.");
								}
								if (ClickedD && AimTarget::bBody) {
									AimTarget::bHead = false;
									AimTarget::bClosestBone = false;
									AimTarget::bNeck = false;
								}
								else if (ClickedD && !AimTarget::bHead && !AimTarget::bClosestBone && !AimTarget::bNeck) {
									AimTarget::bBody = true;
								}
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Keybind"));
							if (ImGui::BeginChild(TEXT("C_Keybind_One"), mvec(100, 44))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Universal"), &Aimkey::bUniversal);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Universal (Active whenever you are aiming, controllers are supported)");
								}
								if (ClickedA && Aimkey::bUniversal) {
									Aimkey::bLMouse = false;
									Aimkey::bRMouse = false;
									Aimkey::bShift = false;
								}
								else if (ClickedA && !Aimkey::bLMouse && !Aimkey::bRMouse && !Aimkey::bShift) {
									Aimkey::bUniversal = true;
								}
								bool ClickedC = ImGui::CoolCheckbox(TEXT("Left mouse"), &Aimkey::bLMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Left mouse button.");
								}
								if (ClickedC && Aimkey::bLMouse) {
									Aimkey::bUniversal = false;
									Aimkey::bRMouse = false;
									Aimkey::bShift = false;
								}
								else if (ClickedC && !Aimkey::bUniversal && !Aimkey::bRMouse && !Aimkey::bShift) {
									Aimkey::bLMouse = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Keybind_Two"), mvec(100, 44))) {
								bool ClickedB = ImGui::CoolCheckbox(TEXT("Right mouse"), &Aimkey::bRMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Right mouse button.");
								}
								if (ClickedB && Aimkey::bRMouse) {
									Aimkey::bLMouse = false;
									Aimkey::bUniversal = false;
									Aimkey::bShift = false;
								}
								else if (ClickedB && !Aimkey::bLMouse && !Aimkey::bUniversal && !Aimkey::bShift) {
									Aimkey::bRMouse = true;
								}
								bool ClickedD = ImGui::CoolCheckbox(TEXT("Shift key"), &Aimkey::bShift);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Shift key (keyboard).");
								}
								if (ClickedD && Aimkey::bShift) {
									Aimkey::bLMouse = false;
									Aimkey::bUniversal = false;
									Aimkey::bRMouse = false;
								}
								else if (ClickedD && !Aimkey::bLMouse && !Aimkey::bUniversal && !Aimkey::bRMouse) {
									Aimkey::bShift = true;
								}
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Aimbot mode"));
							if (ImGui::BeginChild(TEXT("C_AimbotMode_One"), mvec(100, 20))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Memory"), &AimbotMode::bMemory);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Fully flicking memory aimbot. Controllers are supported. Slowness isn't supported.");
								}
								if (ClickedA && AimbotMode::bMemory) {
									AimbotMode::bMouse = false;
								}
								else if (ClickedA && !AimbotMode::bMouse) {
									AimbotMode::bMemory = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_AimbotMode_Two"), mvec(100, 20))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Mouse"), &AimbotMode::bMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("General mouse aimbot. No controllers supported. Slowness is supported.");
								}
								if (ClickedA && AimbotMode::bMouse) {
									AimbotMode::bMemory = false;
								}
								else if (ClickedA && !AimbotMode::bMemory) {
									AimbotMode::bMouse = true;
								}
								ImGui::EndChild();
							}
							ImGui::EndChild();
						}
					}
					if (AimbotPage == 1) { //SMG
						using namespace Options::SMG;
						if (ImGui::BeginChild(TEXT("C_Aimbot_SMG_Tab_One"), mvec(300, 270))) {
							ImGui::Text(TEXT("SMG aimbot config"));
							ImGui::CoolCheckbox(TEXT("Enable"), &bAimbot);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Enable aimbot for SMG's.");
							}
							ImGui::CoolCheckbox(TEXT("Knocked players"), &bKnockedPlayers);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Allow the aimbot to target knocked players.");
							}
							ImGui::CoolCheckbox(TEXT("Visible players"), &bVisibleOnly);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Allow the aimbot to target visible players.");
							}
							ImGui::CoolCheckbox(TEXT("Render FOV"), &bRenderFOV);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Draw a circle showing the aimbot field of view.");
							}
							ImGui::CoolCheckbox(TEXT("Backtrack"), &bBacktrack);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Makes the enemy stuck while aimbotting. [RISK!]");
							}
							ImGui::CoolCheckbox(TEXT("Line to target"), &bLineToTarget);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Draws a line to the targetted player.");
							}
							ImGui::SliderFloat(fAimLineThickness, TEXT("Aimline (t)"), &fAimLineThickness, 0.5f, 5.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Thickness of the aimbot line.");
							}
							ImGui::SliderFloat(fAimbotFOV, TEXT("Field of view"), &fAimbotFOV, 0.f, 360.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Aimbot field of view.");
							}
							ImGui::SliderFloat(fAimbotSmooth, TEXT("Slowness"), &fAimbotSmooth, 0.f, 25.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Speed of the aimbot. The higher, the slower (ONLY Mouse aimbot is supported).");
							}
							ImGui::EndChild();
						} ImGui::SameLine();
						if (ImGui::BeginChild(TEXT("C_Aimbot_SMG_Tab_Two"), mvec(300, 270))) {
							ImGui::Text(TEXT("Target bone"));
							if (ImGui::BeginChild(TEXT("C_Targetbone_One"), mvec(100, 44))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Closest bone"), &AimTarget::bClosestBone);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Closest bone to the targetted player.");
								}
								if (ClickedA && AimTarget::bClosestBone) {
									AimTarget::bHead = false;
									AimTarget::bNeck = false;
									AimTarget::bBody = false;
								}
								else if (ClickedA && !AimTarget::bHead && !AimTarget::bNeck && !AimTarget::bBody) {
									AimTarget::bClosestBone = true;
								}
								bool ClickedC = ImGui::CoolCheckbox(TEXT("Head bone"), &AimTarget::bHead);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Head of targetted player.");
								}
								if (ClickedC && AimTarget::bHead) {
									AimTarget::bClosestBone = false;
									AimTarget::bNeck = false;
									AimTarget::bBody = false;
								}
								else if (ClickedC && !AimTarget::bClosestBone && !AimTarget::bNeck && !AimTarget::bBody) {
									AimTarget::bHead = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Targetbone_Two"), mvec(100, 44))) {
								bool ClickedB = ImGui::CoolCheckbox(TEXT("Neck bone"), &AimTarget::bNeck);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Neck of targetted player.");
								}
								if (ClickedB && AimTarget::bNeck) {
									AimTarget::bHead = false;
									AimTarget::bClosestBone = false;
									AimTarget::bBody = false;
								}
								else if (ClickedB && !AimTarget::bHead && !AimTarget::bClosestBone && !AimTarget::bBody) {
									AimTarget::bNeck = true;
								}
								bool ClickedD = ImGui::CoolCheckbox(TEXT("Body bone"), &AimTarget::bBody);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Body of targetted player.");
								}
								if (ClickedD && AimTarget::bBody) {
									AimTarget::bHead = false;
									AimTarget::bClosestBone = false;
									AimTarget::bNeck = false;
								}
								else if (ClickedD && !AimTarget::bHead && !AimTarget::bClosestBone && !AimTarget::bNeck) {
									AimTarget::bBody = true;
								}
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Keybind"));
							if (ImGui::BeginChild(TEXT("C_Keybind_One"), mvec(100, 44))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Universal"), &Aimkey::bUniversal);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Universal (Active whenever you are aiming, controllers are supported)");
								}
								if (ClickedA && Aimkey::bUniversal) {
									Aimkey::bLMouse = false;
									Aimkey::bRMouse = false;
									Aimkey::bShift = false;
								}
								else if (ClickedA && !Aimkey::bLMouse && !Aimkey::bRMouse && !Aimkey::bShift) {
									Aimkey::bUniversal = true;
								}
								bool ClickedC = ImGui::CoolCheckbox(TEXT("Left mouse"), &Aimkey::bLMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Left mouse button.");
								}
								if (ClickedC && Aimkey::bLMouse) {
									Aimkey::bUniversal = false;
									Aimkey::bRMouse = false;
									Aimkey::bShift = false;
								}
								else if (ClickedC && !Aimkey::bUniversal && !Aimkey::bRMouse && !Aimkey::bShift) {
									Aimkey::bLMouse = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Keybind_Two"), mvec(100, 44))) {
								bool ClickedB = ImGui::CoolCheckbox(TEXT("Right mouse"), &Aimkey::bRMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Right mouse button.");
								}
								if (ClickedB && Aimkey::bRMouse) {
									Aimkey::bLMouse = false;
									Aimkey::bUniversal = false;
									Aimkey::bShift = false;
								}
								else if (ClickedB && !Aimkey::bLMouse && !Aimkey::bUniversal && !Aimkey::bShift) {
									Aimkey::bRMouse = true;
								}
								bool ClickedD = ImGui::CoolCheckbox(TEXT("Shift key"), &Aimkey::bShift);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Shift key (keyboard).");
								}
								if (ClickedD && Aimkey::bShift) {
									Aimkey::bLMouse = false;
									Aimkey::bUniversal = false;
									Aimkey::bRMouse = false;
								}
								else if (ClickedD && !Aimkey::bLMouse && !Aimkey::bUniversal && !Aimkey::bRMouse) {
									Aimkey::bShift = true;
								}
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Aimbot mode"));
							if (ImGui::BeginChild(TEXT("C_AimbotMode_One"), mvec(100, 20))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Memory"), &AimbotMode::bMemory);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Fully flicking memory aimbot. Controllers are supported. Slowness isn't supported.");
								}
								if (ClickedA && AimbotMode::bMemory) {
									AimbotMode::bMouse = false;
								}
								else if (ClickedA && !AimbotMode::bMouse) {
									AimbotMode::bMemory = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_AimbotMode_Two"), mvec(100, 20))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Mouse"), &AimbotMode::bMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("General mouse aimbot. No controllers supported. Slowness is supported.");
								}
								if (ClickedA && AimbotMode::bMouse) {
									AimbotMode::bMemory = false;
								}
								else if (ClickedA && !AimbotMode::bMemory) {
									AimbotMode::bMouse = true;
								}
								ImGui::EndChild();
							}
							ImGui::EndChild();
						}
					}
					if (AimbotPage == 2) { //Shotgun
						using namespace Options::Shotgun;
						if (ImGui::BeginChild(TEXT("C_Aimbot_Shotgun_Tab_One"), mvec(300, 270))) {
							ImGui::Text(TEXT("Shotgun aimbot config"));
							ImGui::CoolCheckbox(TEXT("Enable"), &bAimbot);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Enable aimbot for Shotguns.");
							}
							ImGui::CoolCheckbox(TEXT("Knocked players"), &bKnockedPlayers);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Allow the aimbot to target knocked players.");
							}
							ImGui::CoolCheckbox(TEXT("Visible players"), &bVisibleOnly);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Allow the aimbot to target visible players.");
							}
							ImGui::CoolCheckbox(TEXT("Render FOV"), &bRenderFOV);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Draw a circle showing the aimbot field of view.");
							}
							ImGui::CoolCheckbox(TEXT("Backtrack"), &bBacktrack);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Makes the enemy stuck while aimbotting. [RISK!]");
							}
							ImGui::CoolCheckbox(TEXT("Line to target"), &bLineToTarget);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Draws a line to the targetted player.");
							}
							ImGui::SliderFloat(fAimLineThickness, TEXT("Aimline (t)"), &fAimLineThickness, 0.5f, 5.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Thickness of the aimbot line.");
							}
							ImGui::SliderFloat(fAimbotFOV, TEXT("Field of view"), &fAimbotFOV, 0.f, 360.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Aimbot field of view.");
							}
							ImGui::SliderFloat(fAimbotSmooth, TEXT("Slowness"), &fAimbotSmooth, 0.f, 25.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Speed of the aimbot. The higher, the slower (ONLY Mouse aimbot is supported).");
							}
							ImGui::EndChild();
						} ImGui::SameLine();
						if (ImGui::BeginChild(TEXT("C_Aimbot_Shotgun_Tab_Two"), mvec(300, 270))) {
							ImGui::Text(TEXT("Target bone"));
							if (ImGui::BeginChild(TEXT("C_Targetbone_One"), mvec(100, 44))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Closest bone"), &AimTarget::bClosestBone);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Closest bone to the targetted player.");
								}
								if (ClickedA && AimTarget::bClosestBone) {
									AimTarget::bHead = false;
									AimTarget::bNeck = false;
									AimTarget::bBody = false;
								}
								else if (ClickedA && !AimTarget::bHead && !AimTarget::bNeck && !AimTarget::bBody) {
									AimTarget::bClosestBone = true;
								}
								bool ClickedC = ImGui::CoolCheckbox(TEXT("Head bone"), &AimTarget::bHead);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Head of targetted player.");
								}
								if (ClickedC && AimTarget::bHead) {
									AimTarget::bClosestBone = false;
									AimTarget::bNeck = false;
									AimTarget::bBody = false;
								}
								else if (ClickedC && !AimTarget::bClosestBone && !AimTarget::bNeck && !AimTarget::bBody) {
									AimTarget::bHead = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Targetbone_Two"), mvec(100, 44))) {
								bool ClickedB = ImGui::CoolCheckbox(TEXT("Neck bone"), &AimTarget::bNeck);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Neck of targetted player.");
								}
								if (ClickedB && AimTarget::bNeck) {
									AimTarget::bHead = false;
									AimTarget::bClosestBone = false;
									AimTarget::bBody = false;
								}
								else if (ClickedB && !AimTarget::bHead && !AimTarget::bClosestBone && !AimTarget::bBody) {
									AimTarget::bNeck = true;
								}
								bool ClickedD = ImGui::CoolCheckbox(TEXT("Body bone"), &AimTarget::bBody);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Body of targetted player.");
								}
								if (ClickedD && AimTarget::bBody) {
									AimTarget::bHead = false;
									AimTarget::bClosestBone = false;
									AimTarget::bNeck = false;
								}
								else if (ClickedD && !AimTarget::bHead && !AimTarget::bClosestBone && !AimTarget::bNeck) {
									AimTarget::bBody = true;
								}
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Keybind"));
							if (ImGui::BeginChild(TEXT("C_Keybind_One"), mvec(100, 44))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Universal"), &Aimkey::bUniversal);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Universal (Active whenever you are aiming, controllers are supported)");
								}
								if (ClickedA && Aimkey::bUniversal) {
									Aimkey::bLMouse = false;
									Aimkey::bRMouse = false;
									Aimkey::bShift = false;
								}
								else if (ClickedA && !Aimkey::bLMouse && !Aimkey::bRMouse && !Aimkey::bShift) {
									Aimkey::bUniversal = true;
								}
								bool ClickedC = ImGui::CoolCheckbox(TEXT("Left mouse"), &Aimkey::bLMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Left mouse button.");
								}
								if (ClickedC && Aimkey::bLMouse) {
									Aimkey::bUniversal = false;
									Aimkey::bRMouse = false;
									Aimkey::bShift = false;
								}
								else if (ClickedC && !Aimkey::bUniversal && !Aimkey::bRMouse && !Aimkey::bShift) {
									Aimkey::bLMouse = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Keybind_Two"), mvec(100, 44))) {
								bool ClickedB = ImGui::CoolCheckbox(TEXT("Right mouse"), &Aimkey::bRMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Right mouse button.");
								}
								if (ClickedB && Aimkey::bRMouse) {
									Aimkey::bLMouse = false;
									Aimkey::bUniversal = false;
									Aimkey::bShift = false;
								}
								else if (ClickedB && !Aimkey::bLMouse && !Aimkey::bUniversal && !Aimkey::bShift) {
									Aimkey::bRMouse = true;
								}
								bool ClickedD = ImGui::CoolCheckbox(TEXT("Shift key"), &Aimkey::bShift);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Shift key (keyboard).");
								}
								if (ClickedD && Aimkey::bShift) {
									Aimkey::bLMouse = false;
									Aimkey::bUniversal = false;
									Aimkey::bRMouse = false;
								}
								else if (ClickedD && !Aimkey::bLMouse && !Aimkey::bUniversal && !Aimkey::bRMouse) {
									Aimkey::bShift = true;
								}
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Aimbot mode"));
							if (ImGui::BeginChild(TEXT("C_AimbotMode_One"), mvec(100, 20))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Memory"), &AimbotMode::bMemory);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Fully flicking memory aimbot. Controllers are supported. Slowness isn't supported.");
								}
								if (ClickedA && AimbotMode::bMemory) {
									AimbotMode::bMouse = false;
								}
								else if (ClickedA && !AimbotMode::bMouse) {
									AimbotMode::bMemory = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_AimbotMode_Two"), mvec(100, 20))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Mouse"), &AimbotMode::bMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("General mouse aimbot. No controllers supported. Slowness is supported.");
								}
								if (ClickedA && AimbotMode::bMouse) {
									AimbotMode::bMemory = false;
								}
								else if (ClickedA && !AimbotMode::bMemory) {
									AimbotMode::bMouse = true;
								}
								ImGui::EndChild();
							}
							ImGui::EndChild();
						}
					}
					if (AimbotPage == 3) { //Sniper
						using namespace Options::Sniper;
						if (ImGui::BeginChild(TEXT("C_Aimbot_Sniper_Tab_One"), mvec(300, 270))) {
							ImGui::Text(TEXT("Sniper aimbot config"));
							ImGui::CoolCheckbox(TEXT("Enable"), &bAimbot);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Enable aimbot for Snipers.");
							}
							ImGui::CoolCheckbox(TEXT("Knocked players"), &bKnockedPlayers);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Allow the aimbot to target knocked players.");
							}
							ImGui::CoolCheckbox(TEXT("Visible players"), &bVisibleOnly);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Allow the aimbot to target visible players.");
							}
							ImGui::CoolCheckbox(TEXT("Render FOV"), &bRenderFOV);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Draw a circle showing the aimbot field of view.");
							}
							ImGui::CoolCheckbox(TEXT("Backtrack"), &bBacktrack);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Makes the enemy stuck while aimbotting. [RISK!]");
							}
							ImGui::CoolCheckbox(TEXT("Line to target"), &bLineToTarget);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Draws a line to the targetted player.");
							}
							ImGui::SliderFloat(fAimLineThickness, TEXT("Aimline (t)"), &fAimLineThickness, 0.5f, 5.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Thickness of the aimbot line.");
							}
							ImGui::SliderFloat(fAimbotFOV, TEXT("Field of view"), &fAimbotFOV, 0.f, 360.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Aimbot field of view.");
							}
							ImGui::SliderFloat(fAimbotSmooth, TEXT("Slowness"), &fAimbotSmooth, 0.f, 25.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Speed of the aimbot. The higher, the slower (ONLY Mouse aimbot is supported).");
							}
							ImGui::EndChild();
						} ImGui::SameLine();
						if (ImGui::BeginChild(TEXT("C_Aimbot_Sniper_Tab_Two"), mvec(300, 270))) {
							ImGui::Text(TEXT("Target bone"));
							if (ImGui::BeginChild(TEXT("C_Targetbone_One"), mvec(100, 44))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Closest bone"), &AimTarget::bClosestBone);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Closest bone to the targetted player.");
								}
								if (ClickedA && AimTarget::bClosestBone) {
									AimTarget::bHead = false;
									AimTarget::bNeck = false;
									AimTarget::bBody = false;
								}
								else if (ClickedA && !AimTarget::bHead && !AimTarget::bNeck && !AimTarget::bBody) {
									AimTarget::bClosestBone = true;
								}
								bool ClickedC = ImGui::CoolCheckbox(TEXT("Head bone"), &AimTarget::bHead);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Head of targetted player.");
								}
								if (ClickedC && AimTarget::bHead) {
									AimTarget::bClosestBone = false;
									AimTarget::bNeck = false;
									AimTarget::bBody = false;
								}
								else if (ClickedC && !AimTarget::bClosestBone && !AimTarget::bNeck && !AimTarget::bBody) {
									AimTarget::bHead = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Targetbone_Two"), mvec(100, 44))) {
								bool ClickedB = ImGui::CoolCheckbox(TEXT("Neck bone"), &AimTarget::bNeck);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Neck of targetted player.");
								}
								if (ClickedB && AimTarget::bNeck) {
									AimTarget::bHead = false;
									AimTarget::bClosestBone = false;
									AimTarget::bBody = false;
								}
								else if (ClickedB && !AimTarget::bHead && !AimTarget::bClosestBone && !AimTarget::bBody) {
									AimTarget::bNeck = true;
								}
								bool ClickedD = ImGui::CoolCheckbox(TEXT("Body bone"), &AimTarget::bBody);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Body of targetted player.");
								}
								if (ClickedD && AimTarget::bBody) {
									AimTarget::bHead = false;
									AimTarget::bClosestBone = false;
									AimTarget::bNeck = false;
								}
								else if (ClickedD && !AimTarget::bHead && !AimTarget::bClosestBone && !AimTarget::bNeck) {
									AimTarget::bBody = true;
								}
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Keybind"));
							if (ImGui::BeginChild(TEXT("C_Keybind_One"), mvec(100, 44))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Universal"), &Aimkey::bUniversal);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Universal (Active whenever you are aiming, controllers are supported)");
								}
								if (ClickedA && Aimkey::bUniversal) {
									Aimkey::bLMouse = false;
									Aimkey::bRMouse = false;
									Aimkey::bShift = false;
								}
								else if (ClickedA && !Aimkey::bLMouse && !Aimkey::bRMouse && !Aimkey::bShift) {
									Aimkey::bUniversal = true;
								}
								bool ClickedC = ImGui::CoolCheckbox(TEXT("Left mouse"), &Aimkey::bLMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Left mouse button.");
								}
								if (ClickedC && Aimkey::bLMouse) {
									Aimkey::bUniversal = false;
									Aimkey::bRMouse = false;
									Aimkey::bShift = false;
								}
								else if (ClickedC && !Aimkey::bUniversal && !Aimkey::bRMouse && !Aimkey::bShift) {
									Aimkey::bLMouse = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Keybind_Two"), mvec(100, 44))) {
								bool ClickedB = ImGui::CoolCheckbox(TEXT("Right mouse"), &Aimkey::bRMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Right mouse button.");
								}
								if (ClickedB && Aimkey::bRMouse) {
									Aimkey::bLMouse = false;
									Aimkey::bUniversal = false;
									Aimkey::bShift = false;
								}
								else if (ClickedB && !Aimkey::bLMouse && !Aimkey::bUniversal && !Aimkey::bShift) {
									Aimkey::bRMouse = true;
								}
								bool ClickedD = ImGui::CoolCheckbox(TEXT("Shift key"), &Aimkey::bShift);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Shift key (keyboard).");
								}
								if (ClickedD && Aimkey::bShift) {
									Aimkey::bLMouse = false;
									Aimkey::bUniversal = false;
									Aimkey::bRMouse = false;
								}
								else if (ClickedD && !Aimkey::bLMouse && !Aimkey::bUniversal && !Aimkey::bRMouse) {
									Aimkey::bShift = true;
								}
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Aimbot mode"));
							if (ImGui::BeginChild(TEXT("C_AimbotMode_One"), mvec(100, 20))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Memory"), &AimbotMode::bMemory);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Fully flicking memory aimbot. Controllers are supported. Slowness isn't supported.");
								}
								if (ClickedA && AimbotMode::bMemory) {
									AimbotMode::bMouse = false;
								}
								else if (ClickedA && !AimbotMode::bMouse) {
									AimbotMode::bMemory = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_AimbotMode_Two"), mvec(100, 20))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Mouse"), &AimbotMode::bMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("General mouse aimbot. No controllers supported. Slowness is supported.");
								}
								if (ClickedA && AimbotMode::bMouse) {
									AimbotMode::bMemory = false;
								}
								else if (ClickedA && !AimbotMode::bMemory) {
									AimbotMode::bMouse = true;
								}
								ImGui::EndChild();
							}
							ImGui::EndChild();
						}
					}
					if (AimbotPage == 4) { //Other weapons
						using namespace Options::OtherWeapons;
						if (ImGui::BeginChild(TEXT("C_Aimbot_OtherWeapons_Tab_One"), mvec(300, 270))) {
							ImGui::Text(TEXT("Aimbot config"));
							ImGui::CoolCheckbox(TEXT("Enable"), &bAimbot);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Enable aimbot for all other weapons.");
							}
							ImGui::CoolCheckbox(TEXT("Knocked players"), &bKnockedPlayers);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Allow the aimbot to target knocked players.");
							}
							ImGui::CoolCheckbox(TEXT("Visible players"), &bVisibleOnly);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Allow the aimbot to target visible players.");
							}
							ImGui::CoolCheckbox(TEXT("Render FOV"), &bRenderFOV);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Draw a circle showing the aimbot field of view.");
							}
							ImGui::CoolCheckbox(TEXT("Backtrack"), &bBacktrack);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Makes the enemy stuck while aimbotting. [RISK!]");
							}
							ImGui::CoolCheckbox(TEXT("Line to target"), &bLineToTarget);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Draws a line to the targetted player.");
							}
							ImGui::SliderFloat(fAimLineThickness, TEXT("Aimline (t)"), &fAimLineThickness, 0.5f, 5.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Thickness of the aimbot line.");
							}
							ImGui::SliderFloat(fAimbotFOV, TEXT("Field of view"), &fAimbotFOV, 0.f, 360.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Aimbot field of view.");
							}
							ImGui::SliderFloat(fAimbotSmooth, TEXT("Slowness"), &fAimbotSmooth, 0.f, 25.f);
							if (ImGui::IsItemHovered()) {
								TestText = TEXT("Speed of the aimbot. The higher, the slower (ONLY Mouse aimbot is supported).");
							}
							ImGui::EndChild();
						} ImGui::SameLine();
						if (ImGui::BeginChild(TEXT("C_Aimbot_OtherWeapons_Tab_Two"), mvec(300, 270))) {
							ImGui::Text(TEXT("Target bone"));
							if (ImGui::BeginChild(TEXT("C_Targetbone_One"), mvec(100, 44))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Closest bone"), &AimTarget::bClosestBone);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Closest bone to the targetted player.");
								}
								if (ClickedA && AimTarget::bClosestBone) {
									AimTarget::bHead = false;
									AimTarget::bNeck = false;
									AimTarget::bBody = false;
								}
								else if (ClickedA && !AimTarget::bHead && !AimTarget::bNeck && !AimTarget::bBody) {
									AimTarget::bClosestBone = true;
								}
								bool ClickedC = ImGui::CoolCheckbox(TEXT("Head bone"), &AimTarget::bHead);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Head of targetted player.");
								}
								if (ClickedC && AimTarget::bHead) {
									AimTarget::bClosestBone = false;
									AimTarget::bNeck = false;
									AimTarget::bBody = false;
								}
								else if (ClickedC && !AimTarget::bClosestBone && !AimTarget::bNeck && !AimTarget::bBody) {
									AimTarget::bHead = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Targetbone_Two"), mvec(100, 44))) {
								bool ClickedB = ImGui::CoolCheckbox(TEXT("Neck bone"), &AimTarget::bNeck);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Neck of targetted player.");
								}
								if (ClickedB && AimTarget::bNeck) {
									AimTarget::bHead = false;
									AimTarget::bClosestBone = false;
									AimTarget::bBody = false;
								}
								else if (ClickedB && !AimTarget::bHead && !AimTarget::bClosestBone && !AimTarget::bBody) {
									AimTarget::bNeck = true;
								}
								bool ClickedD = ImGui::CoolCheckbox(TEXT("Body bone"), &AimTarget::bBody);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Body of targetted player.");
								}
								if (ClickedD && AimTarget::bBody) {
									AimTarget::bHead = false;
									AimTarget::bClosestBone = false;
									AimTarget::bNeck = false;
								}
								else if (ClickedD && !AimTarget::bHead && !AimTarget::bClosestBone && !AimTarget::bNeck) {
									AimTarget::bBody = true;
								}
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Keybind"));
							if (ImGui::BeginChild(TEXT("C_Keybind_One"), mvec(100, 44))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Universal"), &Aimkey::bUniversal);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Universal (Active whenever you are aiming, controllers are supported)");
								}
								if (ClickedA && Aimkey::bUniversal) {
									Aimkey::bLMouse = false;
									Aimkey::bRMouse = false;
									Aimkey::bShift = false;
								}
								else if (ClickedA && !Aimkey::bLMouse && !Aimkey::bRMouse && !Aimkey::bShift) {
									Aimkey::bUniversal = true;
								}
								bool ClickedC = ImGui::CoolCheckbox(TEXT("Left mouse"), &Aimkey::bLMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Left mouse button.");
								}
								if (ClickedC && Aimkey::bLMouse) {
									Aimkey::bUniversal = false;
									Aimkey::bRMouse = false;
									Aimkey::bShift = false;
								}
								else if (ClickedC && !Aimkey::bUniversal && !Aimkey::bRMouse && !Aimkey::bShift) {
									Aimkey::bLMouse = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Keybind_Two"), mvec(100, 44))) {
								bool ClickedB = ImGui::CoolCheckbox(TEXT("Right mouse"), &Aimkey::bRMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Right mouse button.");
								}
								if (ClickedB && Aimkey::bRMouse) {
									Aimkey::bLMouse = false;
									Aimkey::bUniversal = false;
									Aimkey::bShift = false;
								}
								else if (ClickedB && !Aimkey::bLMouse && !Aimkey::bUniversal && !Aimkey::bShift) {
									Aimkey::bRMouse = true;
								}
								bool ClickedD = ImGui::CoolCheckbox(TEXT("Shift key"), &Aimkey::bShift);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Keybind: Shift key (keyboard).");
								}
								if (ClickedD && Aimkey::bShift) {
									Aimkey::bLMouse = false;
									Aimkey::bUniversal = false;
									Aimkey::bRMouse = false;
								}
								else if (ClickedD && !Aimkey::bLMouse && !Aimkey::bUniversal && !Aimkey::bRMouse) {
									Aimkey::bShift = true;
								}
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Aimbot mode"));
							if (ImGui::BeginChild(TEXT("C_AimbotMode_One"), mvec(100, 20))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Memory"), &AimbotMode::bMemory);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Fully flicking memory aimbot. Controllers are supported. Slowness isn't supported.");
								}
								if (ClickedA && AimbotMode::bMemory) {
									AimbotMode::bMouse = false;
								}
								else if (ClickedA && !AimbotMode::bMouse) {
									AimbotMode::bMemory = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_AimbotMode_Two"), mvec(100, 20))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Mouse"), &AimbotMode::bMouse);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("General mouse aimbot. No controllers supported. Slowness is supported.");
								}
								if (ClickedA && AimbotMode::bMouse) {
									AimbotMode::bMemory = false;
								}
								else if (ClickedA && !AimbotMode::bMemory) {
									AimbotMode::bMouse = true;
								}
								ImGui::EndChild();
							}
							ImGui::EndChild();
						}
					}
					ImGui::EndChild();
				}
				/*bool bAimbot = false;
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
		}*/
			}
		}

		//Visuals
		{
			if (MenuTab == 1) {
				if (ImGui::BeginChild(TEXT("C_Visuals_Tab"), mvec(650, 340))) {
					ImGui::Text(TEXT(""));

					if (bShowVisualButtons)
					{
						if (VisualPage == 0) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Player ESP"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Player ESP"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							VisualPage = 0;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("Player Wallhack.");
						}

						ImGui::SameLine();
						if (VisualPage == 1) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Environment"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Environment"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							VisualPage = 1;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("World (gun, loot, item) Wallhack.");
						}

						ImGui::SameLine();
						if (VisualPage == 2) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Miscellaneous"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Miscellaneous"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							VisualPage = 2;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("Miscellaneous cheat options.");
						}

						ImGui::SameLine();
						if (VisualPage == 3) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Colors"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Colors"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							VisualPage = 3;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("Customize the cheat's colors.");
						}

						ImGui::SameLine();
						if (VisualPage == 4) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Radar"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Radar"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							VisualPage = 4;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("Set the cheat's render mode. This includes streamproof, colors saturation, etc.");
						}
					}

					if (VisualPage == 0) {
						

							ImGui::Text(TEXT("Visuals"));
							ImGui::CoolCheckbox(TEXT("Character"), &bCharacters);
							ImGui::CoolCheckbox(TEXT("Skeleton"), &bSkeleton);
							ImGui::CoolCheckbox(TEXT("Snapline"), &bSnapline);
							ImGui::CoolCheckbox(TEXT("View angle"), &bViewAngles);
							ImGui::CoolCheckbox(TEXT("Display distance"), &bPlayerDistance);
							ImGui::CoolCheckbox(TEXT("Ammo count"), &bAmmoCount);
							ImGui::CoolCheckbox(TEXT("Current weapon"), &bCurrentWeapon);
							ImGui::CoolCheckbox(TEXT("Player information"), &bPlayerInfo);
							ImGui::SliderFloat(fMaxPlayerDistance, TEXT("Distance"), &fMaxPlayerDistance, 25.f, 225.f);
							ImGui::EndChild();
						} ImGui::SameLine();
						if (ImGui::BeginChild(TEXT("C_Player_Tab_Two"), mvec(300, 270))) {
							ImGui::Text(TEXT("Font"));
							if (ImGui::BeginChild(TEXT("C_Font_One"), mvec(100, 68))) {
								auto ClickedA = ImGui::CoolCheckbox(TEXT("Arial"), &PlayerFonts::bArial);
								if (ClickedA && PlayerFonts::bArial) {
									PlayerFonts::bRajdhani = false;
									PlayerFonts::bFortniteFont = false;
									PlayerFonts::bGTAFont = false;
									PlayerFonts::bStandardFont = false;
									PlayerFonts::bVerdana = false;
								}
								else if (ClickedA && !PlayerFonts::bRajdhani && !PlayerFonts::bVerdana && !PlayerFonts::bFortniteFont && !PlayerFonts::bGTAFont && !PlayerFonts::bStandardFont)
									PlayerFonts::bArial = true;
								auto ClickedB = ImGui::CoolCheckbox(TEXT("Rajdhani"), &PlayerFonts::bRajdhani);
								if (ClickedB && PlayerFonts::bRajdhani) {
									PlayerFonts::bArial = false;
									PlayerFonts::bFortniteFont = false;
									PlayerFonts::bGTAFont = false;
									PlayerFonts::bStandardFont = false;
									PlayerFonts::bVerdana = false;
								}
								else if (ClickedB && !PlayerFonts::bArial && !PlayerFonts::bVerdana && !PlayerFonts::bFortniteFont && !PlayerFonts::bGTAFont && !PlayerFonts::bStandardFont)
									PlayerFonts::bRajdhani = true;
								auto ClickedC = ImGui::CoolCheckbox(TEXT("Verdana"), &PlayerFonts::bVerdana);
								if (ClickedC && PlayerFonts::bVerdana) {
									PlayerFonts::bArial = false;
									PlayerFonts::bFortniteFont = false;
									PlayerFonts::bGTAFont = false;
									PlayerFonts::bStandardFont = false;
									PlayerFonts::bRajdhani = false;
								}
								else if (ClickedC && !PlayerFonts::bArial && !PlayerFonts::bRajdhani && !PlayerFonts::bFortniteFont && !PlayerFonts::bGTAFont && !PlayerFonts::bStandardFont)
									PlayerFonts::bVerdana = true;
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Font_Two"), mvec(120, 68))) {
								auto ClickedD = ImGui::CoolCheckbox(TEXT("Fortnite"), &PlayerFonts::bFortniteFont);
								if (ClickedD && PlayerFonts::bFortniteFont) {
									PlayerFonts::bArial = false;
									PlayerFonts::bVerdana = false;
									PlayerFonts::bGTAFont = false;
									PlayerFonts::bStandardFont = false;
									PlayerFonts::bRajdhani = false;
								}
								else if (ClickedD && !PlayerFonts::bArial && !PlayerFonts::bRajdhani && !PlayerFonts::bVerdana && !PlayerFonts::bGTAFont && !PlayerFonts::bStandardFont)
									PlayerFonts::bFortniteFont = true;
								auto ClickedE = ImGui::CoolCheckbox(TEXT("GTA"), &PlayerFonts::bGTAFont);
								if (ClickedE && PlayerFonts::bGTAFont) {
									PlayerFonts::bArial = false;
									PlayerFonts::bVerdana = false;
									PlayerFonts::bFortniteFont = false;
									PlayerFonts::bStandardFont = false;
									PlayerFonts::bRajdhani = false;
								}
								else if (ClickedE && !PlayerFonts::bArial && !PlayerFonts::bRajdhani && !PlayerFonts::bVerdana && !PlayerFonts::bFortniteFont && !PlayerFonts::bStandardFont)
									PlayerFonts::bGTAFont = true;
								auto ClickedF = ImGui::CoolCheckbox(TEXT("Standard"), &PlayerFonts::bStandardFont);
								if (ClickedF && PlayerFonts::bStandardFont) {
									PlayerFonts::bArial = false;
									PlayerFonts::bVerdana = false;
									PlayerFonts::bFortniteFont = false;
									PlayerFonts::bGTAFont = false;
									PlayerFonts::bRajdhani = false;
								}
								else if (ClickedF && !PlayerFonts::bArial && !PlayerFonts::bRajdhani && !PlayerFonts::bVerdana && !PlayerFonts::bFortniteFont && !PlayerFonts::bGTAFont)
									PlayerFonts::bStandardFont = true;
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Snapline start"));
							if (ImGui::BeginChild(TEXT("C_PlayerESP_SnaplineMode_One"), mvec(100, 20))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Bottom"), &Options::SnaplineStart::bBottom);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("The player snapline will begin from the bottom of your screen.");
								}
								if (ClickedA && Options::SnaplineStart::bBottom) {
									Options::SnaplineStart::bTop = false;
								}
								else if (ClickedA && !Options::SnaplineStart::bTop) {
									Options::SnaplineStart::bBottom = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_PlayerESP_SnaplineMode_Two"), mvec(100, 20))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Top"), &Options::SnaplineStart::bTop);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("The player snapline will begin from the top of your screen.");
								}
								if (ClickedA && Options::SnaplineStart::bTop) {
									Options::SnaplineStart::bBottom = false;
								}
								else if (ClickedA && !Options::SnaplineStart::bBottom) {
									Options::SnaplineStart::bTop = true;
								}
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Character mode"));
							if (ImGui::BeginChild(TEXT("C_PlayerESP_BoxMode_One"), mvec(100, 44))) {
								auto clickedH = ImGui::CoolCheckbox(TEXT("3D"), &Options::CharacterModes::b3D);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Character box mode: 3D Box around all players.");
								}
								if (clickedH && Options::CharacterModes::b3D) {
									Options::CharacterModes::b2D = false;
									Options::CharacterModes::bCorner = false;

								}
								else if (clickedH && !Options::CharacterModes::bCorner && !Options::CharacterModes::b2D && !Options::CharacterModes::bCorner) {
									Options::CharacterModes::b3D = true;
								}
								auto clickedD = ImGui::CoolCheckbox(TEXT("2D Cornered"), &Options::CharacterModes::bCorner);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Character box mode: Draws a cornered rectangle on all players.");
								}
								if (clickedD && Options::CharacterModes::bCorner) {
									Options::CharacterModes::b3D = false;
									Options::CharacterModes::b2D = false;
								}
								else if (clickedD && !Options::CharacterModes::b3D && !Options::CharacterModes::b2D) {
									Options::CharacterModes::bCorner = true;
								}

								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_PlayerESP_BoxMode_Two"), mvec(100, 44))) {
								auto clickedB = ImGui::CoolCheckbox(TEXT("2D Rectangle"), &Options::CharacterModes::b2D);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Character box mode: Draws a rectangle on all players.");
								}
								if (clickedB && Options::CharacterModes::b2D) {
									Options::CharacterModes::b3D = false;
									Options::CharacterModes::bCorner = false;

								}
								else if (clickedB && !Options::CharacterModes::b3D && !Options::CharacterModes::bCorner) {
									Options::CharacterModes::b2D = true;
								}
								ImGui::CoolCheckbox(TEXT("2D Filled"), &Options::CharacterModes::bFill2DBox);
								if (ImGui::IsItemHovered()) {
									TestText = TEXT("Fills the box with a color of your choice. This only supports 'Rectangle' and 'Corner'.");
								}
								ImGui::EndChild();
							}
							ImGui::Text(TEXT("Text mode"));
							if (ImGui::BeginChild(TEXT("C_PlayerESP_TextMode_One"), mvec(100, 20))) {
								ImGui::CoolCheckbox(TEXT("Outlined"), &Options::PlayerFeatures::OutlinedText);
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_PlayerESP_TextMode_Two"), mvec(100, 20))) {
								ImGui::CoolCheckbox(TEXT("Background"), &Options::PlayerFeatures::TextBackground);
								ImGui::EndChild();
							}
							ImGui::EndChild();
						}
					}
					else if (VisualPage == 1) {
						if (ImGui::BeginChild(TEXT("C_Environment_Tab_One"), mvec(300, 270))) {
							ImGui::Text(TEXT("Visuals"));
							ImGui::CoolCheckbox(TEXT("Items & Loot"), &bItems);
							ImGui::CoolCheckbox(TEXT("Loot crates"), &bChest);
							ImGui::CoolCheckbox(TEXT("Vehicles"), &bVehicles);
							ImGui::CoolCheckbox(TEXT("Ammo boxes"), &bAmmoBox);
							ImGui::CoolCheckbox(TEXT("Fishing spots"), &bFloppaSpawns);
							ImGui::CoolCheckbox(TEXT("Shield sources"), &bShieldSources);
							ImGui::SliderFloat(fMaxItemDistance, TEXT("Distance"), &fMaxItemDistance, 25.f, 225.f);
							//ImGui::CoolCheckbox(TEXT("Supply drops (not working)"), &bSupplyDrop);
							//ImGui::CoolCheckbox(TEXT("LLama (not working)"), &bLLama);

							ImGui::EndChild();
						} ImGui::SameLine();

						if (ImGui::BeginChild(TEXT("C_Environment_Tab_Two"), mvec(300, 270))) {
							ImGui::Text(TEXT("Font"));
							if (ImGui::BeginChild(TEXT("C_Font_One"), mvec(100, 68))) {
								auto ClickedA = ImGui::CoolCheckbox(TEXT("Arial"), &ItemFonts::bArial);
								if (ClickedA && ItemFonts::bArial) {
									ItemFonts::bRajdhani = false;
									ItemFonts::bFortniteFont = false;
									ItemFonts::bGTAFont = false;
									ItemFonts::bStandardFont = false;
									ItemFonts::bVerdana = false;
								}
								else if (ClickedA && !ItemFonts::bRajdhani && !ItemFonts::bVerdana && !ItemFonts::bFortniteFont && !ItemFonts::bGTAFont && !ItemFonts::bStandardFont)
									ItemFonts::bArial = true;
								auto ClickedB = ImGui::CoolCheckbox(TEXT("Rajdhani"), &ItemFonts::bRajdhani);
								if (ClickedB && ItemFonts::bRajdhani) {
									ItemFonts::bArial = false;
									ItemFonts::bFortniteFont = false;
									ItemFonts::bGTAFont = false;
									ItemFonts::bStandardFont = false;
									ItemFonts::bVerdana = false;
								}
								else if (ClickedB && !ItemFonts::bArial && !ItemFonts::bVerdana && !ItemFonts::bFortniteFont && !ItemFonts::bGTAFont && !ItemFonts::bStandardFont)
									ItemFonts::bRajdhani = true;
								auto ClickedC = ImGui::CoolCheckbox(TEXT("Verdana"), &ItemFonts::bVerdana);
								if (ClickedC && ItemFonts::bVerdana) {
									ItemFonts::bArial = false;
									ItemFonts::bFortniteFont = false;
									ItemFonts::bGTAFont = false;
									ItemFonts::bStandardFont = false;
									ItemFonts::bRajdhani = false;
								}
								else if (ClickedC && !ItemFonts::bArial && !ItemFonts::bRajdhani && !ItemFonts::bFortniteFont && !ItemFonts::bGTAFont && !ItemFonts::bStandardFont)
									ItemFonts::bVerdana = true;
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Font_Two"), mvec(120, 68))) {
								auto ClickedD = ImGui::CoolCheckbox(TEXT("Fortnite"), &ItemFonts::bFortniteFont);
								if (ClickedD && ItemFonts::bFortniteFont) {
									ItemFonts::bArial = false;
									ItemFonts::bVerdana = false;
									ItemFonts::bGTAFont = false;
									ItemFonts::bStandardFont = false;
									ItemFonts::bRajdhani = false;
								}
								else if (ClickedD && !ItemFonts::bArial && !ItemFonts::bRajdhani && !ItemFonts::bVerdana && !ItemFonts::bGTAFont && !ItemFonts::bStandardFont)
									ItemFonts::bFortniteFont = true;
								auto ClickedE = ImGui::CoolCheckbox(TEXT("GTA"), &ItemFonts::bGTAFont);
								if (ClickedE && ItemFonts::bGTAFont) {
									ItemFonts::bArial = false;
									ItemFonts::bVerdana = false;
									ItemFonts::bFortniteFont = false;
									ItemFonts::bStandardFont = false;
									ItemFonts::bRajdhani = false;
								}
								else if (ClickedE && !ItemFonts::bArial && !ItemFonts::bRajdhani && !ItemFonts::bVerdana && !ItemFonts::bFortniteFont && !ItemFonts::bStandardFont)
									ItemFonts::bGTAFont = true;
								auto ClickedF = ImGui::CoolCheckbox(TEXT("Standard"), &ItemFonts::bStandardFont);
								if (ClickedF && ItemFonts::bStandardFont) {
									ItemFonts::bArial = false;
									ItemFonts::bVerdana = false;
									ItemFonts::bFortniteFont = false;
									ItemFonts::bGTAFont = false;
									ItemFonts::bRajdhani = false;
								}
								else if (ClickedF && !ItemFonts::bArial && !ItemFonts::bRajdhani && !ItemFonts::bVerdana && !ItemFonts::bFortniteFont && !ItemFonts::bGTAFont)
									ItemFonts::bStandardFont = true;
								ImGui::EndChild();
							}

							ImGui::Text(TEXT("Loot rarity"));
							if (ImGui::BeginChild(TEXT("C_LootRarity_One"), mvec(100, 68))) {
								ImGui::CoolCheckbox(TEXT("Common"), &ItemTiers::bCommon);
								ImGui::CoolCheckbox(TEXT("Uncommon"), &ItemTiers::bUncommon);
								ImGui::CoolCheckbox(TEXT("Rare"), &ItemTiers::bRare);
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_LootRarity_Two"), mvec(120, 68))) {
								ImGui::CoolCheckbox(TEXT("Epic"), &ItemTiers::bEpic);
								ImGui::CoolCheckbox(TEXT("Legendary"), &ItemTiers::bLegendary);
								ImGui::CoolCheckbox(TEXT("Mythic"), &ItemTiers::bMythic);
								ImGui::EndChild();
							}

							ImGui::Text(TEXT("Customization"));
							if (ImGui::BeginChild(TEXT("C_Customization_One"), mvec(100, 44))) {
								ImGui::CoolCheckbox(TEXT("Corner box"), &ItemFeatures::bCornerBox);
								ImGui::CoolCheckbox(TEXT("Snapline"), &ItemFeatures::bSnapline);
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Customization_Two"), mvec(120, 44))) {
								ImGui::CoolCheckbox(TEXT("Outlined text"), &ItemFeatures::bOutline);
								ImGui::CoolCheckbox(TEXT("Display distance"), &ItemFeatures::bDistance);
								ImGui::EndChild();
							}
							ImGui::EndChild();
						}
					}
					else if (VisualPage == 3) {
						auto flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoBorder | ImGuiColorEditFlags_NoTooltip |
							ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoOptions;
						ImGui::BeginChild(TEXT("C_PlayerColor_Tab_One"), mvec(150, 280));
						ImGui::Text(TEXT("Visible player"));
						ImGui::ColorEdit4(TEXT("Box"), Options::PlayerColor::BoxVisible, flags);
						ImGui::ColorEdit4(TEXT("Skeleton"), Options::PlayerColor::SkeletonVisible, flags);
						ImGui::ColorEdit4(TEXT("Snapline"), Options::PlayerColor::SnaplineVisible, flags);
						ImGui::ColorEdit4(TEXT("Top text"), Options::PlayerColor::TopTextVisible, flags);
						ImGui::ColorEdit4(TEXT("Bottom text"), Options::PlayerColor::BottomTextVisible, flags);

						ImGui::Text(TEXT("Not visible player"));
						ImGui::ColorEdit4(TEXT("Box "), Options::PlayerColor::BoxNotVisible, flags);
						ImGui::ColorEdit4(TEXT("Skeleton "), Options::PlayerColor::SkeletonNotVisible, flags);
						ImGui::ColorEdit4(TEXT("Snapline "), Options::PlayerColor::SnaplineNotVisible, flags);
						ImGui::ColorEdit4(TEXT("Top text "), Options::PlayerColor::TopTextNotVisible, flags);
						ImGui::ColorEdit4(TEXT("Bottom text "), Options::PlayerColor::BottomTextNotVisible, flags);
						ImGui::EndChild();
					}
					if (VisualPage == 4) {
						ImGui::Text(TEXT(""));
						if (ImGui::BeginChild(TEXT("C_Radar_Tab_One"), mvec(300, 255))) {
							ImGui::Text(TEXT("Radar options"));
							ImGui::CoolCheckbox(TEXT("Radar"), &bRadar);
							ImGui::CoolCheckbox(TEXT("Display players"), &bRadarDisplayPlayers);
							ImGui::CoolCheckbox(TEXT("Display loot"), &bRadarDisplayLoot);
							ImGui::CoolCheckbox(TEXT("Outlined"), &bRadarOutline);
							ImGui::CoolCheckbox(TEXT("Line of sight"), &bShowLineOfSight);
							ImGui::CoolCheckbox(TEXT("Show distance"), &bUseDistanceText);
							ImGui::SliderFloat(fRadarRange, TEXT("Range"), &fRadarRange, 7.f, 50.f);
							ImGui::SliderFloat(fPositionX, TEXT("Mx"), &fPositionX, 1.f, (float)(CenterX * 2));
							ImGui::SliderFloat(fPositionY, TEXT("My"), &fPositionY, 1.f, (float)(CenterY * 2));
							ImGui::EndChild();
						} ImGui::SameLine();
						if (ImGui::BeginChild(TEXT("C_Radar_Tab_Two"), mvec(300, 255))) {
							ImGui::Text(TEXT("General"));
							ImGui::CoolCheckbox(TEXT("Include local player"), &bShowLocalPlayer);
							ImGui::SliderFloat(fSize, TEXT("Size"), &fSize, 1.f, 700);
							ImGui::SliderFloat(fTransparency, TEXT("Transparency"), &fTransparency, 1.f, 255.f);
							ImGui::Text(TEXT("Radar style"));
							if (ImGui::BeginChild(TEXT("C_Radar_Style_One"), mvec(100, 22))) {
								bool ClickedA = ImGui::CoolCheckbox(TEXT("Rectangle"), &bRectangle);
								if (ClickedA && bRectangle) {
									bCircle = false;
								}
								else if (ClickedA && !bCircle) {
									bRectangle = true;
								}
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_Radar_Style_Two"), mvec(100, 22))) {
								bool ClickedC = ImGui::CoolCheckbox(TEXT("Circle"), &bCircle);
								if (ClickedC && bCircle) {
									bRectangle = false;
								}
								else if (ClickedC && !bCircle) {
									bCircle = true;
								}
								ImGui::EndChild();
							}
							ImGui::EndChild();
						}

						/*ImGui::CoolCheckbox(TEXT("Enable radar"), &bRadar);
						ImGui::CoolCheckbox(TEXT("show lineofsight"), &bShowLineOfSight);
						ImGui::CoolCheckbox(TEXT("radar sex outline"), &bRadarOutline);
						ImGui::CoolCheckbox(TEXT("show distance kekw"), &bUseDistanceText);
						ImGui::CoolCheckbox(TEXT("display players"), &bRadarDisplayPlayers);
						ImGui::CoolCheckbox(TEXT("display loot"), &bRadarDisplayLoot);
						ImGui::SliderFloat(fTransparency, TEXT("transgender"), &fTransparency, 1.f, 255.f);
						ImGui::SliderFloat(fRadarRange, TEXT("rangeee"), &fRadarRange, 7000.f, 50000.f);
						ImGui::SliderFloat(fPositionX, TEXT("PosX"), &fPositionX, 1.f, 1920);
						ImGui::SliderFloat(fPositionY, TEXT("PosY"), &fPositionY, 1.f, 1080);
						ImGui::SliderFloat(fSize, TEXT("Size"), &fSize, 1.f, 800.f);*/


						/*bool bRadar = true;
	bool bCircle = true;
	bool bRectangle = false;
	bool bUseTeamColor = true;
	bool bUseVisibleColor = false;
	bool bShowLocalPlayer = false;
	bool bShowLineOfSight = false;
	bool bShowLoot = false;
	float fPositionX = 50.f;
	float fPositionY = 50.f;
	float fSize = 100.f;
	bool fTransparency = 0.8f;
	float fRadarRange = 8000.f;*/
					}
					ImGui::EndChild();
				}
			}
		}

		//Exploits
		{
			if (MenuTab == 2) {
				if (ImGui::BeginChild(TEXT("C_Exploits_Tab"), mvec(650, 340))) {
					ImGui::Text(TEXT(""));
					ImGui::Separator();
					if (ImGui::BeginChild(TEXT("C_Page_One"), mvec(300, 310))) {
						ImGui::Text(TEXT("Exploits (1)"));
						ImGui::CoolCheckbox(TEXT("Instant actions"), &bInstaActions);
						ImGui::CoolCheckbox(TEXT("Instant reboot"), &bInstaReboot);
						ImGui::CoolCheckbox(TEXT("Instant revive"), &bInstaRes);
						ImGui::CoolCheckbox(TEXT("Camera FOV changer"), &bFovChanger);
						ImGui::CoolCheckbox(TEXT("Speedhack"), &bSpeedHack);
						ImGui::CoolCheckbox(TEXT("Full auto"), &bFullAuto);
						ImGui::CoolCheckbox(TEXT("Boat boost"), &bBoatBoost);
						ImGui::CoolCheckbox(TEXT("Airstuck"), &bAirstuck);
						ImGui::CoolCheckbox(TEXT("Allow ADS"), &bAllowAds);
						ImGui::CoolCheckbox(TEXT("Fast weapons"), &bFastWeapons);
						ImGui::CoolCheckbox(TEXT("Spinbot"), &bSpinbot);
						ImGui::CoolCheckbox(TEXT("Double shotgun"), &bDoublePump);
						ImGui::EndChild();
					} ImGui::SameLine();

					if (ImGui::BeginChild(TEXT("C_Combat_Two"), mvec(300, 300))) {
						ImGui::Text(TEXT("Exploits (2)"));
						ImGui::CoolCheckbox(TEXT("No minigun cooldown"), &bNoMinigunCooldown);
						ImGui::SliderFloat(fPublicFov, TEXT("Camera FOV"), &fPublicFov, 70.f, 180.f);
						ImGui::SliderFloat(fSpeedMultiplier, TEXT("Speed"), &fSpeedMultiplier, 1.f, 20.f);

						ImGui::Text(TEXT("Attaching"));
						ImGui::CoolCheckbox(TEXT("No bloom"), &bNoBloom); ImGui::SameLine(); ImGui::TextColored(ImVec4(255, 0, 0, 255), TEXT("(!)"));
						ImGui::CoolCheckbox(TEXT("No spread"), &bNoSpread); ImGui::SameLine(); ImGui::TextColored(ImVec4(255, 0, 0, 255), TEXT("(!)"));
						ImGui::CoolCheckbox(TEXT("Instant reload"), &bNoReload); ImGui::SameLine(); ImGui::TextColored(ImVec4(255, 0, 0, 255), TEXT("(!)"));
						ImGui::CoolCheckbox(TEXT("Unlock firerate"), &bNoCooldown); ImGui::SameLine(); ImGui::TextColored(ImVec4(255, 0, 0, 255), TEXT("(!)"));
						ImGui::Text(TEXT(""));
						if (bExploitsUnprotected) {
							ImGui::Text(TEXT("Status ->")); ImGui::SameLine(); ImGui::TextColored(ImVec4(255, 255, 0, 255), TEXT("Attached"));
						}
						else {
							ImGui::Text(TEXT("Status -> ")); ImGui::SameLine(); ImGui::TextColored(ImVec4(240, 25, 25, 255), TEXT("Not attached"));
						}
						ImGui::Text(TEXT("Features marked with")); ImGui::SameLine(); ImGui::TextColored(ImVec4(255, 0, 0, 255), TEXT("(!)")); ImGui::SameLine();
						ImGui::Text(TEXT("require an activation."));

						if (!bExploitsUnprotected)
							ImGui::TextColored(ImVec4(255, 255, 0, 255), TEXT("[CLICK TO ACTIVATE]"));

						if (ImGui::IsItemClicked() && !bExploitsUnprotected) {
							//unprotect
							{
								uintptr_t ProtectAddress = BaseAddress + 0xD70554; //nospread
								//memory::protect_virtual_memory((PVOID)ProtectAddress, 1, PAGE_EXECUTE_READWRITE);
							}
							{
								uintptr_t ProtectAddress = BaseAddress + 0x4691A1; //nobloom
								//memory::protect_virtual_memory((PVOID)ProtectAddress, 8, PAGE_EXECUTE_READWRITE);
							}
							{
								uintptr_t ProtectAddress = BaseAddress + 0x70EEBC1; //insta reload
								//memory::protect_virtual_memory((PVOID)ProtectAddress, 8, PAGE_EXECUTE_READWRITE);
							}
							{
								uintptr_t ProtectAddress = BaseAddress + 0x7129464; //no cooldown
								//memory::protect_virtual_memory((PVOID)ProtectAddress, 9, PAGE_EXECUTE_READWRITE);
							}
							bExploitsUnprotected = true;
						}
						ImGui::EndChild();
					}
				}
			}
		}

		//Settings
		{
			if (MenuTab == 3) {
				if (ImGui::BeginChild(TEXT("C_Settings_Tab"), mvec(650, 340))) {
					ImGui::Text(TEXT(""));

					if (bShowVisualButtons)
					{
						if (SettingPage == 0) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Information"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Information"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							SettingPage = 0;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("General cheat information.");
						}

						ImGui::SameLine();
						if (SettingPage == 1) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Global chat"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Global chat"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							SettingPage = 1;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("Global chat for all vanta users.");
						}

						ImGui::SameLine();
						if (SettingPage == 2) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("My account"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("My account"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							SettingPage = 2;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("Information about your vanta account.");
						}

						ImGui::SameLine();
						if (SettingPage == 3) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Report a bug"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Report a bug"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							SettingPage = 3;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("Follow the instructions of this page in order to report a bug.");
						}

						ImGui::SameLine();
						if (SettingPage == 4) {
							ImGui::CoolButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Support"), mvec(120, 20));
						}
						else {
							ImGui::CoolButton(ImVec4(0.0f, 0.0f, 0.0f, 0.0f), TEXT("Support"), mvec(120, 20));
						}
						if (ImGui::IsItemClicked()) {
							SettingPage = 4;
						}
						if (ImGui::IsItemHovered()) {
							TestText = TEXT("24/7 live chat support.");
						}
					}
					if (SettingPage == 0) {
						if (ImGui::BeginChild(TEXT("C_Info_One"), mvec(300, 270))) {
							ImGui::Text(TEXT(""));
							ImGui::Separator();
							ImGui::Text(TEXT("[Cheat information]"));
							if (ImGui::BeginChild(TEXT("C_CheatInfo_One"), mvec(100, 50))) {
								ImGui::TextColored(ImVec4(0.92f, 0.92f, 0.3f, 1.0f), TEXT("Cheat version"));
								ImGui::TextColored(ImVec4(0.92f, 0.92f, 0.3f, 1.0f), TEXT("Game version"));
								ImGui::TextColored(ImVec4(0.92f, 0.92f, 0.3f, 1.0f), TEXT("Handler"));
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_CheatInfo_Two"), mvec(140, 50))) {
								std::string HandlerAddress = std::to_string(BaseAddress);
								HandlerAddress = TEXT("0x") +  HandlerAddress;

								ImGui::Text(TEXT("->")); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.8f, 0.4f, 0.05f, 1.0f), TEXT("13.2"));
								ImGui::Text(TEXT("->")); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.8f, 0.4f, 0.05f, 1.0f), TEXT("20.40 (20244966)"));
								ImGui::Text(TEXT("->")); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.8f, 0.4f, 0.05f, 1.0f), HandlerAddress.c_str());
								ImGui::EndChild();
							}
							ImGui::Text(TEXT(""));
							ImGui::Text(TEXT("[Cheat status]"));
							if (ImGui::BeginChild(TEXT("C_CheatStatus_One"), mvec(100, 35))) {
								ImGui::TextColored(ImVec4(0.05f, 0.92f, 0.65f, 1.0f), TEXT("EasyAntiCheat"));
								ImGui::TextColored(ImVec4(0.05f, 0.92f, 0.65f, 1.0f), TEXT("BattlEye"));
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_CheatStatus_Two"), mvec(140, 35))) {
								ImGui::Text(TEXT("->")); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 0.9f), TEXT("Undetected"));
								ImGui::Text(TEXT("->")); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.92f, 0.92f, 0.3f, 0.9f), TEXT("Unknown"));
								ImGui::EndChild();
							}
							ImGui::Text(TEXT(""));
							ImGui::Text(TEXT("[Safety]"));
							if (ImGui::BeginChild(TEXT("C_CheatSafety_One"), mvec(100, 35))) {
								ImGui::TextColored(ImVec4(0.05, 0.3f, 0.7f, 1.0f), TEXT("Discord"));
								ImGui::TextColored(ImVec4(0.05, 0.3f, 0.7f, 1.0f), TEXT("Website"));
								ImGui::EndChild();
							} ImGui::SameLine();
							if (ImGui::BeginChild(TEXT("C_CheatSafety_Two"), mvec(140, 35))) {
								ImGui::Text(TEXT("->")); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.92f, 0.5f, 0.92f, 0.9f), TEXT("[DISCORD]")); if (ImGui::IsItemClicked()) system(TEXT("start https://discord.gg/vanta"));
								ImGui::Text(TEXT("->")); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.92f, 0.5f, 0.92f, 0.9f), TEXT("[WEBSITE]")); if (ImGui::IsItemClicked()) system(TEXT("start https://vantacheats.com"));
								ImGui::EndChild();
							}
							ImGui::Separator();

							ImGui::EndChild();
						} ImGui::SameLine();
						if (ImGui::BeginChild(TEXT("C_Info_Two"), mvec(300, 270))) {
							ImGui::Text(TEXT(""));
							ImGui::Separator();
							ImGui::Text(TEXT("[Change log]"));
							ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), TEXT("[25/05] Menu animation + shader"));
							ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), TEXT("[26/05] Radar (w/ Team color)"));
							ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), TEXT("[26/05] Team box"));
							ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), TEXT("[26/05] Criticals"));
							ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), TEXT("[26/05] Full Auto"));
							ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), TEXT("[26/05] Double shotgun"));
							ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), TEXT("[26/05] Speedhack"));
							ImGui::TextColored(ImVec4(0.75f, 0.75f, 0.75f, 1.0f), TEXT("[26/05] Minigun cooldown"));
							ImGui::Separator();
							ImGui::EndChild();
						}
					}
					if (SettingPage == 1) {
						ImGui::Text(TEXT(""));
						ImGui::Text(TEXT("(Coming in v10)"));

						/*ImGui::Text(TEXT("General chat cooldown: 10 Second(s)"));
						ImGui::InputText(TEXT("input me"), TextToSendContent, 256);
						ImGui::Separator();
						ImGui::BeginChild(TEXT("GlobalChat_C"), mvec(600, 240), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
						for (msg message : ChatMessages) {

							std::stringstream messagei;

							messagei << message.author << TEXT(": ") << message.message;

							std::string messagein = messagei.str();

							const char* messagefinal = messagein.c_str();

							ImGui::Text(messagefinal);
							ImGui::SetScrollHereY(1.0f);
						}
						ImGui::EndChild();
						ImGui::Separator();
						ImGui::InputText(TEXT(""), TextToSendContent, 256);
						ImGui::SameLine();
						if (ImGui::EpicButton(ImVec4(0.65f, 0.05f, 0.9f, 1.0f), TEXT("Send"), mvec(500, 22))) {
							std::thread chattsebnd(ChatSend);
							chattsebnd.detach();
						}*/
					}
					if (SettingPage == 2) {
						ImGui::Text(TEXT(""));
						ImGui::Text(TEXT("(Coming in v10)"));
					}
					if (SettingPage == 3) {
						ImGui::Text(TEXT(""));
						ImGui::Text(TEXT("(Coming in v10)"));
					}
					if (SettingPage == 4) {
						ImGui::Text(TEXT(""));
						ImGui::Text(TEXT("(Coming in v10)"));
					}
				}
			}
		}
		ImGui::End();
	}

	//main menu title
	auto Size66 = ImGui::CalcTextSize(TEXT("Samsung S1#1234 ft. Sincey#0001"));
	m->AddText(mvec(CenterX - (Size66.x / 2), m_pos_y + 7), ImGui::GetColorU32({ 0.92f, 0.92f, 0.3f, 1.0f }), TEXT("Samsung S1#1234 ft. Sincey#0001")); //0.92f, 0.92f, 0.3f, 1.0f

	//background effect (main)
	{
		int Size = 5;
		for (int LayerOffset = 0; LayerOffset < Size; LayerOffset++) {

			mvec StartEx = mvec(m_pos_x, m_pos_y);
			mvec EndEx = mvec(m_pos_x + m_size_x, m_pos_y + m_size_y);

			mvec Start = mvec(StartEx.x - LayerOffset, StartEx.y - LayerOffset);
			mvec End = mvec(EndEx.x + LayerOffset, EndEx.y + LayerOffset);

			float Transparency = 1.f / (LayerOffset * 2);
			Transparency *= 255;

			m->AddRect(Start, End, IM_COL32(0.65f * 255, 0.05f * 255, 0.9f * 255, Transparency), 6.5f, 0, 1.f);
		}
	}

	//background effect (esp preview)
	{
		int Size = 5;
		for (int LayerOffset = 0; LayerOffset < Size; LayerOffset++) {
			int lenght = 250;
			int x1 = m_pos_x + m_size_x + 25;
			int y1 = m_pos_y;
			int x2 = m_pos_x + m_size_x + 25 + lenght;
			int y2 = m_pos_y + m_size_y;
			int x3 = (x1 + lenght) - (lenght / 2);

			mvec StartEx = mvec(x1, y1);
			mvec EndEx = mvec(x2, y2);

			mvec Start = mvec(StartEx.x - LayerOffset, StartEx.y - LayerOffset);
			mvec End = mvec(EndEx.x + LayerOffset, EndEx.y + LayerOffset);

			float Transparency = 1.f / (LayerOffset * 2);
			Transparency *= 255;

			m->AddRect(Start, End, IM_COL32(0.65f * 255, 0.05f * 255, 0.9f * 255, Transparency), 6.5f, 0, 1.f);
		}
	}

	//background effect (buttons)
	{
		int Size = 5;
		for (int LayerOffset = 0; LayerOffset < Size; LayerOffset++) {

			int SizeOfThisX = 63;
			int offset_y = 75;
			int test = 19;


			mvec StartEx = mvec(m_pos_x - (SizeOfThisX + 25), m_pos_y + offset_y + (test / 2));
			mvec EndEx = mvec(StartEx.x + SizeOfThisX, StartEx.y + m_size_y - ((offset_y * 2) + test));

			mvec Start = mvec(StartEx.x - LayerOffset, StartEx.y - LayerOffset);
			mvec End = mvec(EndEx.x + LayerOffset, EndEx.y + LayerOffset);

			float Transparency = 1.f / (LayerOffset * 2);
			Transparency *= 255;

			m->AddRect(Start, End, IM_COL32(0.65f * 255, 0.05f * 255, 0.9f * 255, Transparency), 6.5f, 0, 1.f);
		}

		//int SizeOfThisX = 63;
		//int offset_y = 75;
		//int test = 19;

		//mvec Start = mvec(m_pos_x - (SizeOfThisX + 25), m_pos_y + offset_y + (test / 2));
		//mvec End = mvec(Start.x + SizeOfThisX, Start.y + m_size_y - ((offset_y * 2) + test));

		//ImGui::SetWindowPos(mvec(m_pos_x - (SizeOfThisX + 25), m_pos_y + offset_y + (test / 2)));
		//ImGui::SetWindowSize(mvec(SizeOfThisX, m_size_y - ((offset_y * 2) + test)));
	}


	//POINT point;
	//if (GetCursorPos(&point)) {
	//	m->AddTriangleFilled(mvec(point.x, point.y), mvec(point.x + 5, point.y + 15), mvec(point.x + 15, point.y + 10), ImGui::GetColorU32({ m_r, m_g, m_b, 1.0f }));
		//m->AddTriangle(mvec(point.x, point.y), mvec(point.x + 5, point.y + 15), mvec(point.x + 15, point.y + 10), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), 2.0f);
		//ImGui::GetForegroundDrawList()->AddRectFilled(mvec(point.x, point.y), mvec(point.x + 6, point.y + 6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1.f)));
		//utils::DrawBox(point.x, point.y, 6, 6, 0, 0, 0, 1.f, true);
	//}
	ImGui::PopFont();
}

namespace Menu {
	VOID RenderMenu(HWND Window) {
        if (GetAsyncKeyState(VK_INSERT) & 1) {
            bIsMenuOpen = !bIsMenuOpen;
        }

        if (bIsMenuOpen) {
			MakeMenu();
            MenuWindow(Window);
        }
        else {
            GameWindow(Window);
        }

		//rework
		/*if (bIsMenuOpen) {
			if (Options::bStreamProof) {
				XGUARD_WIN(SetWindowDisplayAffinity(Window, WDA_MONITOR));
			}
			else {
				XGUARD_WIN(SetWindowDisplayAffinity(Window, WDA_NONE));
			}
		}*/
	}
}