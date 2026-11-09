#include "pch.h"
#include "EquipmentSlotUi.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/EquipmentManager.h"
#include "../../03.Object/Item/Equipment/Equipment.h"
#include "../../06.Ui/Image.h"
#include "../../97.Engin/Resource/Sprite.h"


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

	if (_eq != nullptr)
	{
		_eq = nullptr; // Equipment 객체는 소유권이 없으므로 삭제하지 않고 nullptr로 설정
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
	_eq = eq;

	SetSprite(RESOURCE->Get<Sprite>(_eq->GetName()));
	//SetSize({ (float)GetSprite()->GetSize().x, (float)GetSprite()->GetSize().y });
	SetLayer(LAYER_UI);

	if(_levelImage == nullptr)
		_levelImage = new Image();

	_levelImage->SetSprite(RESOURCE->Get<Sprite>(L"LevelTypeNormal"));
	_levelImage->GetTransform()->SetPosition({ GetTransform()->GetPosition().x - (float)GetSprite()->GetSize().x / 2,
		GetTransform()->GetPosition().y + ((float)GetSprite()->GetSize().y / 2),0 });

	if(_numberImage == nullptr)
		_numberImage = new Image();

	cout << "[DEBUG] EquipmentSlotUi::SetEquipmentSprite - Level: " << _eq->GetLevel() << endl;
	_numberImage->SetSprite(RESOURCE->Get<Sprite>(L"NumberTypeNormal" + to_wstring(_eq->GetLevel())));
	_numberImage->GetTransform()->SetPosition({_levelImage->GetTransform()->GetPosition().x + 10.f,	_levelImage->GetTransform()->GetPosition().y + 2,0});
}

void EquipmentSlotUi::SetDefaultWeaponSprite()
{
	SetSprite(RESOURCE->Get<Sprite>(L"DefaultWeaponIcon"));
	//SetSize({ (float)GetSprite()->GetSize().x, (float)GetSprite()->GetSize().y });
	SetLayer(LAYER_UI);
}

void EquipmentSlotUi::SetDefaultArmorSprite()
{
	SetSprite(RESOURCE->Get<Sprite>(L"DefaultArmorIcon"));
	//SetSize({ (float)GetSprite()->GetSize().x, (float)GetSprite()->GetSize().y });
	SetLayer(LAYER_UI);

}




