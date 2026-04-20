#include "pch.h"
#include "EliteLavaBucket.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../02.Scene/Scene.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/Bullet.h"
#include "../../../../03.Object/Projectile/Lava.h"
#include "../../../../03.Object/Entity/Player/Player.h"


EliteLavaBucket::EliteLavaBucket()
{
	_equipType = Equip::Weapon;
}

EliteLavaBucket::~EliteLavaBucket()
{
}

/// 엘리트 라바 버킷 무기 초기화
/// 일정 쿨타임마다 무작위 위치에 용암(Lava) 장판을 생성하여
/// 지속적으로 데미지를 주는 공격 무기
void EliteLavaBucket::Init()
{
	SetEquipInfo({
		L"EliteLavaBucket",		// 무기 이름
		WeaponType::Multishot,  // 무기 타입 (다중 발사형)
		1,						// 초기 레벨
		7,						// 최대 레벨
		},

		{
		1,						// 생성 수 (동시 장판 수)
		1.f,					// 공격 범위
		8.f,					// 쿨타임 (초 단위)
		5.f,					// 장판 지속 시간
		0.5f,					// 공격 주기(지속데미지형인 경우)
		1.f,					// 데미지 배율
		});

	// 레벨별 효과 초기화
	_levelEffects[1] =
	{
		{
			EffectType::None,
			0.f,
			0,
			L"적에게 지속 대미지를 주는 용암을 지면에 던진다"
		}
	};
	_levelEffects[2] =
	{
		{
			EffectType::RangeIncrease,
			0.2f,
			0,
			L"용암의 범위가 20% 상승"
		}
	};
	_levelEffects[3] =
	{
		{
			EffectType::IncreaseProjectileCount,
			0.f,
			1,
			L" 던지는 용암 양동이의 개수가 2개가 된다"
		}
	};

	_levelEffects[4] =
	{
		{
			EffectType::DamageBoost,
			0.3f,
			0,
			L"대미지 30% 상승, 용암의 지속 시간 1초 상승"
		},
		{
			EffectType::DurationIncrease,
			1.f,
			0,
			L"대미지 30% 상승, 용암의 지속 시간 1초 상승"
		}
	};
	_levelEffects[5] =
	{
		{
			EffectType::DamageBoost,
			0.3f,
			0,
			L"대미지 30% 상승"
		}
	};
	_levelEffects[6] =
	{
		{
			EffectType::IncreaseProjectileCount,
			0.f,
			1,
			L"던지는 용암 양동이의 개수가 3개가 된다"
		}
	};
	_levelEffects[7] =
	{
		{
			EffectType::IncreaseProjectileCount,
			0.f,
			1,
			L"던지는 용암 양동이의 개수가 4개가 되고, 용암의 범위가 20% 상승"
		},
		{
			// 아무래도 각 무기별로 7렙떄 특수 기능들이 활성화 되는거 같으니 그걸 bool로 해서 각 무기별로 만들자
			EffectType::RangeIncrease,
			0.2f,
			0,
			L"용암의 범위가 20% 상승"
		}
	};
}

/// @brief 쿨타임마다 화면에 랜덤한 위치에 용암 장판을 생성
void EliteLavaBucket::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	// 쿨타임이 경과하면 용암 생성
	if (_sumTime - _lastAttackTime >= _info._coolTime)
	{
		for (int i = 0; i < _info._count; ++i)
		{
			CreateLava();
		}
		

		// 마지막 공격 시간 갱신
		_lastAttackTime = _sumTime;
	}
}

void EliteLavaBucket::Render(HDC hdc)
{
}

// ------------------------------
// 향후 무기 강화 시 사용하는 함수들
// ------------------------------

/// @brief 무기 장착 시 효과 (레벨에 따른 효과 적용)
void EliteLavaBucket::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_baseInfo._level);

	// 방어구 같이 플레이어한테 치명타 데미지 증가나 치명타 확률증가가 있으면
	// 여기서 적용하는게 맞을듯
}

/// @brief 무기 해제 시 효과 (현재는 효과 없음)
void EliteLavaBucket::OnUnequipEffect(Player& player)
{
	// 강화 효과 해제 등 처리 가능 (현재 없음)
	// 무기류는 일단 해제 시 특별한 효과가 없으므로 비워둠

}

void EliteLavaBucket::CreateLava()
{
	// 화면 내 임의 위치 좌표 생성
	int randX = RandomRange(0, GWinSizeX);
	int randY = RandomRange(0, GWinSizeY);

	// 화면 좌표를 월드 좌표로 변환
	Vec2 randPos = GET_SINGLE(SceneManager)->ScreenToWorld({
		(float)randX, (float)randY
		});

	// 오브젝트 풀에서 Lava 오브젝트 가져오기
	Lava* lava = GET_SINGLE(ObjectPool)->Get<Lava>(L"Lava");

	// 데미지 설정 및 활성화 (위치, 지속 시간 설정 포함)
	lava->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));
	lava->Activate(randPos, _info._duration);

	// 장판 크기 설정
	lava->SetScale(Vec2(_info._range, _info._range));

	// 장판 발동 후 약간의 지연 시간 설정 (지속 피해 주기 등)
	lava->SetAttackDelay(0.5f);

	// 게임 내 오브젝트로 등록
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(lava);
}

/// @brief 레벨업 효과 적용용 함수 (예: 쿨타임 감소, 공격 범위 증가 등)
void EliteLavaBucket::ApplyEffect()
{
	// 추후 강화 기능 구현 시 여기에 적용
	// 생각해보니 레벨업을 하면 레벨을 올리고 OnEquipEffect 이걸 호출해서 적용하는데 필요할까?
}

/// @brief Bomb 고유 능력 사용 (예: 폭탄을 수동 폭발시키는 등)
void EliteLavaBucket::UseAbility(const Player& player)
{
	// 추후 수동 발동 액티브 스킬용
}

void EliteLavaBucket::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const AOEEquipInfo& info)
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

void EliteLavaBucket::ApplyEffectByLevel(int32 level)
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
			case EffectType::IncreaseProjectileCount:		// 투사체 수 증가
				_info._count += effect._intValue;
				break;
			case EffectType::RangeIncrease:					// 공격 범위 증가
				_info._range += effect._value;
				break;
			case EffectType::DurationIncrease:				// 지속 시간 증가
				_info._duration += effect._value;
				break;
			default:										// 없는 경우 경고 메시지
				assert(false && "Unhandled EffectType in ApplyEffectByLevel()");
				break;
			}
		}
	}
}
