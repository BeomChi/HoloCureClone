#include "pch.h"
#include "FanBeam.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../01.Manager/ObjectManager.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/FanBeamObj.h"
#include "../../../../03.Object/Entity/Player/Player.h"


FanBeam::FanBeam()
{
}

FanBeam::~FanBeam()
{
}

void FanBeam::Init()
{
	SetEquipInfo({ L"FanBeam",1,7,1,0,
		1,0.5f,2,1});

	
}

void FanBeam::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_sumTime += deltaTime;


	if (_sumTime - _lastAttackTime >= _info._coolTime)
	{

		FanBeamObj* fanBeamObj = GET_SINGLE(ObjectPool)->Get<FanBeamObj>(L"FanBeamObj");
		fanBeamObj->SetPos(GetFirePos());

		Dir dir = GET_SINGLE(GameManager)->GetPlayer()->GetDir();

		if(dir == DIR_LEFT)
			fanBeamObj->SetState(DirState::Left);
		else
			fanBeamObj->SetState(DirState::Right);

		fanBeamObj->SetDmg(CalculateDamge());
		

		GET_SINGLE(ObjectManager)->AddObject(fanBeamObj);

		_lastAttackTime = _sumTime;
	}
}

void FanBeam::Render(HDC hdc)
{
}

void FanBeam::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_info._level);
}



void FanBeam::OnUnequipEffect(Player& player)
{

}

Vec2 FanBeam::GetFirePos()
{
	Vector firePos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();
	Dir dir = GET_SINGLE(GameManager)->GetPlayer()->GetDir();

	if(dir == DIR_LEFT)
		firePos.x +=  ( - 1) * _firePosLength;
	else
		firePos.x += 1 * _firePosLength;

	return firePos;
}


void FanBeam::ApplyEffect()
{
}

void FanBeam::UseAbility(const Player& player)
{
}
