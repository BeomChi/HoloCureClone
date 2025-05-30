#include "../../pch.h"
#include "Item.h"
#include "../../01.Manager/TimeManager.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Init()
{
	Super::Init();
}

void Item::Update()
{
	Super::Update();
}

void Item::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Item::MoveTo(GameObject* obj)
{
	float deltatime = GET_SINGLE(TimeManager)->GetDeltaTime();

	Vec2 dir = obj->GetPos() - GetPos();
	dir.Normalize();

	_pos += dir * deltatime * 100.f;
}

void Item::Reset()
{

}
