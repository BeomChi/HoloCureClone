#pragma once
#include "../ResourceBase.h"

class Texture : public ResourceBase
{
public:
	Texture();
	virtual ~Texture() override;

	Texture* Loadbmp(HWND hwnd, const wstring& path);
	HDC GetDC();

	void SetSize(Vec2Int size) { _size = size; }
	Vec2Int GetSize() { return _size; }

	void SetTransparent(uint32 transparent) { _transparent = transparent; }
	uint32 GetTransparent() { return _transparent; }

	//Vec2 GetPivot() { return _pivot; }
	//void SetPivot(Vec2 pivot) { _pivot = pivot; }

private:
	HDC _hdc = {};
	HBITMAP _bitmap = {};
	Vec2Int _size = {};
	uint32 _transparent = RGB(255, 0, 255);

	//Vec2 _pivot = { 0.5f,0.5f };
};

