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

	// _slot은 로직 처리용
	// _panel은 실제로 화면에 보이는 용
	for (int i = 0; i < equips.size(); i++)
	{
		EquipmentSelectSlotUi* slot = new EquipmentSelectSlotUi(equips[i]);
		slot->SetPos({ 400.f, 200.f + (i * 65) });
		slot->GetIcon()->SetPos({ slot->GetPos().x - 160, slot->GetPos().y + 5 });
		slot->SetKey(format(L"slot{0}", i));
		_slot.push_back(slot);	
		AddPanel(slot);	

		slot->SetOnClick(
			[this](Equipment* eq)
			{
				OnEquipmentSelected(eq);
			});
	}
	{
		_ActivityConn = (GET_SINGLE(GameManager)->GetPlayer()->OnEquipmentSelectHud += [this](bool isActive)
			{
				this->SetIsActivity(isActive);
				this->Reset();
			});
	}

}

EquipmentSelectHud::~EquipmentSelectHud()
{
	Clear();
	_ActivityConn.Disconnect();
	cout << "[DeBUG] EquipmentSelectHud 소멸자 호출. 슬롯 메모리 해제 완료." << endl;
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
	}
}

void EquipmentSelectHud::Clear()
{
	_slot.clear();
}

void EquipmentSelectHud::OnEquipmentSelected(Equipment* eq)
{
	if (eq == nullptr)
		return;

	Player* player = GET_SINGLE(GameManager)->GetPlayer();

	GET_SINGLE(EquipmentManager)->AddEquiment(eq);


	player->SetChoosingEquipment(false);

	this->SetIsActivity(false);
	
	// 선택이 끝나면 게임 상태를 Playing으로 변경
	GET_SINGLE(GameManager)->SetState(GameState::Playing);

	player->CheckLevelUpExp();
}
