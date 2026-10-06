#include "pch.h"
#include "DevScene.h"
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


DevScene::DevScene()
{
	
}

DevScene::~DevScene()
{
	//GET_SINGLE(ObjectPool)->Clear();
	GET_SINGLE(EquipmentManager)->Clear();
	GET_SINGLE(GameManager)->SetPlayer(nullptr);
	//if (sound)
		//SAFE_DELETE(sound);
	sound->Stop();
	Clear();
}

void DevScene::Init()
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
		GET_SINGLE(ResourceManager)->LoadTexture(L"Pistol", L"Sprite\\Ui\\Pistol.bmp");
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
		GET_SINGLE(ResourceManager)->CreateSprite(L"PistolShoot", GET_SINGLE(ResourceManager)->GetTexture(L"Pistol"));
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
	{
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"GuraLeft");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"Gura_IdleLeft");
			ani->SetInfo({ texture, L"Gura_IdleLeft", {64,34}, 0, 2, 0, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"GuraLeft");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"GuraMoveLeft");
			ani->SetInfo({ texture, L"GuraMoveLeft",{64,34}, 0, 5, 1, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"GuraRight");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"Gura_IdleRight");
			ani->SetInfo({ texture, L"Gura_IdleRight",{64,34}, 0, 2, 0, 0.5f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"GuraRight");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"GuraMoveRight");
			ani->SetInfo({ texture, L"GuraMoveRight",{64,34}, 0, 5, 1, 0.5f });
		}
	}
	{
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FuburaLeft");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"Fubura_MoveLeft");
			ani->SetInfo({ texture, L"Fubura_MoveLeft",{82,57}, 0, 11, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FuburaRight");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"Fubura_MoveRight");
			ani->SetInfo({ texture, L"Fubura_MoveRight",{82,57}, 0, 11, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FuburaLaserStart");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"FuburaLaserStart");
			ani->SetInfo({ texture, L"FuburaLaserStart",{465,50}, 0, 22, 0, 0.8f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FuburaLaser");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"FuburaLaser");
			ani->SetInfo({ texture, L"FuburaLaser",{465,50}, 0, 11, 0, 1.f });
		}
	}
	{
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ShubangelionLeft");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"Shubangelion_MoveLeft");
			ani->SetInfo({ texture, L"Shubangelion_MoveLeft",{128,135}, 0, 7, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ShubangelionRight");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"Shubangelion_MoveRight");
			ani->SetInfo({ texture, L"Shubangelion_MoveRight",{128,135}, 0, 7, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ShubangelionCharge");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"Shubangelion_Charge");
			ani->SetInfo({ texture, L"Shubangelion_Charge",{128,135}, 0, 2, 0, 2.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"ShubagelionAttack");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"Shubagelion_Attack");
			ani->SetInfo({ texture, L"Shubagelion_Attack",{128,135}, 0, 9, 0, 1.f });
		}
	}


#pragma region 오브젝트


	// 오브젝트
	{
#pragma region 몬스터 공격 이펙트 애니메이션
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FanSpawn");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"FanSpawn");
			ani->SetInfo({ texture, L"FanSpawn",{67,114}, 0, 3, 0, 0.25f,false });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FanDie");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"FanDie");
			ani->SetInfo({ texture, L"FanSpawn",{48,48}, 0, 9, 0, 0.5f,false });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"HealObject");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"HealObject");
			ani->SetInfo({ texture, L"HealObject",{32,32}, 0, 7, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PlayerDie");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"PlayerDie");
			ani->SetInfo({ texture, L"PlayerDie",{32,32}, 0, 3, 0, 1.f });
		}
#pragma endregion

#pragma region 장비 이펙트 애니메이션


		// 장비
		{
			// 무기
			{
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LavaStart");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"LavaStart");
					ani->SetInfo({ texture, L"LavaStart",{127,127}, 0, 8, 0, 0.5f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LavaLoop");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"LavaLoop");
					ani->SetInfo({ texture, L"LavaLoop",{127,127}, 0, 13, 0, 1.f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"LavaEnd");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"LavaEnd");
					ani->SetInfo({ texture, L"LavaEnd",{127,127}, 0, 5, 0, 0.5f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"EnCurse");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"EnCurseRight");
					ani->SetInfo({ texture, L"EnCurseRight",{36,21}, 0, 7, 0, 0.5f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"EnCurse");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"EnCurseLeft");
					ani->SetInfo({ texture, L"EnCurseLeft",{36,21}, 0, 7, 1, 0.5f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FanBeam");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"FanBeamRight");
					ani->SetInfo({ texture, L"FanBeamRight",{466,51}, 0, 9, 0, 1.f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"FanBeam");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"FanBeamLeft");
					ani->SetInfo({ texture, L"FanBeamLeft",{466,51}, 0, 9, 1, 1.f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Explode");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"BombExplode");
					ani->SetInfo({ texture, L"BombExplode",{128,128}, 0, 12, 0, 1.f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"PsychoAxe");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"PsychoAxe");
					ani->SetInfo({ texture, L"PsychoAxe",{46,46}, 0, 7, 0, 1.f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Stick");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"Stick");
					ani->SetInfo({ texture, L"Stick",{46,46}, 0, 7, 0, 1.f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"StickExplode");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"StickExplode");
					ani->SetInfo({ texture, L"StickExplode",{93,91}, 0, 6, 0, 1.f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sausage");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"SausageRight");
					ani->SetInfo({ texture, L"SausageRight",{128,128}, 0, 4, 0, 1.f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Sausage");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"SausageLeft");
					ani->SetInfo({ texture, L"SausageLeft",{128,128}, 0, 4, 1, 1.f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Splash");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"SplashRight");
					ani->SetInfo({ texture, L"SplashRight",{128,128}, 0, 5,0, 0.25f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"Splash");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"SplashLeft");
					ani->SetInfo({ texture, L"SplashLeft",{128,128}, 0, 5, 1, 0.25f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"TridentObj");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"TridentRight");
					ani->SetInfo({ texture, L"TridentRight",{200,32}, 0, 6, 0, 0.5f });
				}
				{
					Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"TridentObj");
					Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"TridentLeft");
					ani->SetInfo({ texture, L"TridentLeft",{200,32}, 0, 6, 1, 0.5f });
				}
			}
		}
	}
#pragma endregion
	
#pragma region 몬스터 애니메이션


	// 몬스터
	{
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SukonbuLeft");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"Sukonbu_MoveLeft");
			ani->SetInfo({ texture, L"Sukonbu_MoveLeft",{64,64}, 0, 2, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SukonbuRight");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"Sukonbu_MoveRight");
			ani->SetInfo({ texture, L"Sukonbu_MoveRight",{64,64}, 0, 2, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SukonbuTypeB");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"SukonbuTypeB_MoveLeft");
			ani->SetInfo({ texture, L"SukonbuTypeB_MoveLeft",{42,32}, 0, 1, 1, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SukonbuTypeB");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"SukonbuTypeB_MoveRight");
			ani->SetInfo({ texture, L"SukonbuTypeB_MoveRight",{42,32}, 0, 1, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SukonbuTypeK");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"SukonbuTypeK_MoveLeft");
			ani->SetInfo({ texture, L"SukonbuTypeK_MoveLeft",{32,32}, 0, 2, 1, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SukonbuTypeK");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"SukonbuTypeK_MoveRight");
			ani->SetInfo({ texture, L"SukonbuTypeK_MoveRight",{32,32}, 0, 2, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SukonbuTypeN");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"SukonbuTypeN_MoveLeft");
			ani->SetInfo({ texture, L"SukonbuTypeN_MoveLeft",{32,32}, 0, 2, 1, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SukonbuTypeN");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"SukonbuTypeN_MoveRight");
			ani->SetInfo({ texture, L"SukonbuTypeN_MoveRight",{32,32}, 0, 2, 0, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SukonbuTypeT");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"SukonbuTypeT_MoveLeft");
			ani->SetInfo({ texture, L"SukonbuTypeT_MoveLeft",{42,36}, 0, 1, 1, 1.f });
		}
		{
			Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(L"SukonbuTypeT");
			Animator* ani = GET_SINGLE(ResourceManager)->CreateAnimator(L"SukonbuTypeT_MoveRight");
			ani->SetInfo({ texture, L"SukonbuTypeT_MoveRight",{42,36}, 0, 1, 0, 1.f });
		}

#pragma endregion
	}
#pragma endregion

	GET_SINGLE(ObjectPool)->Init();

	GET_SINGLE(SpawnManager)->Init();
	GET_SINGLE(StageManager)->StartStage();
	GET_SINGLE(EquipmentManager)->Init();

	

	{
		Player* player = new Player();
		assert(player != nullptr);
		player->Init();
		player->SetPos({ 400,400 });
		AddObject(player);

		GET_SINGLE(GameManager)->SetPlayer(player);

	}
	{
		Camera* camera = new Camera();
		camera->SetPos({ 400,400 });
		camera->SetTarget(GET_SINGLE(GameManager)->GetPlayer());
		AddObject(camera);
	}

	{
		PlayerHudPanel* hudPanel = new PlayerHudPanel();
		hudPanel->SetLayer(LAYER_UI);

		GET_SINGLE(UiLayoutManager)->Load("ui_Playerlay.json", hudPanel->GetPanels());
		AddObject(hudPanel);
	}
	{
		EquipmentHud* equipmentHud = new EquipmentHud();
		equipmentHud->Init();
		equipmentHud->SetLayer(LAYER_UI);
		AddObject(equipmentHud);
		GET_SINGLE(UiLayoutManager)->Load("ui_Equipmentlay.json", equipmentHud->GetPanels());
		GET_SINGLE(EquipmentManager)->SetEquipmentHud(equipmentHud);
	}
	{
		EquipmentSelectHud* equipmentSelectHud = new EquipmentSelectHud();
		equipmentSelectHud->SetLayer(LAYER_UI);
		equipmentSelectHud->SetIsActivity(false);

		GET_SINGLE(UiLayoutManager)->Load("ui_EquipmentSelectlay.json", equipmentSelectHud->GetPanels());
		AddObject(equipmentSelectHud);
	}
	{
		GameOverHud* hudPanel = new GameOverHud();
		hudPanel->SetLayer(LAYER_UI);
		hudPanel->SetIsActivity(false);

		GET_SINGLE(UiLayoutManager)->Load("ui_layoutGameOverlay.json", hudPanel->GetPanels());
		AddObject(hudPanel);
	}

#pragma region Sound 
	{
		sound = GET_SINGLE(ResourceManager)->GetSound(L"Stage01BGM");
		sound->Play(true);
	}

#pragma endregion
	
}

void DevScene::Update()
{
	Super::Update();

	GET_SINGLE(StageManager)->Update();
	GET_SINGLE(EquipmentManager)->UpdateAll();

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::Q))
	{
		GET_SINGLE(ObjectPool)->Debug();
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::E))
	{
		_debug = !_debug;
		GET_SINGLE(GameManager)->SetDebugShow(_debug);
	}
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);
	// 현재 소환된 몬스터 수 확인용
	//GET_SINGLE(SpawnManager)->Render(hdc);
}

