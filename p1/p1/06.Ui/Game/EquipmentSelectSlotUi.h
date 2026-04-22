#pragma once
#include "../Button.h"

class Equipment;
class Image;

class EquipmentSelectSlotUi : public Button
{
	using Super = Button;
public:
	EquipmentSelectSlotUi(Equipment* eq);
	virtual ~EquipmentSelectSlotUi() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	//void ButtonEvent(Ui* ui);
	void SetEquipment(Equipment* eq);
	void SetSlot();
	Image* GetIcon() { return _icon; }
	void Activity();

	Equipment* GetEquipment() { return _eq; }
	void SetOnClick(function<void(Equipment*)> func) { _onClick = func; }

	void Clear();
private:
	void OnClicked();

private:
	Equipment* _eq = nullptr;;
	Image* _icon = nullptr;
	Image* _iconFrame = nullptr;

	function<void(Equipment*)> _onClick;
};

