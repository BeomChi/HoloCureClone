#pragma once
#include "../Equipment.h"


class Sausage :    public Equipment
{
	using Super = Item;
public:
	Sausage();
	virtual ~Sausage() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// 장비 착용 시 패시브 효과 적용
	virtual void OnEquipEffect(Player& player) override;

	// 장비 해제 시 효과 제거
	virtual void OnUnequipEffect(Player& player) override;

	Vec2 GetFirePos();

	void CreateSausage();
	

private:
	AOEEquipInfo _info;

	int8 _count = 0;
	float _sumTime = 0;

	float _firePosLength = 30;
	float _lastAttackTime = 0;
	float _knockbackForce = 0;

	float _deltaTime = 0;

	// Equipment을(를) 통해 상속됨
	virtual void ApplyEffect() override;
	virtual void UseAbility(const Player& player) override;

	// Equipment을(를) 통해 상속됨
	virtual void SetEquipInfo(const EquipmentBaseInfo& baseInfo, const AOEEquipInfo& info) override;
	virtual void ApplyEffectByLevel(int32 level) override;
};

