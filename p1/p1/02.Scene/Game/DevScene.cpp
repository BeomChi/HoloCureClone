#include "pch.h"
#include "DevScene.h"
#include "../../01.Manager/InputManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/ObjectManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/SpawnManager.h"
#include "../../01.Manager/StageManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/EquipmentManager.h"
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
#include "../../04.Component/2D/SpriteRenderer.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../05.Resource/2D/Texture.h"
#include "../../05.Resource/2D/Animator.h"
#include "../../05.Resource/2D/Sprite.h"
#include "../../06.Ui/Button.h"


DevScene::DevScene()
{
	
}

DevScene::~DevScene()
{
	GET_SINGLE(EquipmentManager)->Clear();
}

void DevScene::Init()
{

	GET_SINGLE(ResourceManager)->LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.bmp");

	GET_SINGLE(ResourceManager)->LoadTexture(L"GuraLeft", L"Sprite\\Player\\GuraAniLeft.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"GuraRight", L"Sprite\\Player\\GuraAniRight.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"GuraImage", L"Sprite\\Player\\Gura.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"PlayerDie", L"Sprite\\Player\\PlayerDie.bmp");

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


	GET_SINGLE(ResourceManager)->LoadTexture(L"FanSpawn", L"Sprite\\Object\\FanSpawn.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"FanDie", L"Sprite\\Object\\FanDie.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Exp", L"Sprite\\Object\\Exp.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"HealObject", L"Sprite\\Object\\Hamburger.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Bullets", L"Sprite\\Object\\Bullets.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"BLBook", L"Sprite\\Object\\BLBook.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Miasma", L"Sprite\\Object\\Miasma.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Bomb", L"Sprite\\Object\\Bomb.bmp");

	GET_SINGLE(ResourceManager)->LoadTexture(L"EnCurse", L"Sprite\\Object\\EnCurse.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"FanBeam", L"Sprite\\Object\\FanBeam.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"LavaStart", L"Sprite\\Object\\LavaStart.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"LavaLoop", L"Sprite\\Object\\LavaLoop.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"LavaEnd", L"Sprite\\Object\\LavaEnd.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Explode", L"Sprite\\Object\\Explode.bmp");


	GET_SINGLE(ResourceManager)->CreateSprite(L"Stage01", GET_SINGLE(ResourceManager)->GetTexture(L"Stage01"));

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
	GET_SINGLE(ResourceManager)->CreateSprite(L"Bomb", GET_SINGLE(ResourceManager)->GetTexture(L"Bomb"));
	
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
		GET_SINGLE(ObjectManager)->AddObject(background);
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

	// 오브젝트
	{
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
			}
		}
	}
	
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
	}

	GET_SINGLE(SpawnManager)->SetMaxSpawnCount(40);
	GET_SINGLE(SpawnManager)->Init();
	GET_SINGLE(StageManager)->StartStage();

	GET_SINGLE(ObjectPool)->Init();
	{
		Player* player = GET_SINGLE(ObjectPool)->Get<Player>(L"Player");
		player->SetPos({ 400,400 });
		GET_SINGLE(ObjectManager)->AddObject(player);
		GET_SINGLE(GameManager)->SetPlayer(player);

		Bomb* tsetWeapon = new Bomb();
		tsetWeapon->Init();
		GET_SINGLE(EquipmentManager)->AddEquiment(tsetWeapon);
	}
	{
		Camera* camera = new Camera();
		camera->SetPos({ 400,400 });
		GET_SINGLE(ObjectManager)->AddObject(camera);
	}

	/*{
		Fubura* monster = GET_SINGLE(ObjectPool)->Get<Fubura>(L"Fubura");
		monster->SetPos({ 800,400 });
		GET_SINGLE(ObjectManager)->AddObject(monster);
	}
	{
		Shubangelion* monster = GET_SINGLE(ObjectPool)->Get<Shubangelion>(L"Shubangelion");
		monster->SetPos({ 800,800 });
		GET_SINGLE(ObjectManager)->AddObject(monster);
	}*/
	/*{
		NormalMonster* monster = GET_SINGLE(ObjectPool)->Get<NormalMonster>(L"NormalMonster");
		monster->SetPos({ 800,800 });
		GET_SINGLE(ObjectManager)->AddObject(monster);
	}*/


	Super::Init();
}

void DevScene::Update()
{
	Super::Update();
	GET_SINGLE(StageManager)->Update();
	GET_SINGLE(EquipmentManager)->UpdateAll();
}

void DevScene::Render(HDC hdc)
{
	Super::Render(hdc);
	GET_SINGLE(SpawnManager)->Render(hdc);
}

