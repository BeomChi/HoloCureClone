#include "pch.h"
#include "Ui.h"
#include "../01.Manager/InputManager.h"

Ui::Ui()
{
}

Ui::~Ui()
{
}

void Ui::Init()
{
	Super::Init();
}

void Ui::Update()
{
	Super::Update();
}

void Ui::Render(HDC hdc)
{
	Super::Render(hdc);
}

RECT Ui::GetRect()
{
	RECT rect =
	{
		_pos.x - _size.x / 2,
		_pos.y - _size.y / 2,
		_pos.x + _size.x / 2,
		_pos.y + _size.y / 2
	};

	return rect;
}

bool Ui::IsMouseInRect()
{
	RECT rect = GetRect();

	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();

	if (mousePos.x < rect.left)
		return false;
	if (mousePos.x > rect.right)
		return false;
	if (mousePos.y < rect.top)
		return false;
	if (mousePos.y > rect.bottom)
		return false;

	return true;
}
