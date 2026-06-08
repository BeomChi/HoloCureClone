#include "pch.h"
#include "PistolShoot.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../02.Scene/Scene.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/Bullet.h"
#include "../../../../03.Object/Entity/Player/Player.h"


PistolShoot::PistolShoot()
{
	_equipType = Equip::Weapon;
}

PistolShoot::~PistolShoot()
{
}

/// @brief 권총 발사 무기 초기화
/// @details 플레이어의 마우스 방향을 향해 탄환을 발사하는 무기.
///          레벨에 따라 다양한 효과가 추가됨.
void PistolShoot::Init()
{
	// 무기 기본 정보 설정
	SetEquipInfo({
		L"PistolShoot",			 // 무기 이름
		WeaponType::Multishot,   // 무기 타입 (다중 발사형)
		1,						 // 초기 레벨
		6,						 // 최대 레벨
		},

		{
		3,						 // 최대 발사 수 (한 번 공격당 총 3발)
		0,						 // 관통 (탄환이 적을 통과할 수 있는 횟수)
		1.f,						 // 투사체 크기
		3.f,						 // 쿨타임 (초)
		1.f						 // 데미지 배율
		});

		// 레벨별 강화 효과 세팅
		// 현재 강화되는게 값이 2개 이상이면 2번쨰부터 누락됨 그래서 vector로 변경해서 해야함
		_levelEffects[1] =
		{
			EquipEffect{
			EffectType::None,
			0.f,
			0,
			L"아메의 기본 무기."
			}
		};
		_levelEffects[2] =
		{
			EquipEffect
			{
				EffectType::IncreaseProjectileCount,
				0.f,
				2,
				L"발사 수가 2 증가하며, 각 탄환의 최대 관통 수가 1회 증가한다."
			},
			{
				EffectType::PierceCountUp,
				0.f,
				1,
				L""
			}
		};
		_levelEffects[3] =
		{
			EquipEffect
			{
				EffectType::DamageBoost,
				0.2f,
				0,
				L"대미지 20% 상승"
			}
		};
		_levelEffects[4] =
		{
			EquipEffect
			{
				EffectType::SpecialAbility,
				0.f,
				0,
				L"탄환이 최대 관통 수에 도달하면 도탄된다."
			}
		};
		_levelEffects[5] =
		{
			EquipEffect
			{
			EffectType::AttackSpeedUp,
			0.25f,
			0,
			L"각 탄환의 최대 관통 수가 1회 증가하며, 공격 주기가 25% 감소한다."
			}
			,
			EquipEffect
			{
				EffectType::PierceCountUp,
				0.f,
				1,
				L""
			}
		};
		_levelEffects[6] =
		{
			EquipEffect
			{
				EffectType::DamageBoost,
				0.2f,
				0,
				L"대미지 20% 상승"
			}
		};
}

/// @brief 매 프레임 호출, 일정 쿨타임마다 탄환을 마우스 방향으로 연속 발사
void PistolShoot::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

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
			CreateBullet();

			_curBurstTime = 0.f;
			_currentFireCount++;

			if (_currentFireCount >= _info._count)
			{
				_fire = false;
			}
		}

	}

}

/// @brief 무기 자체 렌더링 없음 (탄환이 개별 렌더링 담당)
void PistolShoot::Render(HDC hdc)
{
	// Bullet 오브젝트가 렌더링 처리
}

/// @brief 무기 장착 시 레벨 기반 강화 효과 적용
void PistolShoot::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_baseInfo._level);
}

/// @brief 무기 해제 시 효과 (현재 구현 없음)
void PistolShoot::OnUnequipEffect(Player& player)
{
	// 효과 해제 로직 필요시 작성
}

/// @brief 탄환 발사 위치 계산
/// @details 플레이어 위치 기준 마우스 방향으로 일정 거리(_firePosLength) 떨어진 지점
/// @return Vec2 발사 위치
Vec2 PistolShoot::GetFirePos()
{
	Vector firePos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();
	Vector dir = GetMousePosToPlayerDir();

	// 플레이어 위치에서 마우스 방향으로 _firePosLength 만큼 이동
	firePos += dir * _firePosLength;

	return firePos;
}

/// @brief 플레이어 위치에서 마우스 위치를 월드 좌표로 변환 후 방향 벡터 계산
/// @return 정규화된 방향 벡터 (Vec2)
Vec2 PistolShoot::GetMousePosToPlayerDir()
{
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vec2 mouseWorldPos = GET_SINGLE(SceneManager)->ScreenToWorld(mousePos);
	Vector playerPos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();

	float dirX = mouseWorldPos.x - playerPos.x;
	float dirY = mouseWorldPos.y - playerPos.y;

	Vector dir = { dirX, dirY };
	dir.Normalize();

	return dir;
}

void PistolShoot::CreateBullet()
{
	// 오브젝트 풀에서 Bullet 오브젝트를 가져와서 설정
	Bullet* bullet = GET_SINGLE(ObjectPool)->Get<Bullet>(L"Bullet");

	bullet->SetPos(GetFirePos());                  // 발사 위치 설정
	bullet->SetDir(GetMousePosToPlayerDir());      // 마우스 위치 기준 발사 방향 설정
	bullet->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));           // 데미지 설정
	bullet->SetPierceCount(_info._pierceCount);		// 관통 수 설정

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(bullet); // 게임에 등록
}

void PistolShoot::ApplyEffect()
{
}

void PistolShoot::UseAbility(const Player& player)
{
}

void PistolShoot::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const ProjectileEquipInfo& info)
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

void PistolShoot::ApplyEffectByLevel(int32 level)
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
			case EffectType::PierceCountUp:							// 관통 수 증가
				_info._pierceCount += effect._intValue;
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
