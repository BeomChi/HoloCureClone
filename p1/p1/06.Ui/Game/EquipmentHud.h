#pragma once
#include "../Panel.h"

class EquipmentSlotUi;

class EquipmentHud : public Panel
{
	using Super = Panel;
public:
	EquipmentHud();
	virtual ~EquipmentHud() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void RefreshSlots();
	


private:
	vector<EquipmentSlotUi*> _slot[2]; // 패널 리스트
};

