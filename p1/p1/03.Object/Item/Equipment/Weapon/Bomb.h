#pragma once
#include "../Equipment.h"


class Bomb :    public Equipment
{
	using Super = Item;
public:
	Bomb();
	virtual ~Bomb() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// 장비 착용 시 패시브 효과 적용
	virtual void OnEquipEffect(Player& player) override;

	// 장비 해제 시 효과 제거
	virtual void OnUnequipEffect(Player& player) override;



private:
	bool _fire = false;
	int32 _fireCount = 0;
	float _sumTime = 0;

	float _firePosLength = 30;
	float _lastAttackTime = 0;

	// Equipment을(를) 통해 상속됨
	void ApplyEffect() override;
	void UseAbility(const Player& player) override;
};

