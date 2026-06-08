#include "pch.h"
#include "PsychoAxe.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../02.Scene/Scene.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/Axe.h"
#include "../../../../03.Object/Entity/Player/Player.h"


PsychoAxe::PsychoAxe()
{
	_equipType = Equip::Weapon;
}

PsychoAxe::~PsychoAxe()
{
}

void PsychoAxe::Init()
{
	/// @brief PsychoAxe 무기의 초기 설정 정보를 지정합니다.
	/// @details SetEquipInfo는 무기 이름, 레벨, 쿨타임, 데미지 배율, 지속시간 등
	/// 무기 동작에 필요한 핵심 데이터를 구조체로 전달받아 저장합니다.
	/// 데미지는 실시간으로 계산되므로 기본값은 0으로 설정되어 있습니다.
	SetEquipInfo({
		L"PsychoAxe",		// 무기 이름
		WeaponType::Melee,  // 무기 타입 (근접 공격형)
		1,					// 초기 레벨
		7,					// 최대 레벨
		},

		{
		1,					// 투사체 수 (한 번에 발사되는 개수)
		1.f,					// 공격 범위 (투사체 크기나 히트 범위)
		5.f,					// 재사용 대기시간 (쿨타임, 초 단위)
		5.f,					// 지속 시간 (투사체가 살아있는 시간, 초 단위)
		0.f,					// 공격 주기(지속데미지형인 경우)
		1.f					// 데미지 배율 (실제 데미지 계산 시 곱해짐)
		});

	// 레벨별 효과 초기화
	_levelEffects[1] =
	{
		{
			EffectType::None,
			0.f,
			0,
			L"자신으로부터 나선형으로 날아가는 도끼를 던진다"
		}
	};
	_levelEffects[2] =
	{

		{
			EffectType::RangeIncrease,
			0.2f,
			0,
			L"도끼의 사이즈가 20% 상승, 대미지 20% 상승"
		},
		{
			EffectType::DamageBoost,
			0.2f,
			0,
			L""
		}
	};
	_levelEffects[3] =
	{
		{
			EffectType::AttackSpeedUp,
			0.2f,
			0,
			L"공격 주기가 20% 감소"
		}
	};

	_levelEffects[4] =
	{
		{
			EffectType::RangeIncrease,
			0.f,
			125,
			L"도끼의 사이즈가 20% 상승, 대미지 33% 상승"
		},
		{
			EffectType::DamageBoost,
			0.33f,
			0,
			L""
		}
	};
	_levelEffects[5] =
	{
		{
			EffectType::SpecialAbility,
			0.f,
			0,
			L"도끼의 히트 수 제한이 사라지고, 지속 시간이 1초 상승"
		},
		{
			EffectType::DurationIncrease,
			1.f,
			0,
			L""
		}
	};
	_levelEffects[6] =
	{
		{
			EffectType::RangeIncrease,
			0.5f,
			0,
			L"도끼의 사이즈가 50% 상승"
		}
	};
	_levelEffects[7] =
	{
		{
			EffectType::DamageBoost,
			0.5f,
			0,
			L"대미지 50% 상승"
		},
	};
}

void PsychoAxe::Update()
{

	// 매 프레임마다 호출되는 업데이트 함수
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 마지막 공격 이후 쿨타임이 지났다면 도끼 생성
	if (_sumTime - _lastAttackTime >= _info._coolTime)
	{
		// 오브젝트 풀에서 Axe 투사체를 꺼내옴
		Axe* axe = GET_SINGLE(ObjectPool)->Get<Axe>(L"Axe");

		cout << "[DEBUG] 도끼 생성됨" << endl;
		// 데미지 계산 및 초기 설정
		axe->SetDamageInfo(CalculateDamge(_info._dmgMultiplier)); // 무기의 현재 공격력 설정
		axe->SetPos(GET_SINGLE(GameManager)->GetPlayer()->GetPos()); // 플레이어 위치에서 시작
		cout << "[DEBUG] AxePos : " << axe->GetPos().x << "  " << axe->GetPos().y << endl;
		axe->SetStartPos(axe->GetPos()); // 시작 위치 저장
		axe->SetDuration(_info._duration); // 투사체의 지속 시간 설정
		axe->SetScale(Vec2{ _info._range, _info._range }); // 투사체 크기 설정
		axe->SetLayer(LAYER_AREAATTACK);
		// 오브젝트 매니저에 추가하여 게임 월드에 등장시킴
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(axe);

		// 마지막 공격 시간 업데이트
		_lastAttackTime = _sumTime;
	}
}

void PsychoAxe::Render(HDC hdc)
{
}


// 여기 밑으로는 나중에 강화기능 생기면 사용 예정

void PsychoAxe::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_baseInfo._level);
}

void PsychoAxe::OnUnequipEffect(Player& player)
{
}


// 레벨업으로 인한 수치를 여기서 적용
// ApplyEffectByLevel 여기서 레벨업을 통한 수치를 받고
// ApplyEffect 여기서 적용
void PsychoAxe::ApplyEffect()
{
}

void PsychoAxe::UseAbility(const Player& player)
{
}

void PsychoAxe::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const AOEEquipInfo& info)
{
	_baseInfo._name = baseInfo._name;						// 무기 이름
	_baseInfo._weaponType = baseInfo._weaponType;			// 무기 타입
	_baseInfo._level = baseInfo._level;						// 현재 레벨
	_baseInfo._maxLevel = baseInfo._maxLevel;				// 최대 레벨
	_info._count = info._count;						// 투사체 수 (폭탄은 1개)

	_info._range = info._range;						// 공격 범위 (폭발 범위)
	_info._coolTime = info._coolTime;				// 쿨타임 (초 단위)
	_info._duration = info._duration;				// 지속 시간 (폭탄이 유지되는 시간)
	_info._attackDelay = info._attackDelay;			// 공격 주기 (지속 데미지형인 경우)
	_info._dmgMultiplier = info._dmgMultiplier;		// 데미지 배율 (기본 1.0, 레벨업 시 증가)
}

void PsychoAxe::ApplyEffectByLevel(int32 level)
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
			case EffectType::DamageBoost:							// 공격력 배율 증가 
				_info._dmgMultiplier += effect._value;
				break;
			case EffectType::AttackSpeedUp:							// 공격 속도 증가
				_info._coolTime = max(0.05f, _info._coolTime * (1.f - effect._value));
				break;
			case EffectType::RangeIncrease:							// 공격 범위 증가
				_info._range += effect._value;
				break;
			case EffectType::DurationIncrease:						// 지속 시간 증가
				_info._duration += effect._value;
				break;
			case EffectType::SpecialAbility:						// 특수 능력 활성화 (예: 저주가 체인될 때마다 대미지 증가)	
				_isSpecialAbility = true;
				break;
			default:												// 없는 경우 경고 메시지
				assert(false && "Unhandled EffectType in ApplyEffectByLevel()");
				break;
			}
		}
	}
}
