#include "../../pch.h"
#include "Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

Texture* Texture::Loadbmp(HWND hwnd, const wstring& path)
{
	HDC hdc = ::GetDC(hwnd);

	_hdc = CreateCompatibleDC(hdc);
	_bitmap = (HBITMAP)LoadImage(nullptr, path.c_str(),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE
		| LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

	if (_bitmap == NULL)
	{
		MessageBox(hwnd, path.c_str(), L"이미지 불러오기 실패", NULL);
	}

	HBITMAP prev = (HBITMAP)SelectObject(_hdc, _bitmap);

	if(prev != nullptr)
		DeleteObject(prev);

	BITMAP bit = {};
	GetObject(_bitmap, sizeof(BITMAP), &bit);

	_size.x = bit.bmWidth;
	_size.y = bit.bmHeight;

	return this;
}

HDC Texture::GetDC()
{
	return _hdc;
}
