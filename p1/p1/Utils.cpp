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

HBITMAP Utils::CreateTextBitmap(const wstring& str, int fontSize, COLORREF color, const wstring& fontName,int width, int height)
{
	HDC screenDC = GAME->GetHdc();

	// 1. 텍스트를 그릴 독립적인 DC
	HDC memDC = CreateCompatibleDC(screenDC);

	// 2. 그 DC에서 사용할 Bitmap
	HBITMAP hBitmap =
		CreateCompatibleBitmap(screenDC, width, height);

	// 3. Bitmap을 memDC에 연결
	HBITMAP oldBitmap =
		(HBITMAP)SelectObject(memDC, hBitmap);

	// 4. Font 생성
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

	// 5. Font를 memDC에 연결
	HFONT oldFont =
		(HFONT)SelectObject(memDC, hFont);

	// 출력범위
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(memDC, &rect, brush);
	DeleteObject(brush);

	// 배경 투명 설명, 글자 색상 설정
	SetBkMode(memDC, TRANSPARENT);
	SetTextColor(memDC, color);

	// 6. memDC에 DrawText
	::DrawText(memDC, str.c_str(), -1, &rect, DT_LEFT | DT_TOP | DT_WORDBREAK);

	// 7. Font 복구/삭제
	SelectObject(memDC, oldFont);
	DeleteObject(hFont);

	// 8. Bitmap 복구
	SelectObject(memDC, oldBitmap);

	// 9. DC 삭제
	DeleteDC(memDC);

	// 10. Bitmap은 반환
	return hBitmap;
}

