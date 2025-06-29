#include "pch.h"
#include "EliteLavaBucket.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../01.Manager/ObjectManager.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/Bullet.h"
#include "../../../../03.Object/Projectile/Lava.h"
#include "../../../../03.Object/Entity/Player/Player.h"


EliteLavaBucket::EliteLavaBucket()
{
}

EliteLavaBucket::~EliteLavaBucket()
{
}

void EliteLavaBucket::Init()
{
	SetEquipInfo({ L"EliteLavaBucket",1,7,1,0,
		1,0.5,8,1,5 });

	
}

void EliteLavaBucket::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_sumTime += deltaTime;


	if (_sumTime - _lastAttackTime >= _info._coolTime)
	{
		int randX = RandomRange(0, GWinSizeX);
		int randY = RandomRange(0, GWinSizeY);

		Vec2 randPos = (GET_SINGLE(SceneManager)->ScreenToWorld({(float)randX,(float)randY}));

		Lava* lava = GET_SINGLE(ObjectPool)->Get<Lava>(L"Lava");

		lava->SetDemage(CalculateDamge());
		lava->Activate(randPos, _info._duration);
		lava->SetAttackDelay(0.5f);

		GET_SINGLE(ObjectManager)->AddObject(lava);


		_lastAttackTime = _sumTime;
	}
}

void EliteLavaBucket::Render(HDC hdc)
{
}

void EliteLavaBucket::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_info._level);
}

void EliteLavaBucket::OnUnequipEffect(Player& player)
{
}



void EliteLavaBucket::ApplyEffect()
{
}

void EliteLavaBucket::UseAbility(const Player& player)
{
}
