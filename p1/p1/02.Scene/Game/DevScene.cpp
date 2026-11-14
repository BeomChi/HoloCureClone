#include "pch.h"
#include "DevScene.h"
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
#include "../../03.Object/Camera/CameraToTargetTracking.h"
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
#include "97.Engin/Resource/Texture.h"
#include "97.Engin/Resource/Animation.h"
#include "97.Engin/Resource/Sprite.h"
#include "../../05.Resource/Sound/Sound.h"
#include "../../06.Ui/Button.h"
#include "../../06.Ui/Game/PlayerHudPanel.h"
#include "../../06.Ui/Game/EquipmentHud.h"
#include "../../06.Ui/Game/EquipmentSelectHud.h"
#include "../../06.Ui/Game/GameOverHud.h"
#include "97.Engin/Component/Camera/Camera.h"
#include "97.Engin/Component/Renderer/MeshRenderer.h"


DevScene::DevScene()
{
	
}

DevScene::~DevScene()
{
	// GAME이 nullptr이면 프로그램 종료라는 뜻이니 굳이 여기서
	// 정리 안하고 게임에서 최종 정리하는 걸로
	if (GAME != nullptr)
	{
		// 장비 효과 제거 및 리셋
		EQUIPMENT->UnEquipmentAll(_player);
	}

	SAFE_DELETE(_uiLayoutManager);
	sound->Stop();
	Clear();
}

void DevScene::Init()
{
	Super::Init();

	{
		//RESOURCE->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");

		//RESOURCE->LoadTexture(L"GuraLeft", L"Sprite\\Player\\GuraAniLeft.bmp");
		//RESOURCE->LoadTexture(L"GuraRight", L"Sprite\\Player\\GuraAniRight.bmp");
		//RESOURCE->LoadTexture(L"GuraImage", L"Sprite\\Player\\Gura.bmp");
		//RESOURCE->LoadTexture(L"PlayerDie", L"Sprite\\Player\\PlayerDie.bmp");
		//RESOURCE->LoadTexture(L"GuraIcon", L"Sprite\\Player\\GuraIcon.bmp");

		//RESOURCE->LoadTexture(L"FuburaLeft", L"Sprite\\Monster\\Fubura\\FuburaLeft.bmp");
		//RESOURCE->LoadTexture(L"FuburaRight", L"Sprite\\Monster\\Fubura\\FuburaRight.bmp");
		//RESOURCE->LoadTexture(L"FuburaLaserStart", L"Sprite\\Monster\\Fubura\\LaserStart.bmp");
		//RESOURCE->LoadTexture(L"FuburaLaser", L"Sprite\\Monster\\Fubura\\Laser.bmp");

		//RESOURCE->LoadTexture(L"ShubagelionAttack", L"Sprite\\Monster\\Shubangelion\\ShubagelionAttack.bmp");
		//RESOURCE->LoadTexture(L"ShubangelionCharge", L"Sprite\\Monster\\Shubangelion\\ShubangelionCharge.bmp");
		//RESOURCE->LoadTexture(L"ShubangelionLeft", L"Sprite\\Monster\\Shubangelion\\ShubangelionLeft.bmp");
		//RESOURCE->LoadTexture(L"ShubangelionRight", L"Sprite\\Monster\\Shubangelion\\ShubangelionRight.bmp");

		//RESOURCE->LoadTexture(L"SukonbuLeft", L"Sprite\\Monster\\Sukonbu\\SukonbuLeft.bmp");
		//RESOURCE->LoadTexture(L"SukonbuRight", L"Sprite\\Monster\\Sukonbu\\SukonbuRight.bmp");
		//RESOURCE->LoadTexture(L"SukonbuTypeB", L"Sprite\\Monster\\Sukonbu\\SukonbuTypeB.bmp");
		//RESOURCE->LoadTexture(L"SukonbuTypeK", L"Sprite\\Monster\\Sukonbu\\SukonbuTypeK.bmp");
		//RESOURCE->LoadTexture(L"SukonbuTypeN", L"Sprite\\Monster\\Sukonbu\\SukonbuTypeN.bmp");
		//RESOURCE->LoadTexture(L"SukonbuTypeT", L"Sprite\\Monster\\Sukonbu\\SukonbuTypeT.bmp");

		//// 장비
		//RESOURCE->LoadTexture(L"FanSpawn", L"Sprite\\Object\\FanSpawn.bmp");
		//RESOURCE->LoadTexture(L"FanDie", L"Sprite\\Object\\FanDie.bmp");
		//RESOURCE->LoadTexture(L"Exp", L"Sprite\\Object\\Exp.bmp");
		//RESOURCE->LoadTexture(L"HealObject", L"Sprite\\Object\\Hamburger.bmp");
		//RESOURCE->LoadTexture(L"Bullets", L"Sprite\\Object\\Bullets.bmp");
		//RESOURCE->LoadTexture(L"BLBook", L"Sprite\\Object\\BLBook.bmp");
		//RESOURCE->LoadTexture(L"Miasma", L"Sprite\\Object\\Miasma.bmp");
		//RESOURCE->LoadTexture(L"BombObj", L"Sprite\\Object\\Bomb.bmp");


		//RESOURCE->LoadTexture(L"EnCurse", L"Sprite\\Object\\EnCurse.bmp");
		//RESOURCE->LoadTexture(L"FanBeam", L"Sprite\\Object\\FanBeam.bmp");
		//RESOURCE->LoadTexture(L"LavaStart", L"Sprite\\Object\\LavaStart.bmp");
		//RESOURCE->LoadTexture(L"LavaLoop", L"Sprite\\Object\\LavaLoop.bmp");
		//RESOURCE->LoadTexture(L"LavaEnd", L"Sprite\\Object\\LavaEnd.bmp");
		//RESOURCE->LoadTexture(L"Explode", L"Sprite\\Object\\Explode.bmp");
		//RESOURCE->LoadTexture(L"PsychoAxe", L"Sprite\\Object\\PsychoAxe.bmp");
		//RESOURCE->LoadTexture(L"Stick", L"Sprite\\Object\\Stick.bmp");
		//RESOURCE->LoadTexture(L"StickExplode", L"Sprite\\Object\\StickExplode.bmp");
		//RESOURCE->LoadTexture(L"Sausage", L"Sprite\\Object\\Sausage.bmp");
		//RESOURCE->LoadTexture(L"Splash", L"Sprite\\Object\\Splash.bmp");
		//RESOURCE->LoadTexture(L"TridentObj", L"Sprite\\Object\\Trident.bmp");

		//// UI
		//RESOURCE->LoadTexture(L"PlayerHpBar", L"Sprite\\Ui\\PlayerHpBar.bmp");
		//RESOURCE->LoadTexture(L"PlayerHUD1", L"Sprite\\Ui\\PlayerHUD1.bmp");
		//RESOURCE->LoadTexture(L"ExpBarFrame", L"Sprite\\Ui\\ExpBarFrame.bmp");
		//RESOURCE->LoadTexture(L"ExpBar", L"Sprite\\Ui\\ExpBar.bmp");
		//RESOURCE->LoadTexture(L"DefaultEquipmentIcon", L"Sprite\\Ui\\DefaultEquipmentIcon.bmp");
		//RESOURCE->LoadTexture(L"WeaponIcon_1", L"Sprite\\Ui\\WeaponIcon_1.bmp");
		//RESOURCE->LoadTexture(L"WeaponIcon_2", L"Sprite\\Ui\\WeaponIcon_2.bmp");
		//RESOURCE->LoadTexture(L"ItmeMenu_Menu", L"Sprite\\Ui\\ItmeMenu_Menu.bmp");
		//RESOURCE->LoadTexture(L"Trident", L"Sprite\\Ui\\Trident.bmp");
		//RESOURCE->LoadTexture(L"Pistol", L"Sprite\\Ui\\Pistol.bmp");
		//RESOURCE->LoadTexture(L"KillCount_Coin", L"Sprite\\Ui\\KillCount_Coin.bmp");
		//RESOURCE->LoadTexture(L"Numbers", L"Sprite\\Ui\\Numbers.bmp");
		//RESOURCE->LoadTexture(L"Level", L"Sprite\\Ui\\Level.bmp");
		//RESOURCE->LoadTexture(L"SettingMenuBG", L"Sprite\\Ui\\SettingMenue.bmp");
		//RESOURCE->LoadTexture(L"DefaultButtonImage", L"Sprite\\Ui\\SettingButton.bmp");

		//RESOURCE->CreateSprite(L"Stage01", RESOURCE->Get<Texture>(L"Stage01"));
		//RESOURCE->CreateSprite(L"SettingMenuBG", RESOURCE->Get<Texture>(L"SettingMenuBG"));

		//RESOURCE->CreateSprite(L"Exp01", RESOURCE->Get<Texture>(L"Exp"), 0, 0, 16, 18);
		//RESOURCE->CreateSprite(L"Exp02", RESOURCE->Get<Texture>(L"Exp"), 16, 0, 16, 18);
		//RESOURCE->CreateSprite(L"Exp03", RESOURCE->Get<Texture>(L"Exp"), 32, 0, 16, 18);
		//RESOURCE->CreateSprite(L"Exp04", RESOURCE->Get<Texture>(L"Exp"), 48, 0, 16, 18);
		//RESOURCE->CreateSprite(L"Exp05", RESOURCE->Get<Texture>(L"Exp"), 64, 0, 16, 18);
		//RESOURCE->CreateSprite(L"Exp06", RESOURCE->Get<Texture>(L"Exp"), 80, 0, 16, 18);

		//RESOURCE->CreateSprite(L"Bullet01", RESOURCE->Get<Texture>(L"Bullets"), 0, 0, 17, 17);
		//RESOURCE->CreateSprite(L"Bullet02", RESOURCE->Get<Texture>(L"Bullets"), 17, 0, 17, 17);
		//RESOURCE->CreateSprite(L"Bullet03", RESOURCE->Get<Texture>(L"Bullets"), 34, 0, 17, 17);
		//RESOURCE->CreateSprite(L"Bullet04", RESOURCE->Get<Texture>(L"Bullets"), 51, 0, 17, 17);
		//RESOURCE->CreateSprite(L"Bullet05", RESOURCE->Get<Texture>(L"Bullets"), 68, 0, 17, 17);
		//RESOURCE->CreateSprite(L"Bullet06", RESOURCE->Get<Texture>(L"Bullets"), 85, 0, 17, 17);

		//RESOURCE->CreateSprite(L"BLBook", RESOURCE->Get<Texture>(L"BLBook"));
		//RESOURCE->CreateSprite(L"Miasma", RESOURCE->Get<Texture>(L"Miasma"));
		//RESOURCE->CreateSprite(L"BombObj", RESOURCE->Get<Texture>(L"BombObj"));

		//RESOURCE->CreateSprite(L"PlayerHpBarGreen", RESOURCE->Get<Texture>(L"PlayerHpBar"), 0, 0, 129, 6);
		//RESOURCE->CreateSprite(L"PlayerHpBarRed", RESOURCE->Get<Texture>(L"PlayerHpBar"), 129, 0, 129, 6);
		//RESOURCE->CreateSprite(L"PlayerHpBarPuple", RESOURCE->Get<Texture>(L"PlayerHpBar"), 258, 0, 129, 6);

		//RESOURCE->CreateSprite(L"PlayerHUD1", RESOURCE->Get<Texture>(L"PlayerHUD1"), 199, 0, 199, 87);
		//RESOURCE->CreateSprite(L"GuraIcon", RESOURCE->Get<Texture>(L"GuraIcon"));

		//RESOURCE->CreateSprite(L"ExpBarBG", RESOURCE->Get<Texture>(L"ExpBarFrame"), 0, 0, 650, 26);
		//RESOURCE->CreateSprite(L"ExpBarFrame", RESOURCE->Get<Texture>(L"ExpBarFrame"), 650, 0, 650, 26);
		//RESOURCE->CreateSprite(L"ExpBar", RESOURCE->Get<Texture>(L"ExpBar"), 0, 0, 650, 26);
		//RESOURCE->CreateSprite(L"ExpBarFull", RESOURCE->Get<Texture>(L"ExpBar"), 0, 26, 650, 26);

		//RESOURCE->CreateSprite(L"DefaultWeaponIcon", RESOURCE->Get<Texture>(L"DefaultEquipmentIcon"), 0, 0, 12, 11);
		//RESOURCE->CreateSprite(L"DefaultArmorIcon", RESOURCE->Get<Texture>(L"DefaultEquipmentIcon"), 12, 0, 12.11);

		//RESOURCE->CreateSprite(L"ItemMenuSelect", RESOURCE->Get<Texture>(L"ItmeMenu_Menu"), 0, 0, 386, 68);
		//RESOURCE->CreateSprite(L"ItemMune", RESOURCE->Get<Texture>(L"ItmeMenu_Menu"), 386, 0, 386, 68);
		//RESOURCE->CreateSprite(L"ItemMenuSelectDie", RESOURCE->Get<Texture>(L"ItmeMenu_Menu"), 0, 68, 386, 68);
		//RESOURCE->CreateSprite(L"ItemMenuDie", RESOURCE->Get<Texture>(L"ItmeMenu_Menu"), 386, 68, 386, 68);

		//RESOURCE->CreateSprite(L"SpiderCooking", RESOURCE->Get<Texture>(L"WeaponIcon_1"), 0, 0, 25, 20);
		//RESOURCE->CreateSprite(L"EliteLavaBucket", RESOURCE->Get<Texture>(L"WeaponIcon_1"), 25, 0, 25, 20);
		//RESOURCE->CreateSprite(L"Bomb", RESOURCE->Get<Texture>(L"WeaponIcon_1"), 50, 0, 25, 20);
		//RESOURCE->CreateSprite(L"PsychoAxe", RESOURCE->Get<Texture>(L"WeaponIcon_1"), 75, 0, 25, 20);
		//RESOURCE->CreateSprite(L"BLBook", RESOURCE->Get<Texture>(L"WeaponIcon_1"), 100, 0, 25, 20);
		//RESOURCE->CreateSprite(L"FanBeam", RESOURCE->Get<Texture>(L"WeaponIcon_1"), 125, 0, 25, 20);
		//RESOURCE->CreateSprite(L"GlowStick", RESOURCE->Get<Texture>(L"WeaponIcon_1"), 150, 0, 25, 20);

		//RESOURCE->CreateSprite(L"Sausage", RESOURCE->Get<Texture>(L"WeaponIcon_2"), 0, 0, 25, 22);
		//RESOURCE->CreateSprite(L"EnCurse", RESOURCE->Get<Texture>(L"WeaponIcon_2"), 25, 0, 25, 22);
		//RESOURCE->CreateSprite(L"WamyWater", RESOURCE->Get<Texture>(L"WeaponIcon_2"), 50, 0, 25, 22);
		//RESOURCE->CreateSprite(L"Trident", RESOURCE->Get<Texture>(L"Trident"));
		//RESOURCE->CreateSprite(L"PistolShoot", RESOURCE->Get<Texture>(L"Pistol"));
		//RESOURCE->CreateSprite(L"KillCount", RESOURCE->Get<Texture>(L"KillCount_Coin"),0,0,15,15);
		//RESOURCE->CreateSprite(L"Coin", RESOURCE->Get<Texture>(L"KillCount_Coin"),15,0,15,15);
		//RESOURCE->CreateSprite(L"DefaultButton", RESOURCE->Get<Texture>(L"DefaultButtonImage"),0,0,180,29);
		//RESOURCE->CreateSprite(L"DefaultButtonPress", RESOURCE->Get<Texture>(L"DefaultButtonImage"),0,29,180,29);

		//RESOURCE->CreateSprite(L"LevelTypeNormal", RESOURCE->Get<Texture>(L"Level"),0,0,20,9);
		//RESOURCE->CreateSprite(L"LevelTypeCollabo", RESOURCE->Get<Texture>(L"Level"),20,0,20,9);
		//RESOURCE->CreateSprite(L"LevelTypeExclusive", RESOURCE->Get<Texture>(L"Level"),40,0,20,9);

		//RESOURCE->CreateSprite(L"NumberTypeNormal0", RESOURCE->Get<Texture>(L"Numbers"),0 ,0,5,7);
		//RESOURCE->CreateSprite(L"NumberTypeNormal1", RESOURCE->Get<Texture>(L"Numbers"),5 ,0,5,7);
		//RESOURCE->CreateSprite(L"NumberTypeNormal2", RESOURCE->Get<Texture>(L"Numbers"),10,0,5,7);
		//RESOURCE->CreateSprite(L"NumberTypeNormal3", RESOURCE->Get<Texture>(L"Numbers"),15,0,5,7);
		//RESOURCE->CreateSprite(L"NumberTypeNormal4", RESOURCE->Get<Texture>(L"Numbers"),20,0,5,7);
		//RESOURCE->CreateSprite(L"NumberTypeNormal5", RESOURCE->Get<Texture>(L"Numbers"),25,0,5,7);
		//RESOURCE->CreateSprite(L"NumberTypeNormal6", RESOURCE->Get<Texture>(L"Numbers"),30,0,5,7);
		//RESOURCE->CreateSprite(L"NumberTypeNormal7", RESOURCE->Get<Texture>(L"Numbers"),35,0,5,7);
		//RESOURCE->CreateSprite(L"NumberTypeNormal8", RESOURCE->Get<Texture>(L"Numbers"),40,0,5,7);
		//RESOURCE->CreateSprite(L"NumberTypeNormal9", RESOURCE->Get<Texture>(L"Numbers"),45,0,5,7);

		//RESOURCE->CreateSprite(L"NumberTypeCollabo0", RESOURCE->Get<Texture>(L"Numbers"), 0,  7, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeCollabo1", RESOURCE->Get<Texture>(L"Numbers"), 5,  7, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeCollabo2", RESOURCE->Get<Texture>(L"Numbers"), 10, 7, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeCollabo3", RESOURCE->Get<Texture>(L"Numbers"), 15, 7, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeCollabo4", RESOURCE->Get<Texture>(L"Numbers"), 20, 7, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeCollabo5", RESOURCE->Get<Texture>(L"Numbers"), 25, 7, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeCollabo6", RESOURCE->Get<Texture>(L"Numbers"), 30, 7, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeCollabo7", RESOURCE->Get<Texture>(L"Numbers"), 35, 7, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeCollabo8", RESOURCE->Get<Texture>(L"Numbers"), 40, 7, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeCollabo9", RESOURCE->Get<Texture>(L"Numbers"), 45, 7, 5, 7);

		//RESOURCE->CreateSprite(L"NumberTypeExclusive0", RESOURCE->Get<Texture>(L"Numbers"), 0, 14, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeExclusive1", RESOURCE->Get<Texture>(L"Numbers"), 5, 14, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeExclusive2", RESOURCE->Get<Texture>(L"Numbers"), 10,14, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeExclusive3", RESOURCE->Get<Texture>(L"Numbers"), 15,14, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeExclusive4", RESOURCE->Get<Texture>(L"Numbers"), 20,14, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeExclusive5", RESOURCE->Get<Texture>(L"Numbers"), 25,14, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeExclusive6", RESOURCE->Get<Texture>(L"Numbers"), 30,14, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeExclusive7", RESOURCE->Get<Texture>(L"Numbers"), 35,14, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeExclusive8", RESOURCE->Get<Texture>(L"Numbers"), 40,14, 5, 7);
		//RESOURCE->CreateSprite(L"NumberTypeExclusive9", RESOURCE->Get<Texture>(L"Numbers"), 45,14, 5, 7);

	}
	{
		Sprite* sprite = RESOURCE->Get<Sprite>(L"Stage01");

		GameObject* background = new GameObject();
		SpriteRenderer* renderer = new SpriteRenderer();
		renderer->SetSprite(sprite);
		background->SetLayer(LAYER_BACKGROUND);

		const Vec2 size = sprite->GetSize();

		auto meshRenderer = new MeshRenderer(SCENE->GetGraphics()->GetDevice(),
			SCENE->GetGraphics()->GetDeviceContext());

		background->AddComponent(meshRenderer);

		auto material = RESOURCE->Get<Material>(L"Default");
		meshRenderer->SetMaterial(material);
		auto mesh = RESOURCE->Get<Mesh>(L"Rectangle");
		meshRenderer->SetMesh(mesh);

		background->GetOrAddTransform()->SetScale({3,3,1});
		//background->GetOrAddTransform()->SetPosition(Vec3(size.x / 2, size.y / 2, 0));

		background->AddComponent(renderer);
		AddObject(background);
	}
	{
	//	{
	//		Texture* texture = RESOURCE->Get<Texture>(L"GuraLeft");
	//		Animation* ani = RESOURCE->CreateAnimator(L"Gura_IdleLeft");
	//		//ani->SetInfo({ texture, L"Gura_IdleLeft", {64,34}, 0, 2, 0, 0.5f });
	//	}
	//	{
	//		Texture* texture = RESOURCE->Get<Texture>(L"GuraLeft");
	//		Animation* ani = RESOURCE->CreateAnimator(L"GuraMoveLeft");
	//		//ani->SetInfo({ texture, L"GuraMoveLeft",{64,34}, 0, 5, 1, 0.5f });
	//	}
	//	{
	//		Texture* texture = RESOURCE->Get<Texture>(L"GuraRight");
	//		Animation* ani = RESOURCE->CreateAnimator(L"Gura_IdleRight");
	//		//ani->SetInfo({ texture, L"Gura_IdleRight",{64,34}, 0, 2, 0, 0.5f });
	//	}
	//	{
	//		Texture* texture = RESOURCE->Get<Texture>(L"GuraRight");
	//		Animation* ani = RESOURCE->CreateAnimator(L"GuraMoveRight");
	//		//ani->SetInfo({ texture, L"GuraMoveRight",{64,34}, 0, 5, 1, 0.5f });
	//	}
	//}
	//{
	//	{
	//		Texture* texture = RESOURCE->Get<Texture>(L"FuburaLeft");
	//		Animation* ani = RESOURCE->CreateAnimator(L"Fubura_MoveLeft");
	//		//ani->SetInfo({ texture, L"Fubura_MoveLeft",{82,57}, 0, 11, 0, 1.f });
	//	}
	//	{
	//		Texture* texture = RESOURCE->Get<Texture>(L"FuburaRight");
	//		Animation* ani = RESOURCE->CreateAnimator(L"Fubura_MoveRight");
	//		//ani->SetInfo({ texture, L"Fubura_MoveRight",{82,57}, 0, 11, 0, 1.f });
	//	}
	//	{
	//		Texture* texture = RESOURCE->Get<Texture>(L"FuburaLaserStart");
	//		Animation* ani = RESOURCE->CreateAnimator(L"FuburaLaserStart");
	//		//ani->SetInfo({ texture, L"FuburaLaserStart",{465,50}, 0, 22, 0, 0.8f });
	//	}
	//	{
	//		Texture* texture = RESOURCE->Get<Texture>(L"FuburaLaser");
	//		Animation* ani = RESOURCE->CreateAnimator(L"FuburaLaser");
	//		//ani->SetInfo({ texture, L"FuburaLaser",{465,50}, 0, 11, 0, 1.f });
	//	}
	//}
	//{
	//	{
	//		Texture* texture = RESOURCE->Get<Texture>(L"ShubangelionLeft");
	//		Animation* ani = RESOURCE->CreateAnimator(L"Shubangelion_MoveLeft");
	//		//ani->SetInfo({ texture, L"Shubangelion_MoveLeft",{128,135}, 0, 7, 0, 1.f });
	//	}
	//	{
	//		Texture* texture = RESOURCE->Get<Texture>(L"ShubangelionRight");
	//		Animation* ani = RESOURCE->CreateAnimator(L"Shubangelion_MoveRight");
	//		//ani->SetInfo({ texture, L"Shubangelion_MoveRight",{128,135}, 0, 7, 0, 1.f });
	//	}
	//	{
	//		Texture* texture = RESOURCE->Get<Texture>(L"ShubangelionCharge");
	//		Animation* ani = RESOURCE->CreateAnimator(L"Shubangelion_Charge");
	//		//ani->SetInfo({ texture, L"Shubangelion_Charge",{128,135}, 0, 2, 0, 2.f });
	//	}
	//	{
	//		Texture* texture = RESOURCE->Get<Texture>(L"ShubagelionAttack");
	//		Animation* ani = RESOURCE->CreateAnimator(L"Shubagelion_Attack");
	//		//ani->SetInfo({ texture, L"Shubagelion_Attack",{128,135}, 0, 9, 0, 1.f });
	//	}
	}


//#pragma region 오브젝트
//
//
//	// 오브젝트
//	{
//#pragma region 몬스터 공격 이펙트 애니메이션
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"FanSpawn");
//			Animation* ani = RESOURCE->CreateAnimator(L"FanSpawn");
//			//ani->SetInfo({ texture, L"FanSpawn",{67,114}, 0, 3, 0, 0.25f,false });
//		}
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"FanDie");
//			Animation* ani = RESOURCE->CreateAnimator(L"FanDie");
//			//ani->SetInfo({ texture, L"FanSpawn",{48,48}, 0, 9, 0, 0.5f,false });
//		}
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"HealObject");
//			Animation* ani = RESOURCE->CreateAnimator(L"HealObject");
//			//ani->SetInfo({ texture, L"HealObject",{32,32}, 0, 7, 0, 1.f });
//		}
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"PlayerDie");
//			Animation* ani = RESOURCE->CreateAnimator(L"PlayerDie");
//			//ani->SetInfo({ texture, L"PlayerDie",{32,32}, 0, 3, 0, 1.f });
//		}
//#pragma endregion
//
//#pragma region 장비 이펙트 애니메이션
//
//
//		// 장비
//		{
//			// 무기
//			{
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"LavaStart");
//					Animation* ani = RESOURCE->CreateAnimator(L"LavaStart");
//					//ani->SetInfo({ texture, L"LavaStart",{127,127}, 0, 8, 0, 0.5f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"LavaLoop");
//					Animation* ani = RESOURCE->CreateAnimator(L"LavaLoop");
//					//ani->SetInfo({ texture, L"LavaLoop",{127,127}, 0, 13, 0, 1.f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"LavaEnd");
//					Animation* ani = RESOURCE->CreateAnimator(L"LavaEnd");
//					//ani->SetInfo({ texture, L"LavaEnd",{127,127}, 0, 5, 0, 0.5f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"EnCurse");
//					Animation* ani = RESOURCE->CreateAnimator(L"EnCurseRight");
//					//ani->SetInfo({ texture, L"EnCurseRight",{36,21}, 0, 7, 0, 0.5f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"EnCurse");
//					Animation* ani = RESOURCE->CreateAnimator(L"EnCurseLeft");
//					//ani->SetInfo({ texture, L"EnCurseLeft",{36,21}, 0, 7, 1, 0.5f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"FanBeam");
//					Animation* ani = RESOURCE->CreateAnimator(L"FanBeamRight");
//					//ani->SetInfo({ texture, L"FanBeamRight",{466,51}, 0, 9, 0, 1.f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"FanBeam");
//					Animation* ani = RESOURCE->CreateAnimator(L"FanBeamLeft");
//					//ani->SetInfo({ texture, L"FanBeamLeft",{466,51}, 0, 9, 1, 1.f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"Explode");
//					Animation* ani = RESOURCE->CreateAnimator(L"BombExplode");
//					//ani->SetInfo({ texture, L"BombExplode",{128,128}, 0, 12, 0, 1.f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"PsychoAxe");
//					Animation* ani = RESOURCE->CreateAnimator(L"PsychoAxe");
//					//ani->SetInfo({ texture, L"PsychoAxe",{46,46}, 0, 7, 0, 1.f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"Stick");
//					Animation* ani = RESOURCE->CreateAnimator(L"Stick");
//					//ani->SetInfo({ texture, L"Stick",{46,46}, 0, 7, 0, 1.f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"StickExplode");
//					Animation* ani = RESOURCE->CreateAnimator(L"StickExplode");
//					//ani->SetInfo({ texture, L"StickExplode",{93,91}, 0, 6, 0, 1.f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"Sausage");
//					Animation* ani = RESOURCE->CreateAnimator(L"SausageRight");
//					//ani->SetInfo({ texture, L"SausageRight",{128,128}, 0, 4, 0, 1.f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"Sausage");
//					Animation* ani = RESOURCE->CreateAnimator(L"SausageLeft");
//					//ani->SetInfo({ texture, L"SausageLeft",{128,128}, 0, 4, 1, 1.f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"Splash");
//					Animation* ani = RESOURCE->CreateAnimator(L"SplashRight");
//					//ani->SetInfo({ texture, L"SplashRight",{128,128}, 0, 5,0, 0.25f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"Splash");
//					Animation* ani = RESOURCE->CreateAnimator(L"SplashLeft");
//					//ani->SetInfo({ texture, L"SplashLeft",{128,128}, 0, 5, 1, 0.25f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"TridentObj");
//					Animation* ani = RESOURCE->CreateAnimator(L"TridentRight");
//					//ani->SetInfo({ texture, L"TridentRight",{200,32}, 0, 6, 0, 0.5f });
//				}
//				{
//					Texture* texture = RESOURCE->Get<Texture>(L"TridentObj");
//					Animation* ani = RESOURCE->CreateAnimator(L"TridentLeft");
//					//ani->SetInfo({ texture, L"TridentLeft",{200,32}, 0, 6, 1, 0.5f });
//				}
//			}
//		}
//	}
//#pragma endregion
//	
//#pragma region 몬스터 애니메이션
//
//
//	// 몬스터
//	{
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"SukonbuLeft");
//			Animation* ani = RESOURCE->CreateAnimator(L"Sukonbu_MoveLeft");
//			//ani->SetInfo({ texture, L"Sukonbu_MoveLeft",{64,64}, 0, 2, 0, 1.f });
//		}
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"SukonbuRight");
//			Animation* ani = RESOURCE->CreateAnimator(L"Sukonbu_MoveRight");
//			//ani->SetInfo({ texture, L"Sukonbu_MoveRight",{64,64}, 0, 2, 0, 1.f });
//		}
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"SukonbuTypeB");
//			Animation* ani = RESOURCE->CreateAnimator(L"SukonbuTypeB_MoveLeft");
//			//ani->SetInfo({ texture, L"SukonbuTypeB_MoveLeft",{42,32}, 0, 1, 1, 1.f });
//		}
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"SukonbuTypeB");
//			Animation* ani = RESOURCE->CreateAnimator(L"SukonbuTypeB_MoveRight");
//			//ani->SetInfo({ texture, L"SukonbuTypeB_MoveRight",{42,32}, 0, 1, 0, 1.f });
//		}
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"SukonbuTypeK");
//			Animation* ani = RESOURCE->CreateAnimator(L"SukonbuTypeK_MoveLeft");
//			//ani->SetInfo({ texture, L"SukonbuTypeK_MoveLeft",{32,32}, 0, 2, 1, 1.f });
//		}
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"SukonbuTypeK");
//			Animation* ani = RESOURCE->CreateAnimator(L"SukonbuTypeK_MoveRight");
//			//ani->SetInfo({ texture, L"SukonbuTypeK_MoveRight",{32,32}, 0, 2, 0, 1.f });
//		}
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"SukonbuTypeN");
//			Animation* ani = RESOURCE->CreateAnimator(L"SukonbuTypeN_MoveLeft");
//			//ani->SetInfo({ texture, L"SukonbuTypeN_MoveLeft",{32,32}, 0, 2, 1, 1.f });
//		}
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"SukonbuTypeN");
//			Animation* ani = RESOURCE->CreateAnimator(L"SukonbuTypeN_MoveRight");
//			//ani->SetInfo({ texture, L"SukonbuTypeN_MoveRight",{32,32}, 0, 2, 0, 1.f });
//		}
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"SukonbuTypeT");
//			Animation* ani = RESOURCE->CreateAnimator(L"SukonbuTypeT_MoveLeft");
//			//ani->SetInfo({ texture, L"SukonbuTypeT_MoveLeft",{42,36}, 0, 1, 1, 1.f });
//		}
//		{
//			Texture* texture = RESOURCE->Get<Texture>(L"SukonbuTypeT");
//			Animation* ani = RESOURCE->CreateAnimator(L"SukonbuTypeT_MoveRight");
//			//ani->SetInfo({ texture, L"SukonbuTypeT_MoveRight",{42,36}, 0, 1, 0, 1.f });
//		}
//
//#pragma endregion
//	}
//#pragma endregion

	GET_SINGLE(ObjectPool)->Init();

	//GET_SINGLE(SpawnManager)->Init();
	//GET_SINGLE(StageManager)->StartStage();
	EQUIPMENT->Init();

	_uiLayoutManager = new UiLayoutManager();

	{
		_player = new Player();
		assert(_player != nullptr);
		_player->GetOrAddTransform()->SetPosition(Vec3(400,400,0));
		_player->Init();
		AddObject(_player);

		GAMEMANAGER->SetPlayer(_player);

	}
	{
		// 이놈은 빈 깡통으로 바꾸고 카메라 컴포넌트 넣는 걸로 변경하기
		GameObject* camera = new GameObject();
		camera->GetOrAddTransform();
		camera->AddComponent(new Camera());
		camera->GetOrAddTransform()->SetPosition(Vec3(400, 400, 0));

		camera->Init();
		AddObject(camera);

		auto cameraComp = new CameraToTargetTracking();
		camera->AddComponent(cameraComp);
		cameraComp->SetTarget(GAMEMANAGER->GetPlayer());
	}

	/*{
		PlayerHudPanel* hudPanel = new PlayerHudPanel();
		hudPanel->SetLayer(LAYER_UI);

		_uiLayoutManager->Load("ui_Playerlay.json", hudPanel->GetPanels());
		AddObject(hudPanel);
	}
	{
		EquipmentHud* equipmentHud = new EquipmentHud();
		equipmentHud->Init();
		equipmentHud->SetLayer(LAYER_UI);
		AddObject(equipmentHud);
		_uiLayoutManager->Load("ui_Equipmentlay.json", equipmentHud->GetPanels());
		EQUIPMENT->SetEquipmentHud(equipmentHud);
	}
	{
		EquipmentSelectHud* equipmentSelectHud = new EquipmentSelectHud();
		equipmentSelectHud->SetLayer(LAYER_UI);
		equipmentSelectHud->SetIsActivity(false);

		_uiLayoutManager->Load("ui_EquipmentSelectlay.json", equipmentSelectHud->GetPanels());
		AddObject(equipmentSelectHud);
	}
	{
		GameOverHud* hudPanel = new GameOverHud();
		hudPanel->SetLayer(LAYER_UI);
		hudPanel->SetIsActivity(false);

		_uiLayoutManager->Load("ui_layoutGameOverlay.json", hudPanel->GetPanels());
		AddObject(hudPanel);
	}*/

#pragma region Sound 
	{
		sound = RESOURCE->Get<Sound>(L"Stage01BGM");
		sound->Play(true);
	}

#pragma endregion
	
}

void DevScene::Update()
{
	Super::Update();

	//GET_SINGLE(StageManager)->Update();
	EQUIPMENT->UpdateAll();

	if (INPUT->GetButtonDown(KeyType::Q))
	{
		GET_SINGLE(ObjectPool)->Debug();
	}

	if (INPUT->GetButtonDown(KeyType::E))
	{
		_debug = !_debug;
		GAMEMANAGER->SetDebugShow(_debug);
	}
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);
	// 현재 소환된 몬스터 수 확인용
	//GET_SINGLE(SpawnManager)->Render(hdc);
}

