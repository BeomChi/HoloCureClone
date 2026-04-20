#include "pch.h"
#include "HpBar.h"
#include "../../05.Resource/2D/Sprite.h"

HpBar::HpBar()
{
}

HpBar::~HpBar()
{
}

void HpBar::Init()
{
	Super::Init();
}

void HpBar::Update()
{
	Super::Update();
}

void HpBar::Render(HDC hdc)
{
	Super::Render(hdc);
}

void HpBar::SetHP(float hp,float max)
{
	SetValue(hp, max);
}



