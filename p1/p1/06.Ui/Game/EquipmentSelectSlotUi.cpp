#include "pch.h"
#include "EquipmentSelectSlotUi.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/EquipmentManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../02.Scene/Scene.h"
#include "../../03.Object/Item/Equipment/Equipment.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../05.Resource/2D/Sprite.h"
#include "../../06.Ui/Image.h"


// 무조건 플레이어 생성된 이후 만들기
EquipmentSelectSlotUi::EquipmentSelectSlotUi(Equipment* eq)
{
	SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"ItemMune"), BS_Default);
	SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"ItemMenuSelect"), BS_Pressed);
	SetSize({(float)_sprites[0]->GetSize().x ,(float)_sprites[0]->GetSize().y});
	SetLayer(LAYER_UI);
	SetKey(L"EquipmentSelectSlotUi");

	_eq = eq;

	_icon = new Image();

	Button::SetOnClick([this]()
		{
			OnClicked();
		});

	//_icon->SetPos({ _pos.x - 200.f,_pos.y - 5 });
	//_icon->SetLayer(LAYER_UI);
	//GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(_icon);
	

	//_iconFrame = new Image();
	//_iconFrame->SetLayer(LAYER_UI);
	
	SetSlot();
}

EquipmentSelectSlotUi::~EquipmentSelectSlotUi()
{
	Clear();
}

void EquipmentSelectSlotUi::Init()
{
	Super::Init();

	
}

void EquipmentSelectSlotUi::Update()
{
	Super::Update();
	
	
}

void EquipmentSelectSlotUi::Render(HDC hdc)
{
	Super::Render(hdc);
	
	//_iconFrame->Render(hdc);
	
	if (_eq)
	{
		int level = _eq->GetLevel();
		const auto& effects = _eq->GetLevelEffects();
		auto it = effects.find(_eq->GetLevel());

		if (it != effects.end())
		{
			for (const auto& eff : it->second)
			{
				//if (eff._desc.empty())
				//	cout << "[DEBUG]텅 비어있는 있네~ 정신나갈거 같네" << endl;
				
				//std::wcout.imbue(std::locale(""));
				//wcout << L"[효과 설명]: " << eff._desc << endl;
				//cout << "길이: " << eff._desc.length() << endl;

				Utils::DrawTextFont(
					hdc,
					{ _pos.x - 120, _pos.y - 15},	// 좌표
					eff._desc,							// 내용
					18,								// 글자 크기
					RGB(255, 255, 255),				// 색상
					L"맑은 고딕",					// 폰트
					310, 68);						// 가로, 세로

			}
		}
	}

	_icon->Render(hdc);
}
/*
void EquipmentSelectSlotUi::ButtonEvent(Ui* ui)
{
	if (_eq == nullptr)
		return;

	Player* player = GET_SINGLE(GameManager)->GetPlayer();

	if (GET_SINGLE(EquipmentManager)->HasEquipment(_eq->GetName()))
	{

		_eq->UpgradeEquip(*player);
	}
	else
	{
		GET_SINGLE(EquipmentManager)->AddEquiment(_eq);
	}

	player->SetChoosingEquipment(false);

	this->SetIsActivity(false);
	ui->SetIsActivity(false);
	_icon->SetIsActivity(false);
	player->CheckLevelUpExp();
}
*/
void EquipmentSelectSlotUi::SetEquipment(Equipment* eq)
{
	if (eq == nullptr)
		return;

	_eq = eq;
	SetSlot();
}

void EquipmentSelectSlotUi::SetSlot()
{
	if (_eq == nullptr)
		return;

	Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(_eq->GetName());
	_icon->SetSprite(sprite);
	_icon->SetSize({ (float)sprite->GetSize().x, (float)sprite->GetSize().y });
	//_icon->SetPos({ _pos.x,_pos.y});
}

void EquipmentSelectSlotUi::Activity()
{
	_icon->SetIsActivity(true);
}

void EquipmentSelectSlotUi::OnClicked()
{
	if (_eq && _onClick)
		_onClick(_eq);
}

void EquipmentSelectSlotUi::Clear()
{
	if (_icon)
		SAFE_DELETE(_icon);

	if (_iconFrame)
		SAFE_DELETE(_iconFrame);
	
	if (_eq)
		_eq = nullptr;
}
