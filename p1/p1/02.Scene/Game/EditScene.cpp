#include "pch.h"
#include "EditScene.h"
#include "../../01.Manager/InputManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/SpawnManager.h"
#include "../../01.Manager/StageManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/EquipmentManager.h"
#include "../../01.Manager/UiLayoutManager.h"
#include "../../03.Object/Item/Experinence/ExperinenceObject.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../03.Object/ObjectPool/ObjectPool.h"
#include "../../03.Object/Spawner/Spawner.h"
#include "../../03.Object/Camera/Camera.h"
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
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../05.Resource/2D/Texture.h"
#include "../../05.Resource/2D/Animator.h"
#include "../../05.Resource/2D/Sprite.h"
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
	//GET_SINGLE(ObjectPool)->Clear();
	GET_SINGLE(EquipmentManager)->Clear();
	GET_SINGLE(GameManager)->SetPlayer(nullptr);
	//if (sound)
		//SAFE_DELETE(sound);
	Clear();
}

void EditScene::Init()
{
	Super::Init();

	{
		GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");

		GET_SINGLE(ResourceManager)->LoadTexture(L"GuraLeft", L"Sprite\\Player\\GuraAniLeft.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"GuraRight", L"Sprite\\Player\\GuraAniRight.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"GuraImage", L"Sprite\\Player\\Gura.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDie", L"Sprite\\Player\\PlayerDie.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"GuraIcon", L"Sprite\\Player\\GuraIcon.bmp");

		GET_SINGLE(ResourceManager)->LoadTexture(L"FuburaLeft", L"Sprite\\Monster\\Fubura\\FuburaLeft.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"FuburaRight", L"Sprite\\Monster\\Fubura\\FuburaRight.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"FuburaLaserStart", L"Sprite\\Monster\\Fubura\\LaserStart.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"FuburaLaser", L"Sprite\\Monster\\Fubura\\Laser.bmp");

		GET_SINGLE(ResourceManager)->LoadTexture(L"ShubagelionAttack", L"Sprite\\Monster\\Shubangelion\\ShubagelionAttack.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"ShubangelionCharge", L"Sprite\\Monster\\Shubangelion\\ShubangelionCharge.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"ShubangelionLeft", L"Sprite\\Monster\\Shubangelion\\ShubangelionLeft.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"ShubangelionRight", L"Sprite\\Monster\\Shubangelion\\ShubangelionRight.bmp");

		GET_SINGLE(ResourceManager)->LoadTexture(L"SukonbuLeft", L"Sprite\\Monster\\Sukonbu\\SukonbuLeft.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"SukonbuRight", L"Sprite\\Monster\\Sukonbu\\SukonbuRight.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"SukonbuTypeB", L"Sprite\\Monster\\Sukonbu\\SukonbuTypeB.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"SukonbuTypeK", L"Sprite\\Monster\\Sukonbu\\SukonbuTypeK.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"SukonbuTypeN", L"Sprite\\Monster\\Sukonbu\\SukonbuTypeN.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"SukonbuTypeT", L"Sprite\\Monster\\Sukonbu\\SukonbuTypeT.bmp");

		// 장비
		GET_SINGLE(ResourceManager)->LoadTexture(L"FanSpawn", L"Sprite\\Object\\FanSpawn.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"FanDie", L"Sprite\\Object\\FanDie.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Exp", L"Sprite\\Object\\Exp.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"HealObject", L"Sprite\\Object\\Hamburger.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Bullets", L"Sprite\\Object\\Bullets.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"BLBook", L"Sprite\\Object\\BLBook.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Miasma", L"Sprite\\Object\\Miasma.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"BombObj", L"Sprite\\Object\\Bomb.bmp");


		GET_SINGLE(ResourceManager)->LoadTexture(L"EnCurse", L"Sprite\\Object\\EnCurse.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"FanBeam", L"Sprite\\Object\\FanBeam.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"LavaStart", L"Sprite\\Object\\LavaStart.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"LavaLoop", L"Sprite\\Object\\LavaLoop.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"LavaEnd", L"Sprite\\Object\\LavaEnd.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Explode", L"Sprite\\Object\\Explode.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"PsychoAxe", L"Sprite\\Object\\PsychoAxe.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Stick", L"Sprite\\Object\\Stick.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"StickExplode", L"Sprite\\Object\\StickExplode.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Sausage", L"Sprite\\Object\\Sausage.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Splash", L"Sprite\\Object\\Splash.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"TridentObj", L"Sprite\\Object\\Trident.bmp");

		// UI
		GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerHpBar", L"Sprite\\Ui\\PlayerHpBar.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerHUD1", L"Sprite\\Ui\\PlayerHUD1.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"ExpBarFrame", L"Sprite\\Ui\\ExpBarFrame.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"ExpBar", L"Sprite\\Ui\\ExpBar.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"DefaultEquipmentIcon", L"Sprite\\Ui\\DefaultEquipmentIcon.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"WeaponIcon_1", L"Sprite\\Ui\\WeaponIcon_1.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"WeaponIcon_2", L"Sprite\\Ui\\WeaponIcon_2.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"ItmeMenu_Menu", L"Sprite\\Ui\\ItmeMenu_Menu.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Trident", L"Sprite\\Ui\\Trident.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"KillCount_Coin", L"Sprite\\Ui\\KillCount_Coin.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Numbers", L"Sprite\\Ui\\Numbers.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"Level", L"Sprite\\Ui\\Level.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"SettingMenuBG", L"Sprite\\Ui\\SettingMenue.bmp");
		GET_SINGLE(ResourceManager)->LoadTexture(L"DefaultButtonImage", L"Sprite\\Ui\\SettingButton.bmp");

		GET_SINGLE(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"SettingMenuBG", GET_SINGLE(ResourceManager)->GetTexture(L"SettingMenuBG"));

		GET_SINGLE(ResourceManager)->CreateSprite(L"Exp01", GET_SINGLE(ResourceManager)->GetTexture(L"Exp"), 0, 0, 16, 18);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Exp02", GET_SINGLE(ResourceManager)->GetTexture(L"Exp"), 16, 0, 16, 18);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Exp03", GET_SINGLE(ResourceManager)->GetTexture(L"Exp"), 32, 0, 16, 18);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Exp04", GET_SINGLE(ResourceManager)->GetTexture(L"Exp"), 48, 0, 16, 18);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Exp05", GET_SINGLE(ResourceManager)->GetTexture(L"Exp"), 64, 0, 16, 18);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Exp06", GET_SINGLE(ResourceManager)->GetTexture(L"Exp"), 80, 0, 16, 18);

		GET_SINGLE(ResourceManager)->CreateSprite(L"Bullet01", GET_SINGLE(ResourceManager)->GetTexture(L"Bullets"), 0, 0, 17, 17);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Bullet02", GET_SINGLE(ResourceManager)->GetTexture(L"Bullets"), 17, 0, 17, 17);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Bullet03", GET_SINGLE(ResourceManager)->GetTexture(L"Bullets"), 34, 0, 17, 17);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Bullet04", GET_SINGLE(ResourceManager)->GetTexture(L"Bullets"), 51, 0, 17, 17);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Bullet05", GET_SINGLE(ResourceManager)->GetTexture(L"Bullets"), 68, 0, 17, 17);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Bullet06", GET_SINGLE(ResourceManager)->GetTexture(L"Bullets"), 85, 0, 17, 17);

		GET_SINGLE(ResourceManager)->CreateSprite(L"BLBook", GET_SINGLE(ResourceManager)->GetTexture(L"BLBook"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"Miasma", GET_SINGLE(ResourceManager)->GetTexture(L"Miasma"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"BombObj", GET_SINGLE(ResourceManager)->GetTexture(L"BombObj"));

		GET_SINGLE(ResourceManager)->CreateSprite(L"PlayerHpBarGreen", GET_SINGLE(ResourceManager)->GetTexture(L"PlayerHpBar"), 0, 0, 129, 6);
		GET_SINGLE(ResourceManager)->CreateSprite(L"PlayerHpBarRed", GET_SINGLE(ResourceManager)->GetTexture(L"PlayerHpBar"), 129, 0, 129, 6);
		GET_SINGLE(ResourceManager)->CreateSprite(L"PlayerHpBarPuple", GET_SINGLE(ResourceManager)->GetTexture(L"PlayerHpBar"), 258, 0, 129, 6);

		GET_SINGLE(ResourceManager)->CreateSprite(L"PlayerHUD1", GET_SINGLE(ResourceManager)->GetTexture(L"PlayerHUD1"), 199, 0, 199, 87);
		GET_SINGLE(ResourceManager)->CreateSprite(L"GuraIcon", GET_SINGLE(ResourceManager)->GetTexture(L"GuraIcon"));

		GET_SINGLE(ResourceManager)->CreateSprite(L"ExpBarBG", GET_SINGLE(ResourceManager)->GetTexture(L"ExpBarFrame"), 0, 0, 650, 26);
		GET_SINGLE(ResourceManager)->CreateSprite(L"ExpBarFrame", GET_SINGLE(ResourceManager)->GetTexture(L"ExpBarFrame"), 650, 0, 650, 26);
		GET_SINGLE(ResourceManager)->CreateSprite(L"ExpBar", GET_SINGLE(ResourceManager)->GetTexture(L"ExpBar"), 0, 0, 650, 26);
		GET_SINGLE(ResourceManager)->CreateSprite(L"ExpBarFull", GET_SINGLE(ResourceManager)->GetTexture(L"ExpBar"), 0, 26, 650, 26);

		GET_SINGLE(ResourceManager)->CreateSprite(L"DefaultWeaponIcon", GET_SINGLE(ResourceManager)->GetTexture(L"DefaultEquipmentIcon"), 0, 0, 12, 11);
		GET_SINGLE(ResourceManager)->CreateSprite(L"DefaultArmorIcon", GET_SINGLE(ResourceManager)->GetTexture(L"DefaultEquipmentIcon"), 12, 0, 12.11);

		GET_SINGLE(ResourceManager)->CreateSprite(L"ItemMenuSelect", GET_SINGLE(ResourceManager)->GetTexture(L"ItmeMenu_Menu"), 0, 0, 386, 68);
		GET_SINGLE(ResourceManager)->CreateSprite(L"ItemMune", GET_SINGLE(ResourceManager)->GetTexture(L"ItmeMenu_Menu"), 386, 0, 386, 68);
		GET_SINGLE(ResourceManager)->CreateSprite(L"ItemMenuSelectDie", GET_SINGLE(ResourceManager)->GetTexture(L"ItmeMenu_Menu"), 0, 68, 386, 68);
		GET_SINGLE(ResourceManager)->CreateSprite(L"ItemMenuDie", GET_SINGLE(ResourceManager)->GetTexture(L"ItmeMenu_Menu"), 386, 68, 386, 68);

		GET_SINGLE(ResourceManager)->CreateSprite(L"SpiderCooking", GET_SINGLE(ResourceManager)->GetTexture(L"WeaponIcon_1"), 0, 0, 25, 20);
		GET_SINGLE(ResourceManager)->CreateSprite(L"EliteLavaBucket", GET_SINGLE(ResourceManager)->GetTexture(L"WeaponIcon_1"), 25, 0, 25, 20);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Bomb", GET_SINGLE(ResourceManager)->GetTexture(L"WeaponIcon_1"), 50, 0, 25, 20);
		GET_SINGLE(ResourceManager)->CreateSprite(L"PsychoAxe", GET_SINGLE(ResourceManager)->GetTexture(L"WeaponIcon_1"), 75, 0, 25, 20);
		GET_SINGLE(ResourceManager)->CreateSprite(L"BLBook", GET_SINGLE(ResourceManager)->GetTexture(L"WeaponIcon_1"), 100, 0, 25, 20);
		GET_SINGLE(ResourceManager)->CreateSprite(L"FanBeam", GET_SINGLE(ResourceManager)->GetTexture(L"WeaponIcon_1"), 125, 0, 25, 20);
		GET_SINGLE(ResourceManager)->CreateSprite(L"GlowStick", GET_SINGLE(ResourceManager)->GetTexture(L"WeaponIcon_1"), 150, 0, 25, 20);

		GET_SINGLE(ResourceManager)->CreateSprite(L"Sausage", GET_SINGLE(ResourceManager)->GetTexture(L"WeaponIcon_2"), 0, 0, 25, 22);
		GET_SINGLE(ResourceManager)->CreateSprite(L"EnCurse", GET_SINGLE(ResourceManager)->GetTexture(L"WeaponIcon_2"), 25, 0, 25, 22);
		GET_SINGLE(ResourceManager)->CreateSprite(L"WamyWater", GET_SINGLE(ResourceManager)->GetTexture(L"WeaponIcon_2"), 50, 0, 25, 22);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Trident", GET_SINGLE(ResourceManager)->GetTexture(L"Trident"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"PistolShoot", GET_SINGLE(ResourceManager)->GetTexture(L"Trident"));
		GET_SINGLE(ResourceManager)->CreateSprite(L"KillCount", GET_SINGLE(ResourceManager)->GetTexture(L"KillCount_Coin"),0,0,15,15);
		GET_SINGLE(ResourceManager)->CreateSprite(L"Coin", GET_SINGLE(ResourceManager)->GetTexture(L"KillCount_Coin"),15,0,15,15);
		GET_SINGLE(ResourceManager)->CreateSprite(L"DefaultButton", GET_SINGLE(ResourceManager)->GetTexture(L"DefaultButtonImage"),0,0,180,29);
		GET_SINGLE(ResourceManager)->CreateSprite(L"DefaultButtonPress", GET_SINGLE(ResourceManager)->GetTexture(L"DefaultButtonImage"),0,29,180,29);

		GET_SINGLE(ResourceManager)->CreateSprite(L"LevelTypeNormal", GET_SINGLE(ResourceManager)->GetTexture(L"Level"),0,0,20,9);
		GET_SINGLE(ResourceManager)->CreateSprite(L"LevelTypeCollabo", GET_SINGLE(ResourceManager)->GetTexture(L"Level"),20,0,20,9);
		GET_SINGLE(ResourceManager)->CreateSprite(L"LevelTypeExclusive", GET_SINGLE(ResourceManager)->GetTexture(L"Level"),40,0,20,9);

		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeNormal0", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"),0 ,0,5,7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeNormal1", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"),5 ,0,5,7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeNormal2", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"),10,0,5,7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeNormal3", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"),15,0,5,7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeNormal4", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"),20,0,5,7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeNormal5", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"),25,0,5,7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeNormal6", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"),30,0,5,7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeNormal7", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"),35,0,5,7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeNormal8", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"),40,0,5,7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeNormal9", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"),45,0,5,7);

		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeCollabo0", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 0,  7, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeCollabo1", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 5,  7, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeCollabo2", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 10, 7, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeCollabo3", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 15, 7, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeCollabo4", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 20, 7, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeCollabo5", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 25, 7, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeCollabo6", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 30, 7, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeCollabo7", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 35, 7, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeCollabo8", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 40, 7, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeCollabo9", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 45, 7, 5, 7);

		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeExclusive0", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 0, 14, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeExclusive1", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 5, 14, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeExclusive2", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 10,14, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeExclusive3", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 15,14, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeExclusive4", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 20,14, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeExclusive5", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 25,14, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeExclusive6", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 30,14, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeExclusive7", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 35,14, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeExclusive8", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 40,14, 5, 7);
		GET_SINGLE(ResourceManager)->CreateSprite(L"NumberTypeExclusive9", GET_SINGLE(ResourceManager)->GetTexture(L"Numbers"), 45,14, 5, 7);

	}
	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Stage01");

		GameObject* background = new GameObject();
		SpriteRenderer* renderer = new SpriteRenderer();
		renderer->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);

		const Vec2Int size = sprite->GetSize();

		background->SetScale({ 3,3 });
		background->SetPos(Vec2(size.x / 2, size.y / 2));

		background->AddComponent(renderer);
		AddObject(background);
	}
	{
		// 피벗 및 스프라이트 테스트 용
		Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"GuraImage");
		//texture->SetPivot({ 0,2 });
		GET_SINGLE(ResourceManager)->CreateSprite(L"GuraImage", texture);
	}



#pragma region 오브젝트
	GET_SINGLE(EquipmentManager)->Init();
	{
		Camera* camera = new Camera();
		camera->SetPos({ 400,400 });
		//camera->SetTarget(GET_SINGLE(GameManager)->GetPlayer());
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


#pragma endregion
	
}

void EditScene::Update()
{
	Super::Update();

	SelectObject();

	MoveSelectedObject();
	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::S))
	{
		if (_panel)
		{
			vector<Ui*> objects = _panel->GetPanels();
			GET_SINGLE(UiLayoutManager)->Save("a.json", objects);
		}
		else
		{
			vector<GameObject*> objects = GetGameObjects(LAYER_UI);
			GET_SINGLE(UiLayoutManager)->Save("a.json", objects);
		}
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::D))
	{
		if (_panel)
		{
			vector<Ui*> objects = _panel->GetPanels();
			GET_SINGLE(UiLayoutManager)->Load("a.json", objects);
		}
		else
		{
			vector<GameObject*> objects = GetGameObjects(LAYER_UI);
			GET_SINGLE(UiLayoutManager)->Load("a.json", objects);
		}
	}
}

void EditScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

bool EditScene::InSideObject(GameObject* obj)
{
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vec2 objPos = obj->GetPos();
	Vec2 objSize = obj->GetSize();

	return (mousePos.x <= objPos.x + objSize.x &&
		mousePos.x >= objPos.x - objSize.x &&
		mousePos.y <= objPos.y + objSize.y &&
		mousePos.y >= objPos.y - objSize.y);

}

void EditScene::SelectObject()
{
	
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();


	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::LeftMouse))
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

							_dragOffset = Vec2(mousePos.x, mousePos.y) - objects[j]->GetPos();
							wstring s = _selectedObject->GetKey();
							cout << "[DeBug] Selected Object Pos : " << _selectedObject->GetPos().x << " , " << _selectedObject->GetPos().y << endl;
							cout << "[DeBug] Selected Object Size : " << _selectedObject->GetSize().x << " , " << _selectedObject->GetSize().y << endl;
							wcout << "[DeBug] Selected Object Key : " << s << endl;
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

						_dragOffset = Vec2(mousePos.x, mousePos.y) - panelObjects[i]->GetPos();

						cout << "[DeBug] Selected Object Pos : " << _selectedObject->GetPos().x << " , " << _selectedObject->GetPos().y << endl;
						cout << "[DeBug] Selected Object Size : " << _selectedObject->GetSize().x << " , " << _selectedObject->GetSize().y << endl;
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

	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	_selectedObject->SetPos(Vec2(mousePos.x, mousePos.y) - _dragOffset);
}

