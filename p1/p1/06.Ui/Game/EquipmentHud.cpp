#include "pch.h"
#include "EquipmentHud.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/EquipmentManager.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../05.Resource/2D/Sprite.h"
#include "../../06.Ui/Image.h"
#include "../../06.Ui/Game/HpBar.h"
#include "../../06.Ui/Game/EquipmentSlotUi.h"


// 무조건 플레이어 생성된 이후 만들기
EquipmentHud::EquipmentHud()
{
	
}

EquipmentHud::~EquipmentHud()
{
	for (size_t j = 0; j < 2; j++)
	{
		for (EquipmentSlotUi* slot : _slot[j])
		{
			SAFE_DELETE(slot);
		}
		_slot[j].clear();
	}
}

void EquipmentHud::Init()
{
	Super::Init();

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 6; ++i)
		{
			auto* slot = new EquipmentSlotUi();
			slot->SetPos({ 68.f + (23.f * i), 47.f + (28.f *j)});
			AddPanel(slot);
			_slot[j].push_back(slot);
		}
	}
	RefreshSlots();
}

void EquipmentHud::Update()
{
	Super::Update();
	
	
}

void EquipmentHud::Render(HDC hdc)
{
	Super::Render(hdc);
	
	
}

void EquipmentHud::RefreshSlots()
{

	for (size_t j = 0; j < 2; j++)
	{
		const auto& equips = GET_SINGLE(EquipmentManager)->GetGameObjects(j);
		for (size_t i = 0; i < _slot[j].size(); i++)
		{
			if (i < equips.size())
				_slot[j][i]->SetEquipmentSprite(equips[i]);  // 아이콘 + Lv
			else
			{
				if (j == Equip::Weapon)
					_slot[j][i]->SetDefaultWeaponSprite();                 // 빈 칸
				else if (j == Equip::Armor)
					_slot[j][i]->SetDefaultArmorSprite();                  // 빈 칸
			}
				
		}
	}
}



