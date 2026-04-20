#pragma once
#include "../Equipment.h"

class Miasma;

class SpiderCooking :    public Equipment
{
	using Super = Item;
public:
	SpiderCooking();
	virtual ~SpiderCooking() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// 장비 착용 시 패시브 효과 적용
	virtual void OnEquipEffect(Player& player) override;

	// 장비 해제 시 효과 제거
	virtual void OnUnequipEffect(Player& player) override;

private:
	AOEEquipInfo _info;
	Miasma* _miasma = nullptr;


	// Equipment을(를) 통해 상속됨
	virtual void ApplyEffect() override;
	virtual void UseAbility(const Player& player) override;

	// Equipment을(를) 통해 상속됨
	virtual void SetEquipInfo(const EquipmentBaseInfo& baseInfo, const AOEEquipInfo& info) override;
	virtual void ApplyEffectByLevel(int32 level) override;
};

