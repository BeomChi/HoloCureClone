#include "pch.h"
#include "EnCurse.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../02.Scene/Scene.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/EnCurseObj.h"
#include "../../../../03.Object/Entity/Player/Player.h"


EnCurse::EnCurse()
{
	_equipType = Equip::Weapon;
}

EnCurse::~EnCurse()
{
}

/// @brief 저주 무기(EnCurse) 초기화
/// @details 일정 쿨타임마다 플레이어 앞방향으로 저주 투사체(EnCurseObj)를 발사
void EnCurse::Init()
{
	SetEquipInfo({
		L"EnCurse", // 무기 이름
		WeaponType::Multishot,  // 무기 타입 (다중 발사형)
		1,          // 초기 레벨
		7,          // 최대 레벨
		},

		{
		1,          // 투사체 수
		0,          // 관통수

		1,          // 투사체 크기
		3,          // 쿨타임 (초)
		1           // 데미지 배율
		});

	// 레벨별 효과 초기화
	_levelEffects[1] =
	{
		{
			EffectType::None,
			0.f,
			0,
			L"전방으로 저주받은 에너지 덩어리를 발사한다. 적중 시 다른 적에게 또 하나의 저주가 옮겨질 수 있다."
		}
	};
	_levelEffects[2] =
	{
		// 지금은 확률 그게 없으니 일단 값을 박아 넣고 나중에 추가하면 그에 맞춰 값 수정하기
		{
			EffectType::Probability,
			80.f,
			0,
			L"저주 체인 확률이 80%로 상승"
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
			0.f,
			125,
			L"저주 체인의 최대 범위가 125px로 증가"
		},
	};
	_levelEffects[5] =
	{
		{
			EffectType::IncreaseProjectileCount,
			0.f,
			1,
			L"저주를 2개 발사하고 체인 확률이 90%로 상승"
		},
		{			
			EffectType::Probability,
			90.f,
			0,
			L""
		}
	};
	_levelEffects[6] =
	{
		{
			EffectType::AttackSpeedUp,
			0.15f,
			0,
			L"공격 주기가 15% 감소"
		}
	};
	_levelEffects[7] =
	{
		{
			EffectType::IncreaseProjectileCount,
			0.f,
			1,
			L"저주를 3개 발사하고 체인될때마다 대미지가 10% 상승"
		},
		{
			// 아무래도 각 무기별로 7렙떄 특수 기능들이 활성화 되는거 같으니 그걸 bool로 해서 각 무기별로 만들자
			EffectType::SpecialAbility,
			0.1f,
			0,
			L""
		}
	};

	// 미리 만들어 놓자
	/*for (int i = 0; i < 5; i++)
	{
		GET_SINGLE(ObjectPool)->CreateNewObject(L"EnCurseObj");
	}*/
}

/// @brief 매 프레임마다 호출되며, 쿨타임이 지나면 저주 투사체를 생성
void EnCurse::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (!_fire)
	{
		_sumTime += deltaTime;
		if (_sumTime - _lastAttackTime >= _info._coolTime)
		{
			_currentFireCount = 0;
			_curBurstTime = 0.f;
			_fire = true;

			_lastAttackTime = _sumTime;
		}
	}
	else
	{
		// 연사 중일 때
		_curBurstTime += deltaTime;
		if (_curBurstTime >= _burstInterval)
		{
			CreateCurse();
			_curBurstTime = 0.f;
			_currentFireCount++;

			if (_currentFireCount >= _info._count)
			{
				_fire = false;
			}
		}

	}
}

/// @brief 무기 자체 렌더링은 없음 (투사체가 시각 처리)
void EnCurse::Render(HDC hdc)
{
	// EnCurseObj가 직접 렌더링을 처리
}

/// @brief 무기 장착 시 효과 적용
/// @details 무기 레벨에 따라 강화 효과 적용
void EnCurse::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_baseInfo._level);

	cout << "----------------------" << endl;
	cout << "레벨 :" << _baseInfo._level << endl;
	cout << "최대 레벨 :" << _baseInfo._maxLevel << endl;
	cout << "투사체 수 :" << _info._count << endl;
	cout << "범위 :" << _info._range << endl;
	cout << "쿨타임 :" << _info._coolTime << endl;
	cout << "관통 :" << _info._pierceCount << endl;
	cout << "데미지 배율 : " << _info._dmgMultiplier << endl;
	cout << "전이 거리 : " << _transition_Range << endl;
	cout << "전이 확률 : " << _transition_Probability << endl;
	cout << "전이 데미지 증가 : " << _transition_Damage_Increase_Rate << endl;
}

/// @brief 무기 해제 시 효과 (현재 미사용)
void EnCurse::OnUnequipEffect(Player& player)
{
	// 추후 해제 시 디버프 제거 등 추가 가능
}

void EnCurse::CreateCurse()
{
	// 오브젝트 풀에서 EnCurseObj를 가져옴
	EnCurseObj* enCurseObj = GET_SINGLE(ObjectPool)->Get<EnCurseObj>(L"EnCurseObj");

	// 발사 위치 설정 (플레이어 앞 방향)
	enCurseObj->SetPos(GetFirePos());

	// 플레이어 방향에 따라 투사체 방향 설정
	Dir dir = GET_SINGLE(GameManager)->GetPlayer()->GetDir();
	if (dir == DIR_LEFT)
		enCurseObj->SetState(DirState::Left);
	else
		enCurseObj->SetState(DirState::Right);

	// 데미지 계산 후 설정
	enCurseObj->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));

	enCurseObj->SetTransitionProbability(_transition_Probability);
	enCurseObj->SetTransitionRange(_transition_Range);
	enCurseObj->SetTransitionDamageIncreaseRate(_transition_Damage_Increase_Rate); // 체인 시 대미지 증가율 설정
	enCurseObj->SetIsAbility(_isSpecialAbility); // 특수 능력 활성화 여부 설정



	// 오브젝트 매니저에 등록
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(enCurseObj);
}

/// @brief 투사체 발사 위치 계산
/// @details 플레이어의 앞 방향을 기준으로 투사체 생성 위치 설정
/// @return 발사 좌표 (Vec2)
Vec2 EnCurse::GetFirePos()
{
	Vector firePos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();
	Dir dir = GET_SINGLE(GameManager)->GetPlayer()->GetDir();

	if (dir == DIR_LEFT)
		firePos.x += (-1) * _firePosLength;
	else
		firePos.x += 1 * _firePosLength;

	return firePos;
}


void EnCurse::ApplyEffect()
{
}

void EnCurse::UseAbility(const Player& player)
{
}

void EnCurse::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const ProjectileEquipInfo& info)
{
	_baseInfo._name = baseInfo._name;						// 무기 이름
	_baseInfo._weaponType = baseInfo._weaponType;			// 무기 타입
	_baseInfo._level = baseInfo._level;						// 현재 레벨
	_baseInfo._maxLevel = baseInfo._maxLevel;				// 최대 레벨
	_info._count = info._count;						// 투사체 수
	_info._pierceCount = info._pierceCount;			// 관통 수 (투사체가 적을 관통할 수 있는 횟수)

	_info._range = info._range;						// 투사체 크기
	_info._coolTime = info._coolTime;				// 쿨타임 (초 단위)
	_info._dmgMultiplier = info._dmgMultiplier;		// 데미지 배율
}

void EnCurse::ApplyEffectByLevel(int32 level)
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
			case EffectType::IncreaseProjectileCount:				// 투사체 수 증가
				_info._count += effect._intValue;
				break;
			case EffectType::AttackSpeedUp:							// 공격 속도 증가
				_info._coolTime = max(0.05f, _info._coolTime * (1.f - effect._value));
				break;
			case EffectType::RangeIncrease:							// 체인 공격 범위 증가
				_transition_Range = effect._value;					// 저주 체인 범위 증가
				break;
			case EffectType::Probability:							// 체인 확률 증가
				_transition_Probability = effect._value;		    // 저주 체인 확률 증가
				break;
			case EffectType::SpecialAbility:						// 특수 능력 활성화 (예: 저주가 체인될 때마다 대미지 증가)	
				_transition_Damage_Increase_Rate = effect._value;	// 저주 체인 시 대미지 증가율
				_isSpecialAbility = true;	
				break;
			default:												// 없는 경우 경고 메시지
				assert(false && "Unhandled EffectType in ApplyEffectByLevel()");
				break;
			}
		}
	}
}
