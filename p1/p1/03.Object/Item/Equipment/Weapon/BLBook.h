#pragma once
#include "../Equipment.h"

class BLBookObj;

class BLBook :    public Equipment
{
	using Super = Item;
public:
	BLBook();
	virtual ~BLBook() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// 장비 착용 시 패시브 효과 적용
	virtual void OnEquipEffect(Player& player) override;

	// 장비 해제 시 효과 제거
	virtual void OnUnequipEffect(Player& player) override;

	// Equipment을(를) 통해 상속됨
	virtual void ApplyEffect() override;
	virtual void UseAbility(const Player& player) override;

	// Equipment을(를) 통해 상속됨
	virtual void SetEquipInfo(const EquipmentBaseInfo& baseInfo, const AOEEquipInfo& info) override;
	virtual void ApplyEffectByLevel(int32 level) override;
private:
	// 책 오브젝트 리스트
	vector<BLBookObj*> _blBook;

	// 책 오브젝트 정보
	AOEEquipInfo _info;

	// 책 회전 관련 변수
	float _shieldRoateAngle = 0;
	float _shieldAngle = 0;
	float _playerToshield = 100;

	// 시간 관련 변수
	float _sumTime = 0;
	float _lastAttackTime = 0;

};

