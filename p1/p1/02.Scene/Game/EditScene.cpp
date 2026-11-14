#include "pch.h"
#include "EditScene.h"
#include "../../01.Manager/InputManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/SpawnManager.h"
#include "../../01.Manager/StageManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/EquipmentManager.h"
#include "../../01.Manager/UiLayoutManager.h"
#include "../../03.Object/Item/Experinence/ExperinenceObject.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../03.Object/ObjectPool/ObjectPool.h"
#include "../../03.Object/Spawner/Spawner.h"
#include "../../03.Object/Entity/Monster/Fubura.h"
#include "../../03.Object/Entity/Monster/Shubangelion.h"
#include "../../03.Object/Entity/Monster/NormalMonster.h"
#include "../../03.Object/Projectile/Laser.h"
#include "../../03.Object/Item/Equipment/Weapon/EliteLavaBucket.h"
#include "../../03.Object/Item/Equipment/Weapon/PistolShoot.h"
#include "../../03.Object/Item/Equipment/Weapon/BLBook.h"
#include "../../03.Object/Item/Equipment/Weapon/EnCurse.h"
#include "../../03.Object/Item/Equipment/Weapon/SpiderCooking.h"
#include "../../03.Object/Item/Equipment/Weapon/FanBeam.h"
#include "../../03.Object/Item/Equipment/Weapon/Bomb.h"
#include "../../03.Object/Item/Equipment/Weapon/PsychoAxe.h"
#include "../../03.Object/Item/Equipment/Weapon/Sausage.h"
#include "../../03.Object/Item/Equipment/Weapon/WamyWater.h"
#include "../../03.Object/Item/Equipment/Weapon/Trident.h"
#include "../../04.Component/2D/SpriteRenderer.h"
#include "97.Engin/Resource/Texture.h"
#include "97.Engin/Resource/Animation.h"
#include "97.Engin/Resource/Sprite.h"
#include "97.Engin/Component/Animation/Animator.h"
#include "97.Engin/Component/Renderer/MeshRenderer.h"
#include "97.Engin/Component/Camera/Camera.h"
#include "../../05.Resource/Sound/Sound.h"
#include "../../06.Ui/Button.h"
#include "../../06.Ui/Game/PlayerHudPanel.h"
#include "../../06.Ui/Game/EquipmentHud.h"
#include "../../06.Ui/Game/EquipmentSelectHud.h"
#include "../../06.Ui/Game/GameOverHud.h"
#include "../../06.Ui/Panel.h"


EditScene::EditScene()
{
	
}

EditScene::~EditScene()
{
	// 프로그램 종료시에는 GAME에서 최종적으로 정리
	if (GAME != nullptr)
	{
		EQUIPMENT->Clear();
		GAMEMANAGER->SetPlayer(nullptr);
	}

	SAFE_DELETE(_uiLayoutManager);

	Clear();
}

void EditScene::Init()
{
	Super::Init();
	{
		Sprite* sprite = RESOURCE->Get<Sprite>(L"Stage01");

		GameObject* background = new GameObject();
		MeshRenderer* meshRenderer = new MeshRenderer(SCENE->GetGraphics()->GetDevice(), SCENE->GetGraphics()->GetDeviceContext());
		SpriteRenderer* renderer = new SpriteRenderer();
		renderer->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);
		background->GetOrAddTransform()->SetScale(Vec3(3, 3, 1));

		const Vec2 size = sprite->GetSize();

		//background->SetScale(Vector( 3,3 ));
		background->GetTransform()->SetPosition(Vec3(size.x / 2, size.y / 2, 0));

		background->AddComponent(renderer);
		AddObject(background);
	}


#pragma region 오브젝트
	EQUIPMENT->Init();
	{
		GameObject* camera = new GameObject();
		auto cam = new Camera();
		camera->AddComponent(cam);
		camera->GetOrAddTransform()->SetPosition({0,0,0});
		//camera->SetTarget(GAMEMANAGER->GetPlayer());
		AddObject(camera);
	}

	
	{
		GameOverHud* hudPanel = new GameOverHud();
		hudPanel->SetLayer(LAYER_UI);
		_panel = hudPanel;
		AddObject(hudPanel);
	}
	/*{
		PlayerHudPanel* hudPanel = new PlayerHudPanel();
		hudPanel->SetLayer(LAYER_UI);
		_panel = hudPanel;
		AddObject(hudPanel);
	}*/
	/*{
		EquipmentHud* equipmentHud = new EquipmentHud();
		equipmentHud->Init();
		equipmentHud->SetLayer(LAYER_UI);
		_panel = equipmentHud;
		AddObject(equipmentHud);
	}*/
	 /*{
		EquipmentSelectHud* equipmentSelectHud = new EquipmentSelectHud();
		equipmentSelectHud->SetLayer(LAYER_UI);
		equipmentSelectHud->SetIsActivity(true);
		_panel = equipmentSelectHud;

		AddObject(equipmentSelectHud);
	}*/

	_uiLayoutManager = new UiLayoutManager();
#pragma endregion
	
}

void EditScene::Update()
{
	Super::Update();

	SelectObject();

	MoveSelectedObject();
	if (INPUT->GetButtonDown(KeyType::S))
	{
		if (_panel)
		{
			vector<Ui*> objects = _panel->GetPanels();
			_uiLayoutManager->Save("a.json", objects);
		}
		else
		{
			vector<GameObject*> objects = GetGameObjects(LAYER_UI);
			_uiLayoutManager->Save("a.json", objects);
		}
	}

	if (INPUT->GetButtonDown(KeyType::D))
	{
		if (_panel)
		{
			vector<Ui*> objects = _panel->GetPanels();
			_uiLayoutManager->Load("a.json", objects);
		}
		else
		{
			vector<GameObject*> objects = GetGameObjects(LAYER_UI);
			_uiLayoutManager->Load("a.json", objects);
		}
	}
}

void EditScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

bool EditScene::InSideObject(GameObject* obj)
{
	POINT mousePos = INPUT->GetMousePos();
	Vec3 objPos = obj->GetOrAddTransform()->GetPosition();
	Vec3 objSize = obj->GetTransform()->GetScale();

	return (mousePos.x <= objPos.x + objSize.x &&
		mousePos.x >= objPos.x - objSize.x &&
		mousePos.y <= objPos.y + objSize.y &&
		mousePos.y >= objPos.y - objSize.y);

}

void EditScene::SelectObject()
{
	
	POINT mousePos = INPUT->GetMousePos();


	if (INPUT->GetButtonDown(KeyType::LeftMouse))
	{
		if (!_isDragging)
		{
			_selectedObject = nullptr;

			if (_panel == nullptr)
			{
				for (int i = LAYER_MAXCOUNT - 1; i >= 0; i--)
				{
					vector<GameObject*> objects = GetGameObjects(i);
					for (int j = objects.size() - 1; j >= 0; j--)
					{
						if (InSideObject(objects[j]))
						{
							_selectedObject = objects[j];
							_isDragging = true;

							_dragOffset = Vec3(mousePos.x, mousePos.y,0) - objects[j]->GetOrAddTransform()->GetPosition();
							wstring s = _selectedObject->GetKey();
							return;
						}
					}
				}
			}
			else
			{
				// 패널이 있을 때는 패널 내에서만 선택 가능하도록 구현
				vector<Ui*> panelObjects = _panel->GetPanels();
				for (int i = panelObjects.size() - 1; i >= 0; i--)
				{
					if (InSideObject(panelObjects[i]))
					{
						_selectedObject = panelObjects[i];
						_isDragging = true;

						_dragOffset = Vec3(mousePos.x, mousePos.y,0) - panelObjects[i]->GetOrAddTransform()->GetPosition();

						return;
					}
				}
			}
		}
		else
		{
			_isDragging = false;
		}
	}

	return;
}

void EditScene::MoveSelectedObject()
{
	if (_selectedObject == nullptr || !_isDragging)
		return;

	POINT mousePos = INPUT->GetMousePos();
	_selectedObject->GetOrAddTransform()->SetPosition(Vec3(mousePos.x, mousePos.y, 0) - _dragOffset);
}

