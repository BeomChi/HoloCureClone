#include "pch.h"
#include "Sausage.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../02.Scene/Scene.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/SausageObj.h"
#include "../../../../03.Object/Entity/Player/Player.h"


Sausage::Sausage()
{
	_equipType = Equip::Weapon;
}

Sausage::~Sausage()
{
}

/// @brief 소세지 무기 초기화
/// @details 무기 속성 정보(레벨, 쿨타임, 데미지 배율 등)를 설정한다.
///          데미지는 실시간으로 계산되므로 초기값은 0.
void Sausage::Init()
{
	SetEquipInfo({
		L"Sausage",			// 무기 이름
		WeaponType::Melee,  // 무기 타입 (근접 공격형)
		1,					// 초기 레벨
		7,					// 최대 레벨
		},

		{
		1,					// 생성 수

		1.f,					// 공격 범위
		5.f,					// 쿨타임 (초)
		0.f,					// 지속시간
		0.f,					// 공격 주기(지속데미지형인 경우)
		1.f					// 데미지 배율
		});

	// 레벨별 효과 초기화
	_levelEffects[1] =
	{
		{
			EffectType::None,
			0.f,
			0,
			L"작은 소시지를 휘두른다"
		}
	};
	_levelEffects[2] =
	{
		{
			EffectType::RangeIncrease,
			0.3f,
			0,
			L"대미지 20% 상승"
		}
	};
	_levelEffects[3] =
	{
		{
			EffectType::AttackSpeedUp,
			0.5f,
			0,
			L"공격이 명중했을 때, 넉백(소)가 발생한다"
		}
	};

	_levelEffects[4] =
	{
		{
			EffectType::AttackSpeedUp,
			0.2f,
			0,
			L"공격 주기가 20% 감소"
		}
	};
	_levelEffects[5] =
	{
		{
			EffectType::RangeIncrease,
			0.5f,
			0,
			L"공격 범위랑 대미지 30% 상승"
		},
		{
			EffectType::DamageBoost,
			0.3f,
			0,
			L"공격 범위랑 대미지 30% 상승"
		}
	};
	_levelEffects[6] =
	{
		{
			EffectType::AttackSpeedUp,
			0.2f,
			0,
			L"공격 주기가 20% 감소"
		}
	};
	_levelEffects[7] =
	{
		{
			EffectType::SpecialAbility,
			0.f,
			0,
			L"소시지의 히트 수가 2회로 증가한다"
		},

	};
}

/// @brief 매 프레임마다 호출되어, 쿨타임이 지난 경우 소세지 투사체를 발사함
void Sausage::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 쿨타임이 경과하면 투사체를 발사
	if (_sumTime - _lastAttackTime >= _info._coolTime)
	{
		// 오브젝트 풀에서 SausageObj를 꺼냄
		SausageObj* sausageObj = GET_SINGLE(ObjectPool)->Get<SausageObj>(L"SausageObj");

		// 플레이어 위치 기준으로 발사 위치 지정
		sausageObj->SetPos(GetFirePos());

		// 투사체 크기 설정
		sausageObj->SetScale(Vec2{ _info._range, _info._range }); 

		// 플레이어의 방향에 따라 투사체 방향 설정
		Dir dir = GET_SINGLE(GameManager)->GetPlayer()->GetDir();
		if (dir == DIR_LEFT)
			sausageObj->SetState(DirState::Left);
		else
			sausageObj->SetState(DirState::Right);

		// 실시간 데미지 계산 후 설정
		sausageObj->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));

		// Scene에 추가하여 게임 내 등장시킴
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(sausageObj);

		// 마지막 공격 시간 갱신
		_lastAttackTime = _sumTime;
	}
}

/// @brief 무기 자체의 렌더링은 없음 (투사체가 별도로 처리함)
void Sausage::Render(HDC hdc)
{
	// Sausage 무기는 별도의 시각 효과가 없으므로 비워둠
}

/// @brief 무기 장착 시 플레이어에게 부여되는 효과
void Sausage::OnEquipEffect(Player& player)
{
	// 무기 레벨에 따라 효과 적용
	ApplyEffectByLevel(_baseInfo._level);
}

/// @brief 무기 해제 시 효과 (현재 별도 효과 없음)
void Sausage::OnUnequipEffect(Player& player)
{
	// 필요한 경우 효과 제거 가능
}

/// @brief 플레이어 방향을 고려해 투사체의 시작 위치 계산
/// @return 플레이어 위치 기준으로 좌우 거리만큼 떨어진 위치 반환
Vec2 Sausage::GetFirePos()
{
	Vector firePos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();
	Dir dir = GET_SINGLE(GameManager)->GetPlayer()->GetDir();

	if (dir == DIR_LEFT)
		firePos.x += (-1) * _firePosLength;
	else
		firePos.x += 1 * _firePosLength;

	return firePos;
}


void Sausage::ApplyEffect()
{
}

void Sausage::UseAbility(const Player& player)
{
}

void Sausage::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const AOEEquipInfo& info)
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

void Sausage::ApplyEffectByLevel(int32 level)
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
			case EffectType::SpecialAbility:						// 특수 능력 활성화 (예: 저주가 체인될 때마다 대미지 증가)	
				_isSpecialAbility = true;
			default:												// 없는 경우 경고 메시지
				assert(false && "Unhandled EffectType in ApplyEffectByLevel()");
				break;
			}
		}
	}
}
