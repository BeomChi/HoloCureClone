#include "pch.h"
#include "Item.h"
#include "../../01.Manager/TimeManager.h"
#include "../../03.Object/Entity/Player/Player.h"

Item::Item()
{
	_itemType = ItemType::None;
	GetOrAddTransform();
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

//void Item::Render(HDC hdc)
//{
//	Super::Render(hdc);
//}

void Item::MoveTo(GameObject* obj)
{
	float deltatime = TIME->GetDeltaTime();

	Vec3 pos = GetTransform()->GetPosition();
	Vec3 dir = obj->GetTransform()->GetPosition() - pos;
	dir.Normalize();

	pos += dir * deltatime * 100.f;
}

void Item::Reset()
{
	_player = nullptr;
}

bool Item::PlayerDistance()
{
	if(_player == nullptr)
		return false;

	float deltatime = TIME->GetDeltaTime();
	Vec3 pos = GetTransform()->GetPosition();

	Vec3 dir = _player->GetTransform()->GetPosition() - pos;
	float distance = dir.Length();

	if (distance < _absorbDistance) 
	{
		ApplyEffect();
		SetIsActivity(false); 
	}
	else if(distance < _player->GetItemAbsorbDistance())
	{
		dir.Normalize();
		GetTransform()->SetPosition(pos + dir * _moveSpeed * deltatime);
	}

	return true;
}
