#include "pch.h"
#include "EquipmentSlotUi.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/EquipmentManager.h"
#include "../../03.Object/Item/Equipment/Equipment.h"
#include "../../05.Resource/2D/Sprite.h"
#include "../../06.Ui/Image.h"


// 무조건 플레이어 생성된 이후 만들기
EquipmentSlotUi::EquipmentSlotUi()
{
	
}

EquipmentSlotUi::~EquipmentSlotUi()
{
	if (_levelImage != nullptr)
	{
		SAFE_DELETE(_levelImage);
	}

	if (_numberImage != nullptr)
	{
		SAFE_DELETE(_numberImage);
	}
}

void EquipmentSlotUi::Init()
{
	Super::Init();

	
}

void EquipmentSlotUi::Update()
{
	Super::Update();
	
	
}

void EquipmentSlotUi::Render(HDC hdc)
{
	Super::Render(hdc);

	if (_levelImage != nullptr)
		_levelImage->Render(hdc);

	if (_numberImage != nullptr)
		_numberImage->Render(hdc);
}

void EquipmentSlotUi::SetEquipmentSprite(Equipment* eq)
{
	if (eq == nullptr)
		return;
	

	SetSprite(GET_SINGLE(ResourceManager)->GetSprite(eq->GetName()));
	SetSize({ (float)GetSprite()->GetSize().x, (float)GetSprite()->GetSize().y });
	SetLayer(LAYER_UI);

	_levelImage = new Image();
	_levelImage->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"LevelTypeNormal"));
	_levelImage->SetPos({ GetPos().x - (float)GetSprite()->GetSize().x / 2,
		GetPos().y + ((float)GetSprite()->GetSize().y /2) });

	_numberImage = new Image();
	_numberImage->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeNormal" + to_wstring(eq->GetLevel())));
	_numberImage->SetPos({ _levelImage->GetPos().x + 10.f,	_levelImage->GetPos().y + 2 });
}

void EquipmentSlotUi::SetDefaultWeaponSprite()
{
	SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"DefaultWeaponIcon"));
	SetSize({ (float)GetSprite()->GetSize().x, (float)GetSprite()->GetSize().y });
	SetLayer(LAYER_UI);
}

void EquipmentSlotUi::SetDefaultArmorSprite()
{
	SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"DefaultArmorIcon"));
	SetSize({ (float)GetSprite()->GetSize().x, (float)GetSprite()->GetSize().y });
	SetLayer(LAYER_UI);

}




