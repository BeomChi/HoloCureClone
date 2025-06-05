#pragma once
#include "../Item.h"

class Player;

// 기본 이속도 정해야하고
// 이속 배율에 맞춰서 속도르 맞추고
// 치명타 확률도 만들어야 되네
// 그리고 치뎀도 추가하고
// 기본 공격력 10 
// 배율 1.10 이라고 가정
// 그럼 데미지는 11
// 무기 강화해서 2렙이 되서 20%추가
// 그럼 배율이 1.3이 되서 13

struct EquipInfo
{
	int32 _level = 1;		// 레벨
	int32 _maxLevel = 0;	// 최대 레벨
	int32 _count = 1;		// 생성 갯수
	int32 _dmg = 0;			// 데미지

	float _range = 1;			// 공격 범위		
	float _attackDelay = 0;		// 공격 주기
	float _coolTime = 0;		// 공격 쿨타임
	float _dmgMultiplier = 1;	// 데미지 배율
};

enum class EffectType
{
	DamageBoost,
	IncreaseProjectileCount,
	PierceCountUp,
	BounceOnMaxPierce,
	AttackSpeedUp,
	DelayedDamage,
	None
};

struct EquipEffect {
	EffectType _type = EffectType::None;

	float _value = 0.f;		// 예: 대미지 20% → 0.2, 공격속도 25% → 0.25
	int _intValue = 0;		// 예: 탄환 수 증가, 관통 수 증가

	std::string _desc;		// UI 툴팁에 쓸 설명
};


class Equipment :    public Item
{
	using Super = Item;
public:
	Equipment();
	virtual ~Equipment() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// 장비 착용 시 패시브 효과 적용
	virtual void OnEquipEffect(Player& player) abstract;

	// 장비 해제 시 효과 제거
	virtual void OnUnequipEffect(Player& player) abstract;

	// 장착 상태에서의 기술 사용 (액티브 무기 등)
	virtual void UseAbility(const Player& player) abstract;

	// 장비 정보 설정
	void SetEquipInfo(const EquipInfo& info);

	// 장비 정보 초기화
	void ResetEquipInfo();

	// 장비 업그레이드
	virtual void UpgradeEquip(Player& player);

	void ApplyEffectByLevel(int32 level);


	int32 CalculateDamge();

protected:
	EquipInfo _info;								// 장비 정보
	Equip _equipType = Equip::None;					// 장비 타입

	unordered_map<int32, EquipEffect> _levelEffects;	// 레벨에 따른 효과
};

