#include "pch.h"
#include "SpiderCooking.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../01.Manager/ObjectManager.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/Miasma.h"
#include "../../../../03.Object/Entity/Player/Player.h"





SpiderCooking::SpiderCooking()
{
}

SpiderCooking::~SpiderCooking()
{
}

void SpiderCooking::Init()
{
	SetEquipInfo({ L"SpiderCooking",1,7,3,0,1,0,3,1});

	
}

void SpiderCooking::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	
}

void SpiderCooking::Render(HDC hdc)
{
}

void SpiderCooking::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_info._level);

	if (_info._level == 1)
	{
		_miasma = GET_SINGLE(ObjectManager)->CreateAddGameObject<Miasma>();
	}
	
	_miasma->SetDmg(CalculateDamge());
	
}



void SpiderCooking::OnUnequipEffect(Player& player)
{

}



void SpiderCooking::ApplyEffect()
{
}

void SpiderCooking::UseAbility(const Player& player)
{
}
