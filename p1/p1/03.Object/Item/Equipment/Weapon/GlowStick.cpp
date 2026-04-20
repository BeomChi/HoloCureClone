#include "pch.h"
#include "GlowStick.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../02.Scene/Scene.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/Stick.h"
#include "../../../../03.Object/Entity/Player/Player.h"


GlowStick::GlowStick()
{
	_equipType = Equip::Weapon;
}

GlowStick::~GlowStick()
{
}

/// @brief 권총 발사 무기 초기화
/// @details 플레이어의 마우스 방향을 향해 탄환을 발사하는 무기.
///          레벨에 따라 다양한 효과가 추가됨.
void GlowStick::Init()
{
	// 무기 기본 정보 설정
	SetEquipInfo({
		L"GlowStick",  // 무기 이름
		WeaponType::Multishot, // 무기 타입 (다중 발사형)
		1,              // 초기 레벨
		7,              // 최대 레벨
		},

		{
		3,              // 최대 발사 수 (한 번 공격당 총 3발)
		5,				// 관통	
		1.f,              // 투사체 크기
		3.f,              // 쿨타임 (초)
		1.f               // 데미지 배율
		});

	// 레벨별 강화 효과 세팅
	_levelEffects[1] = 
	{
		{ 
			EffectType::None,
			0.f,
			0,
			L"가까운 적에게 형광봉을 던진다. 형광봉은 일정 거리 날아갔다가 돌아오며, 최대 히트수 제한에 도달하면 폭발한다."
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
			EffectType::PierceCountUp,
			0.f,
			5,
			L"히트 수 제한 10 상승, 던지는 형광봉의 개수가 2개가 된다."
		},
		{
			EffectType::IncreaseProjectileCount,
			0.f,
			1,
			L"던지는 형광봉의 개수가 2개가 된다."
		}
	};
	_levelEffects[4] = 
	{
		{
			EffectType::RangeIncrease,
			0.25f,
			0,
			L"형광봉의 사이즈가 25% 상승"
		}
	};
	_levelEffects[5] = 
	{
		{ 
			EffectType::IncreaseProjectileCount,
			0.f,
			1, 
			L"던지는 형광봉의 개수가 3개가 된다." 
		}
	};
	_levelEffects[6] = 
	{
		{ 
			EffectType::DamageBoost,
			0.33f,
			0,
			L"대미지 33% 상승"
		}
	};
	_levelEffects[7] =
	{
		{ 
			EffectType::IncreaseProjectileCount,
			0.f,
			1, 
			L"던지는 형광봉의 개수가 4개가 된다"
		}
	};
}

/// @brief 매 프레임 호출, 일정 쿨타임마다 탄환을 마우스 방향으로 연속 발사
void GlowStick::Update()
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
			CreateStick();
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
void GlowStick::Render(HDC hdc)
{
	// Bullet 오브젝트가 렌더링 처리
}

/// @brief 무기 장착 시 레벨 기반 강화 효과 적용
void GlowStick::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_baseInfo._level);
}

/// @brief 무기 해제 시 효과 (현재 구현 없음)
void GlowStick::OnUnequipEffect(Player& player)
{
	// 효과 해제 로직 필요시 작성
}

/// @brief 탄환 발사 위치 계산
/// @details 플레이어 위치 기준 마우스 방향으로 일정 거리(_firePosLength) 떨어진 지점
/// @return Vec2 발사 위치
Vec2 GlowStick::GetFirePos()
{
	Vector firePos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();
	Vector dir = GetMousePosToPlayerDir();

	// 플레이어 위치에서 마우스 방향으로 _firePosLength 만큼 이동
	firePos += dir * _firePosLength;

	return firePos;
}

/// @brief 플레이어 위치에서 마우스 위치를 월드 좌표로 변환 후 방향 벡터 계산
/// @return 정규화된 방향 벡터 (Vec2)
Vec2 GlowStick::GetMousePosToPlayerDir()
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

void GlowStick::CreateStick()
{
	// 오브젝트 풀에서 Bullet 오브젝트를 가져와서 설정
	Stick* bullet = GET_SINGLE(ObjectPool)->Get<Stick>(L"Stick");

	bullet->SetPos(GetFirePos());                  // 발사 위치 설정
	bullet->SetDir(GetMousePosToPlayerDir());      // 마우스 위치 기준 발사 방향 설정
	bullet->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));           // 데미지 설정
	bullet->SetStickPierceCount(_info._pierceCount);         // 관통할 형광봉 횟수 설정
	bullet->SetScale(Vec2{ _info._range ,_info._range });            // 형광봉 크기 설정

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(bullet); // 게임에 등록
}

void GlowStick::ApplyEffect()
{
}

void GlowStick::UseAbility(const Player& player)
{
}

void GlowStick::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const ProjectileEquipInfo& info)
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

void GlowStick::ApplyEffectByLevel(int32 level)
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
			case EffectType::PierceCountUp:					// 히트 수 증가
				_info._pierceCount += effect._intValue;
				break;
			case EffectType::RangeIncrease:					// 공격 범위 증가
				_info._range += effect._value;
				break;
			default:										// 없는 경우 경고 메시지
				assert(false && "Unhandled EffectType in ApplyEffectByLevel()");
				break;
			}
		}
	}
}
