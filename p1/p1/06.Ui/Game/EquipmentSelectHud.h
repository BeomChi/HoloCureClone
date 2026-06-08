#pragma once
#include "../Panel.h"
#include "Signal.hpp"

class EquipmentSelectSlotUi;
class Equipment;

class EquipmentSelectHud : public Panel
{
	using Super = Panel;
public:
	EquipmentSelectHud();
	virtual ~EquipmentSelectHud() override;


	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void Reset() override;
	void Clear();

private:
	void OnEquipmentSelected(Equipment* eq);

private:
	vector<EquipmentSelectSlotUi*> _slot; // 패널 리스트
	Connection _ActivityConn;
};

