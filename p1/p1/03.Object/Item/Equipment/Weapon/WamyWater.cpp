#include "pch.h"
#include "WamyWater.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../02.Scene/Scene.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/Splash.h"
#include "../../../../03.Object/Entity/Player/Player.h"


WamyWater::WamyWater()
{
	_equipType = Equip::Weapon;
}

WamyWater::~WamyWater()
{
}

/// @brief 와미수 무기 초기화
/// @details 무기 속성 정보(레벨, 쿨타임, 데미지 배율 등)를 설정한다.
///          데미지는 실시간으로 계산되므로 초기값은 0.
void WamyWater::Init()
{
	SetEquipInfo({
		L"WamyWater", // 무기 이름
		WeaponType::Melee, // 무기 타입 (근접 공격형)
		1,          // 초기 레벨
		7,          // 최대 레벨
		},

		{
		1,          // 투사체 수
		
		1.f,          // 공격 범위
		2.f,          // 쿨타임 (초)
		0.f,          // 공격 주기(지속데미지형인 경우)
		0.f,			// 지속 시간 (투사체가 살아있는 시간, 초 단위)
		1.f           // 데미지 배율
		});

	_levelEffects[1] =
	{
		{
			EffectType::None,
			0.f,
			0,
			L"전방으로 출처를 알 수 없는 물을 뿌려 적들을 넉백 시킨다."
		}
	};
	_levelEffects[2] = 
	{
		{
			EffectType::DamageBoost,
			0.2f,
			0,
			L"대미지 20% 상승" 
		}  
	};
	_levelEffects[3] =
	{
		{
			EffectType::RangeIncrease,
			0.3f,
			0,
			L"공격 범위가 30% 상승한다"
		}
	};


	// 넉백 enum 자고 일어나서 추가하자
	_levelEffects[4] = 
	{
		{ 
			EffectType::KnockbackForce,
			0.2f,
			0, 
			L"넉백 효과가 상승한다"
		}
	};
	_levelEffects[5] = 
	{
		{ 
			EffectType::AttackSpeedUp,
			0.2f,
			0, 
			L"공격 주기가 20% 감소" 
		}
	};
	_levelEffects[6] =
	{
		{
			EffectType::DamageBoost,
			0.3f,
			0,
			L"대미지 30% 상승"
		}
	};
	_levelEffects[7] =
	{
		{
			EffectType::RangeIncrease,
			0.3f,
			0,
			L"공격 범위가 30% 상승한다"
		},
		{
			EffectType::SpecialAbility,
			0.f,
			0,
			L""
		}
	};
}

/// @brief 매 프레임마다 호출되어, 쿨타임이 지난 경우 스플레쉬 투사체를 발사함
void WamyWater::Update()
{
	if (GET_SINGLE(GameManager)->GetPlayer() == nullptr)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 쿨타임이 경과하면 투사체를 발사
	if (_sumTime - _lastAttackTime >= _info._coolTime)
	{
		// 오브젝트 풀에서 SausageObj를 꺼냄
		Splash* splash = GET_SINGLE(ObjectPool)->Get<Splash>(L"Splash");

		// 플레이어 위치 기준으로 발사 위치 지정
		splash->SetPos(GetFirePos());

		// 플레이어의 방향에 따라 투사체 방향 설정
		Dir dir = GET_SINGLE(GameManager)->GetPlayer()->GetDir();
		
		if (dir == DIR_LEFT)
			splash->SetState(DirState::Left);
		else
			splash->SetState(DirState::Right);

		// 실시간 데미지 계산 후 설정
		splash->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));
		splash->SetScale(Vec2{ _info._range, _info._range }); // 투사체 크기 설정
		splash->SetKnockbackForce(_knockbackForce );

		// ObjectManager에 추가하여 게임 내 등장시킴
		// 나중에 ObjectManager 지우고 씬으로 관리 예정
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(splash);

		// 마지막 공격 시간 갱신
		_lastAttackTime = _sumTime;
	}
}

/// @brief 무기 자체의 렌더링은 없음 (투사체가 별도로 처리함)
void WamyWater::Render(HDC hdc)
{
	// Sausage 무기는 별도의 시각 효과가 없으므로 비워둠
}

/// @brief 무기 장착 시 플레이어에게 부여되는 효과
void WamyWater::OnEquipEffect(Player& player)
{
	// 무기 레벨에 따라 효과 적용
	ApplyEffectByLevel(_baseInfo._level);
}

/// @brief 무기 해제 시 효과 (현재 별도 효과 없음)
void WamyWater::OnUnequipEffect(Player& player)
{
	// 필요한 경우 효과 제거 가능
}

/// @brief 플레이어 방향을 고려해 투사체의 시작 위치 계산
/// @return 플레이어 위치 기준으로 좌우 거리만큼 떨어진 위치 반환
Vec2 WamyWater::GetFirePos()
{
	Vector firePos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();
	Dir dir = GET_SINGLE(GameManager)->GetPlayer()->GetDir();

	if (dir == DIR_LEFT)
		firePos.x += (-1) * _firePosLength;
	else
		firePos.x += 1 * _firePosLength;

	return firePos;
}


void WamyWater::ApplyEffect()
{
}

void WamyWater::UseAbility(const Player& player)
{
}

void WamyWater::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const AOEEquipInfo& info)
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

void WamyWater::ApplyEffectByLevel(int32 level)
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
			case EffectType::AttackSpeedUp:					// 쿨타임 감소
				_info._coolTime = max(0.05f, _info._coolTime * (1.f - effect._value));
				break;
			case EffectType::RangeIncrease:					// 공격 범위 증가
				_info._range += effect._value;
				break;
			case EffectType::SpecialAbility:				// 특수 능력 활성화
				_isSpecialAbility = true;
				break;
			case EffectType::KnockbackForce:				// 넉백 거리 증가
				_knockbackForce = _knockbackForce + (_knockbackForce * effect._value);
				break;
			default:										// 없는 경우 경고 메시지
				assert(false && "Unhandled EffectType in ApplyEffectByLevel()");
				break;
			}
		}
	}
}
