#include "pch.h"
#include "EquipmentSelectHud.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/EquipmentManager.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../03.Object/Item/Equipment/Equipment.h"
#include "../../05.Resource/2D/Sprite.h"
#include "../../06.Ui/Image.h"
#include "../../06.Ui/Game/HpBar.h"
#include "../../06.Ui/Game/EquipmentSelectSlotUi.h"


// 무조건 플레이어 생성된 이후 만들기
EquipmentSelectHud::EquipmentSelectHud()
{
	auto equips = GET_SINGLE(EquipmentManager)->GetRandomEquipments();

	for (int i = 0; i < equips.size(); i++)
	{
		EquipmentSelectSlotUi* slot = new EquipmentSelectSlotUi(equips[i]);
		slot->SetPos({ 400.f, 200.f + (i * 65) });
		slot->GetIcon()->SetPos({ slot->GetPos().x - 160, slot->GetPos().y + 5 });
		_slot.push_back(slot);
		AddPanel(slot);

		slot->SetOnClick(
			[this, slot]() 
			{
				slot->ButtonEvent(this);
			});
	}

	GET_SINGLE(GameManager)->GetPlayer()->SetEquipmentSelectHud(this);
}

EquipmentSelectHud::~EquipmentSelectHud()
{
	Clear();
}

void EquipmentSelectHud::Init()
{
	Super::Init();

	
}

void EquipmentSelectHud::Update()
{
	Super::Update();
	
	
}

void EquipmentSelectHud::Render(HDC hdc)
{
	Super::Render(hdc);
	
	
}

void EquipmentSelectHud::Reset()
{
	auto equips = GET_SINGLE(EquipmentManager)->GetRandomEquipments();

	for (int i = 0; i < equips.size(); i++)
	{
		_slot[i]->SetIsActivity(true);
		_slot[i]->SetEquipment(equips[i]);
		_slot[i]->Activity();
	}
}

void EquipmentSelectHud::Clear()
{
	_slot.clear();
}
