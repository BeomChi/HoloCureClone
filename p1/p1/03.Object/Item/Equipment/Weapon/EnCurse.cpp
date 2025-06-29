#include "pch.h"
#include "EnCurse.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../01.Manager/ObjectManager.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/EnCurseObj.h"
#include "../../../../03.Object/Entity/Player/Player.h"


EnCurse::EnCurse()
{
}

EnCurse::~EnCurse()
{
}

void EnCurse::Init()
{
	SetEquipInfo({ L"EnCurse",1,7,1,0,1,0,3,1});

	
}

void EnCurse::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_sumTime += deltaTime;


	if (_sumTime - _lastAttackTime >= _info._coolTime)
	{

		EnCurseObj* enCurseObj = GET_SINGLE(ObjectPool)->Get<EnCurseObj>(L"EnCurseObj");
		enCurseObj->SetPos(GetFirePos());

		Dir dir = GET_SINGLE(GameManager)->GetPlayer()->GetDir();

		if(dir == DIR_LEFT)
			enCurseObj->SetState(DirState::Left);
		else
			enCurseObj->SetState(DirState::Right);

		enCurseObj->SetDmg(CalculateDamge());

		GET_SINGLE(ObjectManager)->AddObject(enCurseObj);

		_lastAttackTime = _sumTime;
	}
}

void EnCurse::Render(HDC hdc)
{
}

void EnCurse::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_info._level);
}



void EnCurse::OnUnequipEffect(Player& player)
{

}

Vec2 EnCurse::GetFirePos()
{
	Vector firePos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();
	Dir dir = GET_SINGLE(GameManager)->GetPlayer()->GetDir();

	if(dir == DIR_LEFT)
		firePos.x +=  ( - 1) * _firePosLength;
	else
		firePos.x += 1 * _firePosLength;

	return firePos;
}


void EnCurse::ApplyEffect()
{
}

void EnCurse::UseAbility(const Player& player)
{
}
