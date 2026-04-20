#include "pch.h"
#include "SpiderCooking.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../02.Scene/Scene.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/Miasma.h"
#include "../../../../03.Object/Entity/Player/Player.h"





SpiderCooking::SpiderCooking()
{
	_equipType = Equip::Weapon;
}

SpiderCooking::~SpiderCooking()
{
}

/// @brief SpiderCooking 무기 초기화
/// @details 투사체 없이 장착 시 지속 효과를 발생시키는 무기.
///          레벨별 강화 효과 적용 준비됨.
void SpiderCooking::Init()
{
	// 무기 기본 정보 설정
	SetEquipInfo({
		L"SpiderCooking",	// 무기 이름
		WeaponType::Melee,  // 무기 타입 (근접 공격형)
		1,					// 초기 레벨
		7,					// 최대 레벨
		},

		{
		1,					// 투사체 수 (여기서는 의미 없을 수 있음)

		1.f,					// 공격 범위
		3.f,					// 쿨타임
		0.f,					// 지속 시간 (지속 데미지형인 경우)
		0.5f,				// 공격 주기(지속데미지형인 경우)
		1.f					// 데미지 배율
		});

	// 레벨별 효과 초기화
	_levelEffects[1] =
	{
		{
			EffectType::None,
			0.f,
			0,
			L"범위 내의 적에게 지속 대미지를 주는 오라 계통의 공격을 발생시킨다"
		}
	};
	_levelEffects[2] =
	{
		{
			EffectType::RangeIncrease,
			0.15f,
			0,
			L"공격 범위 15% 상승"
		}
	};
	_levelEffects[3] =
	{
		{
			EffectType::DamageBoost,
			0.3f,
			0,
			L"대미지 30% 상승"
		}
	};

	_levelEffects[4] =
	{
		{
			EffectType::RangeIncrease,
			0.25f,
			0,
			L"공격 범위 25% 상승"
		}
	};
	_levelEffects[5] =
	{
		{
			EffectType::DelayedDamage,
			0.2f,
			0,
			L"대미지 발생 스피드 20% 상승"
		}
	};
	_levelEffects[6] =
	{
		{
			EffectType::DamageBoost,
			0.2f,
			0,
			L"대미지 30% 상승"
		}
	};
	_levelEffects[7] =
	{
		{
			EffectType::SpecialAbility,
			0.f,
			0,
			L"공격이 명중했을 때, 넉백(소)가 발생한다."
		},

	};
}

/// @brief 매 프레임 호출되지만 현재 동작 없음
/// @details 필요 시 이곳에 지속 효과나 상태 업데이트 로직 추가 가능
void SpiderCooking::Update()
{
	// 현재 Update 비어있음
}

/// @brief 무기 렌더링 처리 (현재 없음)
void SpiderCooking::Render(HDC hdc)
{
	// 무기 자체 렌더링 없음
}

/// @brief 무기 장착 시 호출되는 효과 적용 함수
/// @details
/// - 무기 레벨에 따른 강화 효과 적용
/// - 레벨 1일 때 `Miasma` 오브젝트 생성하여 지속 데미지 효과 발생
void SpiderCooking::OnEquipEffect(Player& player)
{
	// 레벨에 따라 강화 효과 적용
	ApplyEffectByLevel(_baseInfo._level);

	// 무기 레벨 1일 경우, 게임 내 오브젝트 매니저에서 Miasma 오브젝트 생성
	if (_baseInfo._level == 1 && _miasma == nullptr)
	{
		_miasma = new Miasma();
		_miasma->Init();
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(_miasma); // 현재 씬에 Miasma 오브젝트 추가
	}

	// Miasma 데미지 값을 현재 무기 데미지에 맞게 설정
	_miasma->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));
	_miasma->SetAttackDelay(_info._attackDelay);
	_miasma->SetScale(Vec2{ _info._range, _info._range }); // 공격 범위에 맞게 스케일 설정
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

void SpiderCooking::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const AOEEquipInfo& info)
{
	_baseInfo._name = baseInfo._name;						// 무기 이름
	_baseInfo._weaponType = baseInfo._weaponType;			// 무기 타입
	_baseInfo._level = baseInfo._level;						// 현재 레벨
	_baseInfo._maxLevel = baseInfo._maxLevel;				// 최대 레벨

	_info._count = info._count;						// 투사체 수 (폭탄은 1개)
	_info._range = info._range;						// 공격 범위 (폭발 범위)
	_info._coolTime = info._coolTime;				// 쿨타임 (초 단위)
	_info._duration = info._duration;				// 지속 시간
	_info._attackDelay = info._attackDelay;			// 공격 주기 (지속 데미지형인 경우)
	_info._dmgMultiplier = info._dmgMultiplier;		// 데미지 배율 (기본 1.0, 레벨업 시 증가)
}

void SpiderCooking::ApplyEffectByLevel(int32 level)
{
	if (level < 1 || level > 7)
		return;

	if (_levelEffects.contains(level))
	{
		const auto& effects = _levelEffects[level];
		for (const EquipEffect& effect : effects)
		{
			switch (effect._type)
			{
			case EffectType::None:
				break;
			case EffectType::DamageBoost:					// 공격력 배율 증가 
				_info._dmgMultiplier += effect._value;
				break;
			case EffectType::DelayedDamage:				// 지속 데미지 발생 속도 증가
				_info._attackDelay = max(0.05f, _info._attackDelay * (1.f - effect._value));
				break;
			case EffectType::RangeIncrease:					// 공격 범위 증가
				_info._range += effect._value;
				break;
			case EffectType::SpecialAbility:				// 특수 능력 활성화
				_isSpecialAbility = true;
				break;
			default:										// 없는 경우 경고 메시지
				assert(false && "Unhandled EffectType in ApplyEffectByLevel()");
				break;
			}
		}
	}
}
