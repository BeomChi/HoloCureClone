#include "pch.h"
#include "Ui.h"
#include "../01.Manager/InputManager.h"
#include "97.Engin/Component/Transform/Transform.h"

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
	float x = GetOrAddTransform()->GetPosition().x;
	float y = GetOrAddTransform()->GetPosition().y;

	float cx = GetOrAddTransform()->GetScale().x;
	float cy = GetOrAddTransform()->GetScale().y;

	RECT rect =
	{
		x - cx/ 2,
		y - cy / 2,
		x + cx / 2,
		y + cy / 2
	};

	return rect;
}

bool Ui::IsMouseInRect()
{
	RECT rect = GetRect();

	POINT mousePos = INPUT->GetMousePos();

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
