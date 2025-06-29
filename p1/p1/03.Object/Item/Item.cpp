#include "pch.h"
#include "Item.h"
#include "../../01.Manager/TimeManager.h"
#include "../../03.Object/Entity/Player/Player.h"

Item::Item()
{
	_itemType = ItemType::None;
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
	_player = nullptr;
}

bool Item::PlayerDistance()
{
	if(_player == nullptr)
		return false;

	float deltatime = GET_SINGLE(TimeManager)->GetDeltaTime();

	Vec2 dir = _player->GetPos() - GetPos();
	float distance = dir.Length();

	if (distance < _absorbDistance) 
	{
		ApplyEffect();
		SetIsActivity(false); 
	}
	else
	{
		dir.Normalize();
		SetPos(GetPos() + dir * _moveSpeed * deltatime);
	}

	return true;
}
