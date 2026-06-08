#include "pch.h"
#include "FanBeam.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../02.Scene/Scene.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/FanBeamObj.h"
#include "../../../../03.Object/Entity/Player/Player.h"


FanBeam::FanBeam()
{
	_equipType = Equip::Weapon;
}

FanBeam::~FanBeam()
{
}

/// @brief 전방 빔 공격 무기(FanBeam) 초기화
/// @details 일정 쿨타임마다 플레이어 전방에 FanBeamObj(빔 투사체)를 생성하여 즉시 공격
void FanBeam::Init()
{
	SetEquipInfo({
		L"FanBeam",			// 무기 이름
		WeaponType::Ranged, // 무기 타입 (원거리 공격형)
		1,					// 초기 레벨
		7,					// 최대 레벨
		},

		{
		1,					// 투사체 수 (1개의 빔)
		1.f,				// 공격 범위
		2.f,				// 쿨타임 (초)
		1.f,				// 지속 시간
		1.f,				// 공격 주기(지속데미지형인 경우)
		1					// 데미지 배율
		});

	// 레벨별 효과 초기화
	_levelEffects[1] =
	{
		{
			EffectType::None,
			0.f,
			0,
			L"마이크에서 강력한 레이저 빔이 발사된다. 수평으로만 발사가능"
		}
	};
	_levelEffects[2] =
	{
		{
			EffectType::RangeIncrease,
			0.3f,
			0,
			L"빔의 사이즈가 30% 상승"
		}
	};
	_levelEffects[3] =
	{
		{
			EffectType::AttackSpeedUp,
			0.5f,
			0,
			L"공격 주기 0.5초 감소"
		}
	};

	_levelEffects[4] =
	{
		{
			EffectType::DamageBoost,
			0.5f,
			0,
			L"대미지 50% 상승"
		}
	};
	_levelEffects[5] =
	{
		{
			EffectType::AttackSpeedUp,
			0.5f,
			0,
			L"공격 주기 0.5초 감소."
		}
	};
	_levelEffects[6] =
	{
		{
			EffectType::RangeIncrease,
			0.5f,
			0,
			L"빔의 사이즈가 50% 상승"
		}
	};
	_levelEffects[7] =
	{
		{
			EffectType::SpecialAbility,
			0.f,
			0,
			L"후방에 빔을 하나 더 발사한다"
		},
	};

}

/// @brief 일정 시간마다 전방에 FanBeamObj 생성 및 공격
void FanBeam::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 쿨타임 경과 시 공격 실행
	if (_sumTime - _lastAttackTime >= _info._coolTime)
	{
		// 오브젝트 풀에서 FanBeamObj 가져오기
		FanBeamObj* fanBeamObj = GET_SINGLE(ObjectPool)->Get<FanBeamObj>(L"FanBeamObj");

		// 발사 위치 설정 (플레이어 앞 방향)
		fanBeamObj->SetPos(GetFirePos(false));

		// 플레이어 방향에 따라 빔 방향 설정
		Dir dir = GET_SINGLE(GameManager)->GetPlayer()->GetDir();

		if (dir == DIR_LEFT)
			fanBeamObj->SetState(DirState::Left);
		else
			fanBeamObj->SetState(DirState::Right);

		// 데미지 설정
		fanBeamObj->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));

		// 크기 설정
		fanBeamObj->SetScale(Vec2(_info._range, _info._range));

		// 오브젝트 매니저에 등록
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(fanBeamObj);

		if (_isSpecialAbility)
		{
			// 후방 빔 발사
			FanBeamObj* rearFanBeamObj2 = GET_SINGLE(ObjectPool)->Get<FanBeamObj>(L"FanBeamObj");

			rearFanBeamObj2->SetPos(GetFirePos(_isSpecialAbility));

			// 반대 방향으로 설정
			if (dir == DIR_LEFT)
			{
				rearFanBeamObj2->SetState(DirState::Right);
			}
			else
			{
				rearFanBeamObj2->SetState(DirState::Left);
			}

			cout << "Front : " << (dir == DIR_LEFT ? "Left" : "Right") << endl;
			cout << "Rear  : " << (dir == DIR_LEFT ? "Right" : "Left") << endl;

			// 데미지 및 크기 설정
			rearFanBeamObj2->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));
			rearFanBeamObj2->SetScale(Vec2(_info._range, _info._range));

			// 오브젝트 매니저에 등록
			GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(rearFanBeamObj2);
		}

		// 마지막 공격 시간 갱신
		_lastAttackTime = _sumTime;
	}
}

/// @brief FanBeam 무기 자체는 별도 렌더링 없음 (투사체가 처리)
void FanBeam::Render(HDC hdc)
{
	// FanBeamObj가 시각적 효과 처리
}

/// @brief 무기 장착 시 효과 적용
/// @details 레벨 기반 효과를 적용 (쿨타임 감소, 데미지 증가 등)
void FanBeam::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_baseInfo._level);
}

/// @brief 무기 해제 시 효과 (현재는 별도 처리 없음)
void FanBeam::OnUnequipEffect(Player& player)
{
	// 효과 해제 로직 필요 시 추가
}

/// @brief 플레이어 앞 방향 기준 빔 발사 위치 계산
/// @return Vec2 형태의 위치 값
Vec2 FanBeam::GetFirePos(bool isSpecialAbility)
{
	Vector firePos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();
	Dir dir = GET_SINGLE(GameManager)->GetPlayer()->GetDir();

	if (!isSpecialAbility)
	{
		if (dir == DIR_LEFT)
			firePos.x += (-1) * _firePosLength;
		else
			firePos.x += 1 * _firePosLength;
	}
	else
	{
		if (dir == DIR_LEFT)
			firePos.x += 1 * _firePosLength;
		else
			firePos.x += (-1) * _firePosLength;
	}

	return firePos;
}


void FanBeam::ApplyEffect()
{
}

void FanBeam::UseAbility(const Player& player)
{
}

void FanBeam::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const AOEEquipInfo& info)
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

void FanBeam::ApplyEffectByLevel(int32 level)
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
			case EffectType::AttackSpeedUp:					// 공격 속도 증가
				_info._coolTime -= effect._value;			
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
