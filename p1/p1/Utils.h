#pragma once

#include <windows.h>
#include <string>
using namespace std;

class Utils
{
public:
	static void DrawText(HDC hdc, Pos pos, const wstring& str);

	static void DrawRect(HDC hdc, Pos pos, int32 w, int32 h);

	static void DrawCircle(HDC hdc, Pos pos, int32 radius);

	static void DrawLine(HDC hdc, Pos from, Pos to);

	static void DrawLineColored(HDC hdc, Pos from, Pos to, COLORREF color);

	static void DrawTextFont(HDC hdc, Pos pos, const wstring& str,
		int fontSize = 16,
		COLORREF color = RGB(255, 255, 255),
		const wstring& fontName = L"¸¼Àº °íµñ",
		int width = 300,
		int height = 100);

};

