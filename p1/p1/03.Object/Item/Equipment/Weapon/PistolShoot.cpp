#include "../../../../pch.h"
#include "PistolShoot.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../01.Manager/ObjectManager.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/Bullet.h"
#include "../../../../03.Object/Entity/Player/Player.h"


PistolShoot::PistolShoot()
{
}

PistolShoot::~PistolShoot()
{
}

void PistolShoot::Init()
{
	SetEquipInfo({ 1,7,3,0,1,0,3,1 });

	_levelEffects[1] = EquipEffect{
	EffectType::None,
	0.f,
	0,
	"아메의 기본 무기."
	};
	_levelEffects[2] = EquipEffect{
	EffectType::IncreaseProjectileCount,
	0.f,
	2,
	"발사 수가 2 증가하며, 각 탄환의 최대 관통 수가 1회 증가한다."
	};

	_levelEffects[3] = EquipEffect{
		EffectType::DamageBoost,
		0.2f,
		0,
		"대미지 20% 상승"
	};

	_levelEffects[4] = EquipEffect{
		EffectType::BounceOnMaxPierce,
		0.f,
		0,
		"탄환이 최대 관통 수에 도달하면 도탄된다."
	};

	_levelEffects[5] = EquipEffect{
		EffectType::AttackSpeedUp,
		0.25f,
		1,
		"각 탄환의 최대 관통 수가 1회 증가하며, 공격 주기가 25% 감소한다."
	};

	_levelEffects[6] = EquipEffect{
		EffectType::DamageBoost,
		0.2f,
		0,
		"대미지 20% 상승"
	};
}

void PistolShoot::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_sumTime += deltaTime;


	if (_sumTime - _lastAttackTime >= _info._coolTime)
	{

		Bullet* bullet = GET_SINGLE(ObjectPool)->Get<Bullet>(L"Bullet");

		bullet->SetPos(GetFirePos());
		bullet->SetDir(GetMousePosToPlayerDir());
		bullet->SetDmg(CalculateDamge());

		GET_SINGLE(ObjectManager)->AddObject(bullet);
		_fireCount++;

		if (_fireCount >= _info._count)
			_lastAttackTime = _sumTime;
	}
}

void PistolShoot::Render(HDC hdc)
{
}

void PistolShoot::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_info._level);
}



void PistolShoot::OnUnequipEffect(Player& player)
{

}

Vec2 PistolShoot::GetFirePos()
{
	Vector firePos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();
	Vector dir = GetMousePosToPlayerDir();


	firePos += dir * _firePosLength;

	return firePos;
}

Vec2 PistolShoot::GetMousePosToPlayerDir()
{
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vec2 Pos = GET_SINGLE(SceneManager)->ScreenToWorld(mousePos);
	Vector firePos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();

	float dirX = Pos.x - _pos.x;
	float dirY = Pos.y - _pos.y;

	Vector dir = { dirX,dirY };
	dir.Normalize();

	return dir;
}
