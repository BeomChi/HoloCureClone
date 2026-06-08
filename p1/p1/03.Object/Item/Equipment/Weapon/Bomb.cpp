#include "pch.h"
#include "Bomb.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../02.Scene/Scene.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/BombObj.h"
#include "../../../../03.Object/Entity/Player/Player.h"


Bomb::Bomb()
{
	_equipType = Equip::Weapon;
}

Bomb::~Bomb()
{
}

/// @brief 폭탄(Bomb) 무기 초기화
/// @details 일정 쿨타임마다 화면의 랜덤 위치에 폭탄을 생성하여 일정 시간 후 폭발시키는 무기
void Bomb::Init()
{
	SetEquipInfo({
		L"Bomb",				// 무기 이름
		WeaponType::Multishot,  // 무기 타입 (다중 발사형)
		1,						// 초기 레벨
		7,						// 최대 레벨
		},

		{
		1,						// 투사체 수 (폭탄 1개)
		1.f,					// 공격 범위
		8.f,					// 쿨타임 (초 단위)
		3.f,					// 지속 시간 (폭탄 생성 후 유지 시간)
		0.f,					// 공격 주기(지속데미지형인 경우)
		1.f						// 데미지 배율
		});

	// 레벨별 효과 초기화
	_levelEffects[1] =
	{
		{
			EffectType::None,
			0.f,
			0,
			L"근처의 적 전부에게 대미지를 주는 폭탄을 던진다"
		}
	};
	_levelEffects[2] =
	{
		{
			EffectType::RangeIncrease,
			0.15f,
			0,
			L"폭발 범위가 15% 상승"
		}
	};
	_levelEffects[3] =
	{
		{
			EffectType::DamageBoost,
			0.2f,
			0,
			L" 대미지 20% 상승"
		}
	};

	_levelEffects[4] =
	{
		{
			EffectType::IncreaseProjectileCount,
			0.f,
			1,
			L"폭탄의 개수가 2개가 된다"
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
			0.2f,
			0,
			L"폭발 범위가 20 % 상승"
		}
	};
	_levelEffects[7] =
	{
		{
			EffectType::RangeIncrease,
			0.f,
			1,
			L"폭탄의 개수가 3개가 된다."
		},
		{
			// 아무래도 각 무기별로 7렙떄 특수 기능들이 활성화 되는거 같으니 그걸 bool로 해서 각 무기별로 만들자
			EffectType::SpecialAbility,	// 뭔 소리인지 모르겠네 
			0.f,
			0,
			L"[* 이 때 폭탄은 바라보는 방향의 앞쪽에 1개, 그와 120도의 각을 이루면서 뒤로 2개 생성된다.]"
		}
	};
}

/// @brief 매 프레임마다 호출되어 쿨타임마다 폭탄을 랜덤 위치에 생성
void Bomb::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;
	
	// 쿨타임이 지났을 경우 폭탄 생성
	if (_sumTime - _lastAttackTime >= _info._coolTime)
	{
		for (int i = 0; i < _info._count; i++)
		{
			// 윈도우 화면 내 임의 위치 생성
			int randX = RandomRange(0, GWinSizeX);
			int randY = RandomRange(0, GWinSizeY);

			// 화면 좌표를 월드 좌표로 변환
			Vec2 randPos = GET_SINGLE(SceneManager)->ScreenToWorld({ (float)randX, (float)randY });

			// 오브젝트 풀에서 폭탄 객체 꺼내오기
			BombObj* bombObj = GET_SINGLE(ObjectPool)->Get<BombObj>(L"BombObj");

			// 데미지 및 위치 설정
			bombObj->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));
			bombObj->SetPos(randPos);
			bombObj->SetAttackDelay(_info._duration); // 3초 후 폭발

			// 게임 오브젝트로 등록
			GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(bombObj);

		}
		// 마지막 발사 시간 갱신
		_lastAttackTime = _sumTime;
	}
}

/// @brief Bomb 무기 자체는 별도 렌더링 없음 (폭탄 오브젝트가 처리)
void Bomb::Render(HDC hdc)
{
	// 폭탄은 BombObj가 직접 렌더링하므로 이쪽은 비워둠
}

// ------------------------------
// 향후 무기 강화 시 사용하는 함수들
// ------------------------------

/// @brief 무기 장착 시 효과 (레벨에 따른 효과 적용)
void Bomb::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_baseInfo._level);

	// 방어구 같이 플레이어한테 치명타 데미지 증가나 치명타 확률증가가 있으면
	// 여기서 적용하는게 맞을듯
}

/// @brief 무기 해제 시 효과 (현재는 효과 없음)
void Bomb::OnUnequipEffect(Player& player)
{
	// 강화 효과 해제 등 처리 가능 (현재 없음)
	// 무기류는 일단 해제 시 특별한 효과가 없으므로 비워둠
	
}

/// @brief 레벨업 효과 적용용 함수 (예: 쿨타임 감소, 공격 범위 증가 등)
void Bomb::ApplyEffect()
{
	// 추후 강화 기능 구현 시 여기에 적용
	// 생각해보니 레벨업을 하면 레벨을 올리고 OnEquipEffect 이걸 호출해서 적용하는데 필요할까?
}

/// @brief Bomb 고유 능력 사용 (예: 폭탄을 수동 폭발시키는 등)
void Bomb::UseAbility(const Player& player)
{
	// 추후 수동 발동 액티브 스킬용
}

void Bomb::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const AOEEquipInfo& info)
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

void Bomb::ApplyEffectByLevel(int32 level)
{
	if (level < 1 || level > 7)
		return;

	// 레벨에 따른 효과 적용
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

			case EffectType::AttackSpeedUp:					// 공격 속도 증가
				_info._coolTime = max(0.05f, _info._coolTime * (1.f - effect._value));
				break;
			case EffectType::RangeIncrease:					// 공격 범위 증가
				_info._range += effect._intValue;
				break;
			case EffectType::SpecialAbility:				// 특수 능력 활성화
				_isSpecialAbility = true;					// BombObj에서 처리
				break;
			default:										// 없는 경우 경고 메시지
				assert(false && "Unhandled EffectType in ApplyEffectByLevel()");
				break;
			}
		}
	}
}
