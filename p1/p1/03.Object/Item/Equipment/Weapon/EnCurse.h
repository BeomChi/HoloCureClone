#pragma once
#include "../Equipment.h"


class EnCurse :    public Equipment
{
	using Super = Item;
public:
	EnCurse();
	virtual ~EnCurse() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// 장비 착용 시 패시브 효과 적용
	virtual void OnEquipEffect(Player& player) override;

	// 장비 해제 시 효과 제거
	virtual void OnUnequipEffect(Player& player) override;

	void CreateCurse();

	Vec2 GetFirePos();
	//Vec2 GetMousePosToPlayerDir();

private:
	ProjectileEquipInfo _info;

	bool _fire = false;

	int32 _currentFireCount = 0;

	float _sumTime = 0;
	float _burstInterval = 0.2f;
	float _curBurstTime = 0.f;

	float _firePosLength = 30;
	float _lastAttackTime = 0;

	int32 _transition_Range = 100;	// 체인 거리
	float _transition_Probability = 100.f;			// 체인 확률
	float _transition_Damage_Increase_Rate = 0.f;

	// Equipment을(를) 통해 상속됨
	virtual void ApplyEffect() override;
	virtual void UseAbility(const Player& player) override;

	// Equipment을(를) 통해 상속됨
	virtual void SetEquipInfo(const EquipmentBaseInfo& baseInfo, const ProjectileEquipInfo& info) override;
	virtual void ApplyEffectByLevel(int32 level) override;
};

