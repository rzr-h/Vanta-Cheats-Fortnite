#pragma once

#include "Includes.h"
#include "GameFunctions.h"

void Make3DBox(bool foreground, bool StartIsCenter, float Offset, float Thickness, ImVec4 Clr, Vector Start, float Top)
{
	ImDrawList* Renderer;
	if (foreground)
		Renderer = ImGui::GetForegroundDrawList();
	else
		Renderer = ImGui::GetBackgroundDrawList();

	if (StartIsCenter) {
		Vector BottomOne = Vector(Start.x + Offset, Start.y + Offset, Start.z - Offset);
		Vector BottomOneW2S = W2S(BottomOne);

		Vector BottomTwo = Vector(Start.x - Offset, Start.y - Offset, Start.z - Offset);
		Vector BottomTwoW2S = W2S(BottomTwo);

		Vector BottomThree = Vector(Start.x + Offset, Start.y - Offset, Start.z - Offset);
		Vector BottomThreeW2S = W2S(BottomThree);

		Vector BottomFour = Vector(Start.x - Offset, Start.y + Offset, Start.z - Offset);
		Vector BottomFourW2S = W2S(BottomFour);

		Vector TopOne = Vector(Start.x + Offset, Start.y + Offset, Start.z + Offset);
		Vector TopOneW2S = W2S(TopOne);

		Vector TopTwo = Vector(Start.x - Offset, Start.y - Offset, Start.z + Offset);
		Vector TopTwoW2S = W2S(TopTwo);

		Vector TopThree = Vector(Start.x + Offset, Start.y - Offset, Start.z + Offset);
		Vector TopThreeW2S = W2S(TopThree);

		Vector TopFour = Vector(Start.x - Offset, Start.y + Offset, Start.z + Offset);
		Vector TopFourW2S = W2S(TopFour);

		Renderer->AddLine(mvec(BottomOneW2S.x, BottomOneW2S.y), mvec(BottomThreeW2S.x, BottomThreeW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(BottomThreeW2S.x, BottomThreeW2S.y), mvec(BottomTwoW2S.x, BottomTwoW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(BottomTwoW2S.x, BottomTwoW2S.y), mvec(BottomFourW2S.x, BottomFourW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(BottomFourW2S.x, BottomFourW2S.y), mvec(BottomOneW2S.x, BottomOneW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);

		Renderer->AddLine(mvec(TopOneW2S.x, TopOneW2S.y), mvec(TopThreeW2S.x, TopThreeW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(TopThreeW2S.x, TopThreeW2S.y), mvec(TopTwoW2S.x, TopTwoW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(TopTwoW2S.x, TopTwoW2S.y), mvec(TopFourW2S.x, TopFourW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(TopFourW2S.x, TopFourW2S.y), mvec(TopOneW2S.x, TopOneW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);

		Renderer->AddLine(mvec(BottomOneW2S.x, BottomOneW2S.y), mvec(TopOneW2S.x, TopOneW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(BottomTwoW2S.x, BottomTwoW2S.y), mvec(TopTwoW2S.x, TopTwoW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(BottomThreeW2S.x, BottomThreeW2S.y), mvec(TopThreeW2S.x, TopThreeW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(BottomFourW2S.x, BottomFourW2S.y), mvec(TopFourW2S.x, TopFourW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
	}
	else {
		Vector BottomOne = Vector(Start.x + Offset, Start.y + Offset, Start.z);
		Vector BottomOneW2S = W2S(BottomOne);

		Vector BottomTwo = Vector(Start.x - Offset, Start.y - Offset, Start.z);
		Vector BottomTwoW2S = W2S(BottomTwo);

		Vector BottomThree = Vector(Start.x + Offset, Start.y - Offset, Start.z);
		Vector BottomThreeW2S = W2S(BottomThree);

		Vector BottomFour = Vector(Start.x - Offset, Start.y + Offset, Start.z);
		Vector BottomFourW2S = W2S(BottomFour);

		Vector TopOne = Vector(Start.x + Offset, Start.y + Offset, Top);
		Vector TopOneW2S = W2S(TopOne);

		Vector TopTwo = Vector(Start.x - Offset, Start.y - Offset, Top);
		Vector TopTwoW2S = W2S(TopTwo);

		Vector TopThree = Vector(Start.x + Offset, Start.y - Offset, Top);
		Vector TopThreeW2S = W2S(TopThree);

		Vector TopFour = Vector(Start.x - Offset, Start.y + Offset, Top);
		Vector TopFourW2S = W2S(TopFour);

		Renderer->AddLine(mvec(BottomOneW2S.x, BottomOneW2S.y), mvec(BottomThreeW2S.x, BottomThreeW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(BottomThreeW2S.x, BottomThreeW2S.y), mvec(BottomTwoW2S.x, BottomTwoW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(BottomTwoW2S.x, BottomTwoW2S.y), mvec(BottomFourW2S.x, BottomFourW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(BottomFourW2S.x, BottomFourW2S.y), mvec(BottomOneW2S.x, BottomOneW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);

		Renderer->AddLine(mvec(TopOneW2S.x, TopOneW2S.y), mvec(TopThreeW2S.x, TopThreeW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(TopThreeW2S.x, TopThreeW2S.y), mvec(TopTwoW2S.x, TopTwoW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(TopTwoW2S.x, TopTwoW2S.y), mvec(TopFourW2S.x, TopFourW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(TopFourW2S.x, TopFourW2S.y), mvec(TopOneW2S.x, TopOneW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);

		Renderer->AddLine(mvec(BottomOneW2S.x, BottomOneW2S.y), mvec(TopOneW2S.x, TopOneW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(BottomTwoW2S.x, BottomTwoW2S.y), mvec(TopTwoW2S.x, TopTwoW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(BottomThreeW2S.x, BottomThreeW2S.y), mvec(TopThreeW2S.x, TopThreeW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
		Renderer->AddLine(mvec(BottomFourW2S.x, BottomFourW2S.y), mvec(TopFourW2S.x, TopFourW2S.y), ImGui::GetColorU32({ Clr.x, Clr.y, Clr.z, Clr.w }), Thickness);
	}
}
void DrawRect(bool foreground, int x, int y, int w, int h, ImColor color, int thickness) {
	if (foreground)
		ImGui::GetForegroundDrawList()->AddRect(mvec(x, y), mvec(x + w, y + h), color, 0, 0, thickness);
	else
		ImGui::GetBackgroundDrawList()->AddRect(mvec(x, y), mvec(x + w, y + h), color, 0, 0, thickness);
}

void DrawFilledRect(bool foreground, int x, int y, int w, int h, ImColor color) {
	if (foreground)
		ImGui::GetForegroundDrawList()->AddRectFilled(mvec(x, y), mvec(x + w, y + h), color, 0, 0);
	else
		ImGui::GetBackgroundDrawList()->AddRectFilled(mvec(x, y), mvec(x + w, y + h), color, 0, 0);

}
void RenderBox(bool ForeGround, float OffsetW, float OffsetH, int X, int Y, int W, int H, ImVec4 Color, int thickness, bool Filled, bool NoCorner) {
	float lineW = (W / OffsetW);
	float lineH = (H / OffsetH);
	ImDrawList* p = ImGui::GetBackgroundDrawList();
	if (ForeGround)
		p = ImGui::GetForegroundDrawList();

	if (Filled) {
		auto Converted = IM_COL32(Color.x * 255, Color.y * 255, Color.z * 255, 40);
		DrawFilledRect(ForeGround, X, Y, W, H, Converted);
	}
	if (NoCorner) {
		auto Converted = IM_COL32(Color.x * 255, Color.y * 255, Color.z * 255, Color.w * 255);
		DrawRect(ForeGround, X, Y, W, H, Converted, 2.0f);
	}
	else {
		//oben links nach unten
		p->AddLine(mvec(X, Y - 1), mvec(X, Y + lineH), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//oben links nach rechts (l-mittig)
		p->AddLine(mvec(X, Y), mvec(X + lineW, Y), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//oben rechts (r-mittig) nach rechts
		p->AddLine(mvec(X + W - lineW, Y), mvec(X + W + 2, Y), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//oben rechts nach vert-rechts (oberhalb)
		p->AddLine(mvec(X + W, Y - 1), mvec(X + W, Y + lineH), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//unten vert-links (unterhalb) nach unten links
		p->AddLine(mvec(X, Y + H - lineH), mvec(X, Y + H), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//unten links nach rechts (mittig)
		p->AddLine(mvec(X - 1, Y + H), mvec(X + lineW + 1, Y + H), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//unten rechts (mittig) nach rechts
		p->AddLine(mvec(X + W - lineW, Y + H), mvec(X + W + 2, Y + H), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);

		//unten rechts nach vert-rechts (unterhalb)
		p->AddLine(mvec(X + W, Y + H - lineH), mvec(X + W, Y + H), ImGui::GetColorU32({ Color.x, Color.y, Color.z, Color.w }), thickness);
	}
}

namespace Render {
	VOID MakeText(const char* Text, mvec ScreenLocation, ImU32 Color, bool Background, bool Outlined) {
		ImDrawList* Draw = ImGui::GetForegroundDrawList();
		if (Background)
			Draw = ImGui::GetBackgroundDrawList();

		if (Outlined) {
			Draw->AddText(mvec(ScreenLocation.x + 1, ScreenLocation.y + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), Text);
			Draw->AddText(mvec(ScreenLocation.x - 1, ScreenLocation.y - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), Text);
			Draw->AddText(mvec(ScreenLocation.x + 1, ScreenLocation.y - 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), Text);
			Draw->AddText(mvec(ScreenLocation.x - 1, ScreenLocation.y + 1), ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 1.0f }), Text);
		}

		Draw->AddText(ScreenLocation, Color, Text);
	}

	VOID MakeLine(mvec ScreenStart, mvec ScreenEnd, ImU32 Color, float Thickness, bool Background) {
		ImDrawList* Draw = ImGui::GetForegroundDrawList();
		if (Background)
			Draw = ImGui::GetBackgroundDrawList();

		Draw->AddLine(ScreenStart, ScreenEnd, Color, Thickness);
	}

	VOID MakeRect(mvec ScreenStart, mvec ScreenEnd, ImU32 Color, ImVec4 FilledColor, float Rounding, float Thickness, bool Background, bool Filled) {
		ImDrawList* Draw = ImGui::GetForegroundDrawList();
		if (Background)
			Draw = ImGui::GetBackgroundDrawList();

		if (Filled) {
			auto Converted = IM_COL32(FilledColor.x * 255, FilledColor.y * 255, FilledColor.z * 255, 40);

			Draw->AddRectFilled(ScreenStart, ScreenEnd, Converted, Rounding, NULL);
		}

		Draw->AddRect(ScreenStart, ScreenEnd, Color, Rounding, NULL, Thickness);
	}

	VOID Make2DBox(int X, int Y, int W, int H, bool Background, ImVec4 Color) {
		auto Converted = IM_COL32(Color.x * 255, Color.y * 255, Color.z * 255, Color.w * 255);
		DrawRect(Background, X, Y, W, H, Converted, 2.0f);
	}
}

bool ret = false;
ImTextureID TestNigger;
PDIRECT3DTEXTURE9 my_texture = NULL;
bool LoadTextureFromFile(const char* filename, PDIRECT3DTEXTURE9* out_texture, int* out_width, int* out_height)
{
	// Load texture from disk
	PDIRECT3DTEXTURE9 texture;

	HRESULT hr = D3DXCreateTextureFromFileA(pDevice, filename, &texture);
	if (hr != S_OK)
		return false;

	// Retrieve description of the texture surface so we can access its size
	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;
	return true;
}