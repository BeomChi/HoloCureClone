#include "pch.h"
#include "BLBook.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../02.Scene/Scene.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/BLBookObj.h"
#include "../../../../03.Object/Entity/Player/Player.h"





BLBook::BLBook()
{
	_equipType = Equip::Weapon;
}

BLBook::~BLBook()
{
}

/// @brief 회전하는 책(BLBook) 무기 초기화
/// @details 일정 수의 책이 플레이어 주변을 회전하며 지속적으로 데미지를 주는 구조
void BLBook::Init()
{
	// 무기 정보 초기화
	SetEquipInfo({
		L"BLBook",				 // 무기 이름
		WeaponType::Multishot,	 // 무기 타입 (다중 발사형)
		1,						 // 초기 레벨
		7,						 // 최대 레벨
		},

		{
		3,						 // 회전하는 책의 수
		1.f,					 // 공격 범위
		7.f,					 // 쿨타임 (책은 지속 공격이라 무시될 수 있음)
		5.f,					 // 지속시간
		0.f,					 // 공격 주기(지속데미지형인 경우)
		1.f						 // 데미지 배율
		});
	_levelEffects[1] =
	{
		{
			EffectType::None,
			0.f,
			0,
			L"주기적으로 캐릭터 주위를 공전하며 닿은 적에게 대미지를 주고 약한 넉백을 가하는 BL 책이 생성된다"
		}
	};
	_levelEffects[2] =
	{
		{
			EffectType::IncreaseProjectileCount,
			0.f,
			1,
			L"소환되는 책의 개수가 1개 추가"
		}
	};
	_levelEffects[3] =
	{
		{
			EffectType::DamageBoost,
			0.3f,
			0,
			L"대미지 30% 상승, 지속시간이 1초 상승"
		},
		{
			EffectType::DurationIncrease,
			1.f,
			0,
			L""
		}
	};

	_levelEffects[4] =
	{
		{
			EffectType::IncreaseProjectileCount,
			0.f,
			1,
			L"소환되는 책의 개수가 1개 추가"
		}
	};
	_levelEffects[5] =
	{
		{
			EffectType::DamageBoost,
			0.4f,
			0,
			L"대미지 40% 상승"
		}
	};
	_levelEffects[6] =
	{
		{
			EffectType::IncreaseProjectileCount,
			0.f,
			1,
			L"소환되는 책의 개수가 1개 추가."
		}
	};
	_levelEffects[7] =
	{
		{
			EffectType::DamageBoost,
			0.4f,
			0,
			L"대미지 40% 상승"
		},
	};

	// 책 간의 각도 간격 계산 (예: 3개면 120도 간격)
	_shieldAngle = 360 / _info._count;

	// 플레이어와 책 사이의 거리
	_playerToshield = 100;
	_sumTime = 100;
}

/// @brief 책 오브젝트들을 순회하며 위치 업데이트 및 생성
void BLBook::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime - _lastAttackTime >= _info._coolTime)
	{
		for (int i = 0; i < _info._count; i++)
		{
			// 책이 아직 생성되지 않았거나 비활성화된 경우 새로 생성
			if (i >= _blBook.size())
			{
				auto* obj = GET_SINGLE(ObjectPool)->Get<BLBookObj>(L"BLBook");
				obj->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));
				GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(obj);
				_blBook.push_back(obj);
			}
			else if (_blBook[i] == nullptr || !_blBook[i]->GetIsActivity())
			{
				_blBook[i] = GET_SINGLE(ObjectPool)->Get<BLBookObj>(L"BLBook");
				_blBook[i]->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));
				_blBook[i]->SetDuration(_info._duration); // 지속시간 설정
			}
		}
		_lastAttackTime = _sumTime;		 // 마지막 공격 시간 갱신
	}

	for (int i = 0; i < _info._count; i++)
	{
		if (_blBook[i] == nullptr || !_blBook[i]->GetIsActivity())
			continue;

		// 플레이어 기준 위치 계산
		Vector shieldPos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();

		// 회전각 업데이트 (프레임마다 증가, 초당 15도)
		_shieldRoateAngle += (15 * deltaTime) * PI / 180;

		// 현재 책의 각도 계산 (기준 각 + 개별 오프셋)
		float shieldDinstance = (i * _shieldAngle) * PI / 180;

		// 극좌표 → 직교좌표 변환 (원형 회전 위치 계산)
		shieldPos.x += cos(_shieldRoateAngle + shieldDinstance) * _playerToshield;
		shieldPos.y += sin(_shieldRoateAngle + shieldDinstance) * _playerToshield;

		// 위치 적용
		_blBook[i]->SetPos(shieldPos);

	}
	
}


/// @brief BLBook 자체는 렌더링 없음 (투사체가 처리함)
void BLBook::Render(HDC hdc)
{
	// 따로 무기 오브젝트를 화면에 그리진 않음
}

// ------------------------------
// 향후 무기 강화 시 사용하는 함수들
// ------------------------------

/// @brief 무기 장착 시 효과 (레벨에 따른 효과 적용)
void BLBook::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_baseInfo._level);

	if (_blBook.size() < _info._count)
	{
		auto* obj = GET_SINGLE(ObjectPool)->Get<BLBookObj>(L"BLBook");
		obj->SetDamageInfo(CalculateDamge(_info._dmgMultiplier));
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(obj);
		_blBook.push_back(obj);
	}

	_shieldAngle = 360 / _info._count;
	cout << "----------------------" << endl;
	cout <<"레벨 :" <<_baseInfo._level << endl;
	cout <<"최대 레벨 :" <<_baseInfo._maxLevel << endl;
	cout <<"투사체 수 :" <<_info._count << endl;
	cout <<"범위 :" <<_info._range << endl;
	cout <<"쿨타임 :" <<_info._coolTime << endl;
	cout <<"지속시간 :" <<_info._duration << endl;
	cout <<"공격 주기 :" <<_info._attackDelay << endl;
	cout <<"데미지 배율 : " <<_info._dmgMultiplier << endl;

	// 방어구 같이 플레이어한테 치명타 데미지 증가나 치명타 확률증가가 있으면
	// 여기서 적용하는게 맞을듯
}

/// @brief 무기 해제 시 효과 (현재는 효과 없음)
void BLBook::OnUnequipEffect(Player& player)
{
	// 강화 효과 해제 등 처리 가능 (현재 없음)
	// 무기류는 일단 해제 시 특별한 효과가 없으므로 비워둠
	

}

/// @brief 레벨업 효과 적용용 함수 (예: 쿨타임 감소, 공격 범위 증가 등)
void BLBook::ApplyEffect()
{
	// 추후 강화 기능 구현 시 여기에 적용
	// 생각해보니 레벨업을 하면 레벨을 올리고 OnEquipEffect 이걸 호출해서 적용하는데 필요할까?
}

/// @brief Bomb 고유 능력 사용 (예: 폭탄을 수동 폭발시키는 등)
void BLBook::UseAbility(const Player& player)
{
	// 추후 수동 발동 액티브 스킬용
}


void BLBook::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const AOEEquipInfo& info)
{
	_baseInfo._name = baseInfo._name;						// 무기 이름
	_baseInfo._weaponType = baseInfo._weaponType;			// 무기 타입
	_baseInfo._level = baseInfo._level;						// 현재 레벨
	_baseInfo._maxLevel = baseInfo._maxLevel;				// 최대 레벨
	_info._count = info._count;						// 투사체 수

	_info._range = info._range;						// 공격 범위
	_info._coolTime = info._coolTime;				// 쿨타임 (초 단위)
	_info._duration = info._duration;				// 지속 시간 (폭탄이 유지되는 시간)
	_info._attackDelay = info._attackDelay;			// 공격 주기 (지속 데미지형인 경우)
	_info._dmgMultiplier = info._dmgMultiplier;		// 데미지 배율 (기본 1.0, 레벨업 시 증가)
}

/// @brief 레벨별 강화 효과를 적용하는 함수
/// @param level 현재 적용할 레벨
/// @details 레벨 효과 타입에 따라 무기 능력치를 변경
void BLBook::ApplyEffectByLevel(int32 level)
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
