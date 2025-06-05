#include "../../../pch.h"
#include "Equipment.h"
#include "../../../01.Manager/GameManager.h"
#include "../../../03.Object/Entity/Player/Player.h"

Equipment::Equipment()
{
	_itemType = ItemType::Equipment;
}

Equipment::~Equipment()
{
}

void Equipment::Init()
{
	Super::Init();
}

void Equipment::Update()
{
	Super::Update();
}

void Equipment::Render(HDC hdc)
{
	Super::Render(hdc);
}


void Equipment::SetEquipInfo(const EquipInfo& info)
{
	_info._count = info._count;
	_info._level = 1;
	_info._maxLevel = info._maxLevel;
	_info._dmg = info._dmg;

	 _info._range = info._range;
	 _info._attackDelay = info._attackDelay;
	 _info._coolTime = info._coolTime;
	 _info._dmgMultiplier = info._dmgMultiplier;
}

void Equipment::ResetEquipInfo()
{
	_info._level = 1;
	_info._maxLevel = 0;
	_info._count = 1;

	_info._range = 1;
	_info._dmg = 0;
	_info._attackDelay = 0;
	_info._coolTime = 0;
	_info._dmgMultiplier = 0;
}

void Equipment::UpgradeEquip(Player& player)
{
	_info._level++;

	OnEquipEffect(player);
}

void Equipment::ApplyEffectByLevel(int32 level)
{
	if (_levelEffects.contains(level))
	{
		const EquipEffect& effect = _levelEffects[level];

		switch (effect._type)
		{
		case EffectType::DamageBoost:
			_info._dmgMultiplier += effect._value;
			break;

		case EffectType::IncreaseProjectileCount:
			_info._count += effect._intValue;
			break;

		case EffectType::BounceOnMaxPierce:
			// 도탄 플래그 설정
			//_canBounce = true;
			break;

		case EffectType::AttackSpeedUp:
			_info._coolTime *= (1.f - effect._value);
			_info._range += effect._intValue; // 관통 수 증가라면
			break;

		case EffectType::DelayedDamage:
			//_enableDelayedDamage = true;
			//_delayedDamagePercent = effect._value;
			//_delayTime = effect._intValue;
			break;

		default:
			break;
		}
	}
}

int32 Equipment::CalculateDamge()
{
	auto player = GET_SINGLE(GameManager)->GetPlayer();

	return player->GetInfo()._atk * player->GetInfo()._dmgMultiplier * _info._dmgMultiplier;
}
