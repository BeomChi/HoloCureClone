#include "pch.h"
#include "Utils.h"

void Utils::DrawText(HDC hdc, Pos pos, const wstring& str)
{
	::TextOut(hdc, static_cast<int32>(pos.x), static_cast<int32>(pos.y), str.c_str(), static_cast<int32>(str.size()));
}

void Utils::DrawRect(HDC hdc, Pos pos, int32 w, int32 h)
{
	::Rectangle(hdc, static_cast<int32>(pos.x - w / 2), static_cast<int32>(pos.y - h / 2), static_cast<int32>(pos.x + w / 2), static_cast<int32>(pos.y + h / 2));
}

void Utils::DrawCircle(HDC hdc, Pos pos, int32 radius)
{
	::Ellipse(hdc, static_cast<int32>(pos.x - radius), static_cast<int32>(pos.y - radius), static_cast<int32>(pos.x + radius), static_cast<int32>(pos.y + radius));
}

void Utils::DrawLine(HDC hdc, Pos from, Pos to)
{
	::MoveToEx(hdc, static_cast<int32>(from.x), static_cast<int32>(from.y), nullptr);
	::LineTo(hdc, static_cast<int32>(to.x), static_cast<int32>(to.y));
}

void Utils::DrawLineColored(HDC hdc, Pos from, Pos to, COLORREF color)
{
	HPEN pen = ::CreatePen(PS_SOLID, 1, color);
	HPEN oldPen = (HPEN)::SelectObject(hdc, (HGDIOBJ)pen);

	::MoveToEx(hdc, static_cast<int32>(from.x), static_cast<int32>(from.y), nullptr);
	::LineTo(hdc, static_cast<int32>(to.x), static_cast<int32>(to.y));

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}

void Utils::DrawTextFont(HDC hdc, Pos pos, const wstring& str, int fontSize, COLORREF color, const wstring& fontName, int width, int height)
{
	// 폰트 생성
	HFONT hFont = CreateFont(
		fontSize, 0, 0, 0, FW_NORMAL,
		FALSE, FALSE, FALSE,
		HANGEUL_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		fontName.c_str()
	);

	// 기존 폰트 백업, 적용
	HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

	// 배경 투명 설명, 글자 색상 설정
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);

	// 출력범위
	RECT rect;
	rect.left = static_cast<LONG>(pos.x);
	rect.top = static_cast<LONG>(pos.y);
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	::DrawText(hdc, str.c_str(), -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);

	// 리소스 정리
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}

