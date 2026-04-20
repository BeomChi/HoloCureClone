#pragma once
#include "../Item.h"

class Player;


// 무기 강화시 적용되는 효과들
enum class EffectType
{
	DamageBoost,				// 공격력 배율 증가 (데미지 x%)
	IncreaseProjectileCount,	// 투사체 수 증가
	PierceCountUp,				// 최대 관통 수 증가
	BounceOnMaxPierce,			// 투사체가 최대 관통 후 도탄
	AttackSpeedUp,				// 공격 쿨타임 감소 (공격 속도 증가)
	DelayedDamage,				// 데미지를 지연시켜 주기적으로 적용 (DoT 느낌)
	RangeIncrease,				// 공격 범위 증가
	Stop,						// 적을 잠시 멈추게 함 (넉백 후 정지 효과 등)
	DurationIncrease,			// 지속 시간 증가 (예: DoT 효과의 지속 시간 연장)
	Probability,				// 확률 기반 효과 (예: 20% 확률로 추가 효과 발동)
	SpecialAbility,				// 특수 능력 활성화 (예: 특정 기술 사용 가능)
	None,						// 효과 없음 (레벨업에 특별한 변화가 없을 때 사용)
};

struct EquipEffect {
	EffectType _type = EffectType::None;

	// 이 부분 그만 까먹자 자꾸 1.2 , 1.5 이렇게 값넣지 말자
	float _value = 0.f;		// 예: 대미지 20% → 0.2, 공격속도 25% → 0.25
	int _intValue = 0;		// 예: 탄환 수 증가, 관통 수 증가

	wstring _desc;		// UI 툴팁에 쓸 설명
};

struct EquipmentBaseInfo
{
	wstring _name;								// 이름
	WeaponType _weaponType = WeaponType::None;  // 무기 타입
	int32 _level = 1;							// 레벨
	int32 _maxLevel = 7;						// 최대 레벨
};

class Equipment
{
public:
	Equipment();
	virtual ~Equipment() ;

	virtual void Init() ;
	virtual void Update() ;
	virtual void Render(HDC hdc) ;

	Equip GetType() { return _equipType; }

	bool IsMaxLevel();

	// 장비 착용 시 패시브 효과 적용
	virtual void OnEquipEffect(Player& player) abstract;

	// 장비 해제 시 효과 제거
	virtual void OnUnequipEffect(Player& player) abstract;

	// 장착 상태에서의 기술 사용 (액티브 무기 등)
	virtual void UseAbility(const Player& player) abstract;

	// 장비 정보 설정
	virtual void SetEquipInfo(const EquipmentBaseInfo& baseInfo,const ProjectileEquipInfo& info);
	virtual void SetEquipInfo(const EquipmentBaseInfo& baseInfo,const AOEEquipInfo& info);

	// 장비 정보 초기화
	//void ResetEquipInfo();

	// 장비 업그레이드
	virtual void UpgradeEquip(Player& player);

	// 레벨에 따른 효과 적용
	virtual void ApplyEffectByLevel(int32 level) abstract;

	// 레벨에 따른 효과 적용
	virtual void ApplyEffect() abstract;

	// 무기의 최종 데미지 계산
	DamageInfo  CalculateDamge(float dmgMultiplier);

	const int32 GetLevel() { return _baseInfo._level; }
	const int32 GetMaxLevel() { return _baseInfo._maxLevel; }

	const wstring& GetName() { return _baseInfo._name; }
	const unordered_map<int32, vector<EquipEffect>>& GetLevelEffects() { return _levelEffects; }

	int RandomRange(int min, int max)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<int32_t> dist(min, max);

		return dist(mt);
	}

protected:
	EquipmentBaseInfo _baseInfo;					// 장비 기본 정보
	Equip _equipType = Equip::None;					// 장비 타입
	bool _isSpecialAbility = false;					// 특수 능력 활성화 여부

	unordered_map<int32, vector<EquipEffect>> _levelEffects;	// 레벨에 따른 효과
};

