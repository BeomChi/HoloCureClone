#include "pch.h"
#include "Bomb.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../01.Manager/ObjectManager.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/BombObj.h"
#include "../../../../03.Object/Entity/Player/Player.h"


Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

void Bomb::Init()
{
	SetEquipInfo({ L"Bomb",1,7,1,0,
		1,0.5,8,1,5 });

	
}

void Bomb::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_sumTime += deltaTime;


	if (_sumTime - _lastAttackTime >= _info._coolTime)
	{
		int randX = RandomRange(0, GWinSizeX);
		int randY = RandomRange(0, GWinSizeY);

		Vec2 randPos = (GET_SINGLE(SceneManager)->ScreenToWorld({(float)randX,(float)randY}));

		BombObj* bombObj = GET_SINGLE(ObjectPool)->Get<BombObj>(L"BombObj");

		bombObj->SetDemage(CalculateDamge());
		bombObj->SetPos(randPos);
		bombObj->SetAttackDelay(3.f);

		GET_SINGLE(ObjectManager)->AddObject(bombObj);


		_lastAttackTime = _sumTime;
	}
}

void Bomb::Render(HDC hdc)
{
}


// 여기 밑으로는 나중에 강화기능 생기면 사용 예정

void Bomb::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_info._level);
}

void Bomb::OnUnequipEffect(Player& player)
{
}


// 레벨업으로 인한 수치를 여기서 적용
// ApplyEffectByLevel 여기서 레벨업을 통한 수치를 받고
// ApplyEffect 여기서 적용
void Bomb::ApplyEffect()
{
}

void Bomb::UseAbility(const Player& player)
{
}
