#pragma once
#include "../Image.h"

class Equipment;


class EquipmentSlotUi : public Image
{
	using Super = Image;
public:
	EquipmentSlotUi();
	virtual ~EquipmentSlotUi() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetEquipmentSprite(Equipment* eq);
	void SetDefaultWeaponSprite();
	void SetDefaultArmorSprite();
	


private:
	Image* _levelImage = nullptr; // 레벨 이미지
	Image* _numberImage = nullptr; // 레벨 이미지
	Equipment* _eq;
};

