#include "pch.h"
#include "ResourceManager.h"



ResourceManager::ResourceManager(ComPtr<ID3D11Device> device) : _device(device)
{
}

ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init(HWND hwnd, fs::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;

	CreateDefaultTexture();
	CreateDefaultAnimation();
	CreateDefaultShader();
	CreateDefaultMaterial();
	CreateDefaultMesh();
	
	LoadGameResouresTexture();
	CreateameResouresSprite();
	CreateameResouresAnimation();
}

void ResourceManager::Clear()
{
	for (auto& resourceMap : _resources)
	{
		for (auto& resource : resourceMap)
		{
			SAFE_DELETE(resource.second);
		}

		resourceMap.clear();
	}

	/*for (auto& item : _textures)
		SAFE_DELETE(item.second);

	_textures.clear();

	for (auto& item : _sprites)
		SAFE_DELETE(item.second);

	_sprites.clear();

	for (auto& item : _animators)
		SAFE_DELETE(item.second);

	_animators.clear();

	for (auto& item : _sound)
		SAFE_DELETE(item.second);

	_sound.clear();*/
}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent)
{
	Texture* texture = Get<Texture>(key);
	if (texture != nullptr)
		return texture;

	fs::path fullPath = _resourcePath / path;

	texture = new Texture(_device);

	texture->SetName(key);
	texture->Create(fullPath.wstring());
	Add(texture->GetName(), texture);

	//texture->Loadbmp(_hwnd, fullPath.c_str());
	//texture->SetTransparent(transparent);
	//_textures[key] = texture;

	return texture;
}

Sprite* ResourceManager::CreateSprite(const wstring& key, Texture* texture, int32 x, int32 y, 
	int32 cx, int32 cy)
{
	Sprite* sprite = Get<Sprite>(key);
	if (sprite != nullptr)
		return sprite;


	if (cx == 0)
		cx = texture->GetSize().x;

	if (cy == 0)
		cy = texture->GetSize().y;

	sprite = new Sprite(texture, x, y, cx, cy);
	sprite->SetName(key);
	Add(sprite->GetName(), sprite);
	//_sprites[key] = sprite;

	return sprite;
}

Animation* ResourceManager::CreateAnimator(const wstring& key)
{
	Animation* ani = Get<Animation>(key);
	if (ani != nullptr)
		return ani;

	ani = new Animation();
	ani->SetName(key);
	Add(ani->GetName(), ani);

	return ani;
}

Sound* ResourceManager::LoadSound(const wstring& key, const wstring& path)
{
	Sound* sound = Get<Sound>(key);
	if (sound != nullptr)
		return sound;

	fs::path fullPath = _resourcePath / path;

	sound = new Sound();
	sound->SetName(key);
	sound->LoadWave(fullPath);
	Add(sound->GetName(), sound);

	return sound;
}

void ResourceManager::CreateDefaultTexture()
{
	{
		//fs::path fullPath = _resourcePath / L"Sprite/Ui/Title.png";
		fs::path fullPath = _resourcePath / L"엘따끄.png";
		//LoadTexture(L"엘렐레", fullPath);
		auto texture = new Texture(_device);
		texture->SetName(L"엘렐레");
		texture->Create(fullPath.wstring());

		Add(texture->GetName(), texture);
	}
	{
		/*fs::path fullPath = _resourcePath / L"Sprite\\Player\\GuraAniLeft.bmp";
		auto texture = new Texture(_device);
		texture->SetName(L"Gura");
		texture->Create(fullPath.wstring());
		Add(texture->GetName(), texture);*/
	}


}

void ResourceManager::CreateDefaultAnimation()
{
	Animation* animation = new Animation();

	animation->SetName(L"GuraAnim");
	animation->SetTexture(Get<Texture>(L"Gura"));
	animation->SetLoop(true);

	animation->AddKeyframe(Keyframe{ Vec2{0.f,34.f},Vec2{64.f,34.f},0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{64.f,34.f},Vec2{64.f,34.f},0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{128.f,34.f},Vec2{64.f,34.f},0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{192.f,34.f},Vec2{64.f,34.f},0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{256.f,34.f},Vec2{64.f,34.f},0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{320.f,34.f},Vec2{64.f,34.f},0.1f });

	Add(animation->GetName(), animation);


}

void ResourceManager::CreateDefaultShader()
{
	// Shaders vertex
	VertexShader* vertexShader = new VertexShader(_device);
	vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	// input layout
	InputLayout* inputLayout = new InputLayout(_device);
	inputLayout->Create(VertexTextureData::descs, vertexShader->GetBlob());

	// Shader pixel
	PixelShader* pixelShader = new PixelShader(_device);
	pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	Shader* shader = new Shader();
	shader->SetName(L"Default");
	shader->_vertexShader = vertexShader;
	shader->_inputLayout = inputLayout;
	shader->_pixelShader = pixelShader;
	Add(shader->GetName(), shader);
}

void ResourceManager::CreateDefaultMaterial()
{
	Material* material = new Material();
	material->SetName(L"Default");
	material->SetShader(Get<Shader>(L"Default"));
	material->SetTexture(Get<Texture>(L"엘렐레"));
	Add(material->GetName(), material);
}

void ResourceManager::CreateDefaultMesh()
{
	Mesh* mesh = new Mesh(_device);
	mesh->SetName(L"Rectangle");
	mesh->CreateDefautRectangle();
	Add(mesh->GetName(), mesh);
}

void ResourceManager::LoadGameResouresTexture()
{
	LoadTexture(L"Title", L"Sprite/Ui/Title.png");
	LoadTexture(L"MenuBackground", L"Sprite\\Ui\\menuBackground.bmp");
	LoadTexture(L"Start", L"Sprite\\Ui\\Start.png");

	LoadTexture(L"Stage01", L"Sprite\\Map\\Stage01.png");

	LoadTexture(L"GuraLeft", L"Sprite\\Player\\GuraAniLeft.png");
	LoadTexture(L"GuraRight", L"Sprite\\Player\\GuraAniRight.png");
	LoadTexture(L"GuraImage", L"Sprite\\Player\\Gura.png");
	LoadTexture(L"PlayerDie", L"Sprite\\Player\\PlayerDie.png");
	LoadTexture(L"GuraIcon", L"Sprite\\Player\\GuraIcon.png");

	LoadTexture(L"FuburaLeft", L"Sprite\\Monster\\Fubura\\FuburaLeft.png");
	LoadTexture(L"FuburaRight", L"Sprite\\Monster\\Fubura\\FuburaRight.png");
	LoadTexture(L"FuburaLaserStart", L"Sprite\\Monster\\Fubura\\LaserStart.png");
	LoadTexture(L"FuburaLaser", L"Sprite\\Monster\\Fubura\\Laser.png");

	LoadTexture(L"ShubagelionAttack", L"Sprite\\Monster\\Shubangelion\\ShubagelionAttack.png");
	LoadTexture(L"ShubangelionCharge", L"Sprite\\Monster\\Shubangelion\\ShubangelionCharge.png");
	LoadTexture(L"ShubangelionLeft", L"Sprite\\Monster\\Shubangelion\\ShubangelionLeft.png");
	LoadTexture(L"ShubangelionRight", L"Sprite\\Monster\\Shubangelion\\ShubangelionRight.png");

	LoadTexture(L"SukonbuLeft", L"Sprite\\Monster\\Sukonbu\\SukonbuLeft.png");
	LoadTexture(L"SukonbuRight", L"Sprite\\Monster\\Sukonbu\\SukonbuRight.png");
	LoadTexture(L"SukonbuTypeB", L"Sprite\\Monster\\Sukonbu\\SukonbuTypeB.png");
	LoadTexture(L"SukonbuTypeK", L"Sprite\\Monster\\Sukonbu\\SukonbuTypeK.png");
	LoadTexture(L"SukonbuTypeN", L"Sprite\\Monster\\Sukonbu\\SukonbuTypeN.png");
	LoadTexture(L"SukonbuTypeT", L"Sprite\\Monster\\Sukonbu\\SukonbuTypeT.png");

	// 장비
	LoadTexture(L"FanSpawn", L"Sprite\\Object\\FanSpawn.png");
	LoadTexture(L"FanDie", L"Sprite\\Object\\FanDie.png");
	LoadTexture(L"Exp", L"Sprite\\Object\\Exp.png");
	LoadTexture(L"HealObject", L"Sprite\\Object\\Hamburger.png");
	LoadTexture(L"Bullets", L"Sprite\\Object\\Bullets.png");
	LoadTexture(L"BLBook", L"Sprite\\Object\\BLBook.png");
	LoadTexture(L"Miasma", L"Sprite\\Object\\Miasma.png");
	LoadTexture(L"BombObj", L"Sprite\\Object\\Bomb.png");


	LoadTexture(L"EnCurse", L"Sprite\\Object\\EnCurse.png");
	LoadTexture(L"FanBeam", L"Sprite\\Object\\FanBeam.png");
	LoadTexture(L"LavaStart", L"Sprite\\Object\\LavaStart.png");
	LoadTexture(L"LavaLoop", L"Sprite\\Object\\LavaLoop.png");
	LoadTexture(L"LavaEnd", L"Sprite\\Object\\LavaEnd.png");
	LoadTexture(L"Explode", L"Sprite\\Object\\Explode.png");
	LoadTexture(L"PsychoAxe", L"Sprite\\Object\\PsychoAxe.png");
	LoadTexture(L"Stick", L"Sprite\\Object\\Stick.png");
	LoadTexture(L"StickExplode", L"Sprite\\Object\\StickExplode.png");
	LoadTexture(L"Sausage", L"Sprite\\Object\\Sausage.png");
	LoadTexture(L"Splash", L"Sprite\\Object\\Splash.png");
	LoadTexture(L"TridentObj", L"Sprite\\Object\\Trident.png");

	// UI
	LoadTexture(L"PlayerHpBar", L"Sprite\\Ui\\PlayerHpBar.png");
	LoadTexture(L"PlayerHUD1", L"Sprite\\Ui\\PlayerHUD1.png");
	LoadTexture(L"ExpBarFrame", L"Sprite\\Ui\\ExpBarFrame.png");
	LoadTexture(L"ExpBar", L"Sprite\\Ui\\ExpBar.bmp");
	LoadTexture(L"DefaultEquipmentIcon", L"Sprite\\Ui\\DefaultEquipmentIcon.png");
	LoadTexture(L"WeaponIcon_1", L"Sprite\\Ui\\WeaponIcon_1.png");
	LoadTexture(L"WeaponIcon_2", L"Sprite\\Ui\\WeaponIcon_2.png");
	LoadTexture(L"ItmeMenu_Menu", L"Sprite\\Ui\\ItmeMenu_Menu.png");
	LoadTexture(L"Trident", L"Sprite\\Ui\\Trident.png");
	LoadTexture(L"Pistol", L"Sprite\\Ui\\Pistol.png");
	LoadTexture(L"KillCount_Coin", L"Sprite\\Ui\\KillCount_Coin.png");
	LoadTexture(L"Numbers", L"Sprite\\Ui\\Numbers.png");
	LoadTexture(L"Level", L"Sprite\\Ui\\Level.png");
	LoadTexture(L"SettingMenuBG", L"Sprite\\Ui\\SettingMenue.bmp");
	LoadTexture(L"DefaultButtonImage", L"Sprite\\Ui\\SettingButton.png");
}

void ResourceManager::CreateameResouresSprite()
{
	CreateSprite(L"Start_Off", Get<Texture>(L"Start"), 0, 0, 150, 150);
	CreateSprite(L"Start_On", Get<Texture>(L"Start"), 150, 0, 150, 150);
	CreateSprite(L"Title", Get<Texture>(L"Title"));
	CreateSprite(L"MenuBackground", Get<Texture>(L"MenuBackground"));

	CreateSprite(L"Stage01", Get<Texture>(L"Stage01"));
	CreateSprite(L"SettingMenuBG", Get<Texture>(L"SettingMenuBG"));

	CreateSprite(L"Exp01", Get<Texture>(L"Exp"), 0, 0, 16, 18);
	CreateSprite(L"Exp02", Get<Texture>(L"Exp"), 16, 0, 16, 18);
	CreateSprite(L"Exp03", Get<Texture>(L"Exp"), 32, 0, 16, 18);
	CreateSprite(L"Exp04", Get<Texture>(L"Exp"), 48, 0, 16, 18);
	CreateSprite(L"Exp05", Get<Texture>(L"Exp"), 64, 0, 16, 18);
	CreateSprite(L"Exp06", Get<Texture>(L"Exp"), 80, 0, 16, 18);

	CreateSprite(L"Bullet01", Get<Texture>(L"Bullets"), 0, 0, 17, 17);
	CreateSprite(L"Bullet02", Get<Texture>(L"Bullets"), 17, 0, 17, 17);
	CreateSprite(L"Bullet03", Get<Texture>(L"Bullets"), 34, 0, 17, 17);
	CreateSprite(L"Bullet04", Get<Texture>(L"Bullets"), 51, 0, 17, 17);
	CreateSprite(L"Bullet05", Get<Texture>(L"Bullets"), 68, 0, 17, 17);
	CreateSprite(L"Bullet06", Get<Texture>(L"Bullets"), 85, 0, 17, 17);

	CreateSprite(L"BLBook", Get<Texture>(L"BLBook"));
	CreateSprite(L"Miasma", Get<Texture>(L"Miasma"));
	CreateSprite(L"BombObj", Get<Texture>(L"BombObj"));

	CreateSprite(L"PlayerHpBarGreen", Get<Texture>(L"PlayerHpBar"), 0, 0, 129, 6);
	CreateSprite(L"PlayerHpBarRed", Get<Texture>(L"PlayerHpBar"), 129, 0, 129, 6);
	CreateSprite(L"PlayerHpBarPuple", Get<Texture>(L"PlayerHpBar"), 258, 0, 129, 6);

	CreateSprite(L"PlayerHUD1", Get<Texture>(L"PlayerHUD1"), 199, 0, 199, 87);
	CreateSprite(L"GuraIcon", Get<Texture>(L"GuraIcon"));

	CreateSprite(L"ExpBarBG", Get<Texture>(L"ExpBarFrame"), 0, 0, 650, 26);
	CreateSprite(L"ExpBarFrame", Get<Texture>(L"ExpBarFrame"), 650, 0, 650, 26);
	CreateSprite(L"ExpBar", Get<Texture>(L"ExpBar"), 0, 0, 650, 26);
	CreateSprite(L"ExpBarFull", Get<Texture>(L"ExpBar"), 0, 26, 650, 26);

	CreateSprite(L"DefaultWeaponIcon", Get<Texture>(L"DefaultEquipmentIcon"), 0, 0, 12, 11);
	CreateSprite(L"DefaultArmorIcon", Get<Texture>(L"DefaultEquipmentIcon"), 12, 0, 12, 11);

	CreateSprite(L"ItemMenuSelect", Get<Texture>(L"ItmeMenu_Menu"), 0, 0, 386, 68);
	CreateSprite(L"ItemMune", Get<Texture>(L"ItmeMenu_Menu"), 386, 0, 386, 68);
	CreateSprite(L"ItemMenuSelectDie", Get<Texture>(L"ItmeMenu_Menu"), 0, 68, 386, 68);
	CreateSprite(L"ItemMenuDie", Get<Texture>(L"ItmeMenu_Menu"), 386, 68, 386, 68);

	CreateSprite(L"SpiderCooking", Get<Texture>(L"WeaponIcon_1"), 0, 0, 25, 20);
	CreateSprite(L"EliteLavaBucket", Get<Texture>(L"WeaponIcon_1"), 25, 0, 25, 20);
	CreateSprite(L"Bomb", Get<Texture>(L"WeaponIcon_1"), 50, 0, 25, 20);
	CreateSprite(L"PsychoAxe", Get<Texture>(L"WeaponIcon_1"), 75, 0, 25, 20);
	CreateSprite(L"BLBook", Get<Texture>(L"WeaponIcon_1"), 100, 0, 25, 20);
	CreateSprite(L"FanBeam", Get<Texture>(L"WeaponIcon_1"), 125, 0, 25, 20);
	CreateSprite(L"GlowStick", Get<Texture>(L"WeaponIcon_1"), 150, 0, 25, 20);

	CreateSprite(L"Sausage", Get<Texture>(L"WeaponIcon_2"), 0, 0, 25, 22);
	CreateSprite(L"EnCurse", Get<Texture>(L"WeaponIcon_2"), 25, 0, 25, 22);
	CreateSprite(L"WamyWater", Get<Texture>(L"WeaponIcon_2"), 50, 0, 25, 22);
	CreateSprite(L"Trident", Get<Texture>(L"Trident"));
	CreateSprite(L"PistolShoot", Get<Texture>(L"Pistol"));
	CreateSprite(L"KillCount", Get<Texture>(L"KillCount_Coin"), 0, 0, 15, 15);
	CreateSprite(L"Coin", Get<Texture>(L"KillCount_Coin"), 15, 0, 15, 15);
	CreateSprite(L"DefaultButton", Get<Texture>(L"DefaultButtonImage"), 0, 0, 180, 29);
	CreateSprite(L"DefaultButtonPress", Get<Texture>(L"DefaultButtonImage"), 0, 29, 180, 29);

	CreateSprite(L"LevelTypeNormal", Get<Texture>(L"Level"), 0, 0, 20, 9);
	CreateSprite(L"LevelTypeCollabo", Get<Texture>(L"Level"), 20, 0, 20, 9);
	CreateSprite(L"LevelTypeExclusive", Get<Texture>(L"Level"), 40, 0, 20, 9);

	CreateSprite(L"NumberTypeNormal0", Get<Texture>(L"Numbers"), 0, 0, 5, 7);
	CreateSprite(L"NumberTypeNormal1", Get<Texture>(L"Numbers"), 5, 0, 5, 7);
	CreateSprite(L"NumberTypeNormal2", Get<Texture>(L"Numbers"), 10, 0, 5, 7);
	CreateSprite(L"NumberTypeNormal3", Get<Texture>(L"Numbers"), 15, 0, 5, 7);
	CreateSprite(L"NumberTypeNormal4", Get<Texture>(L"Numbers"), 20, 0, 5, 7);
	CreateSprite(L"NumberTypeNormal5", Get<Texture>(L"Numbers"), 25, 0, 5, 7);
	CreateSprite(L"NumberTypeNormal6", Get<Texture>(L"Numbers"), 30, 0, 5, 7);
	CreateSprite(L"NumberTypeNormal7", Get<Texture>(L"Numbers"), 35, 0, 5, 7);
	CreateSprite(L"NumberTypeNormal8", Get<Texture>(L"Numbers"), 40, 0, 5, 7);
	CreateSprite(L"NumberTypeNormal9", Get<Texture>(L"Numbers"), 45, 0, 5, 7);

	CreateSprite(L"NumberTypeCollabo0", Get<Texture>(L"Numbers"), 0, 7, 5, 7);
	CreateSprite(L"NumberTypeCollabo1", Get<Texture>(L"Numbers"), 5, 7, 5, 7);
	CreateSprite(L"NumberTypeCollabo2", Get<Texture>(L"Numbers"), 10, 7, 5, 7);
	CreateSprite(L"NumberTypeCollabo3", Get<Texture>(L"Numbers"), 15, 7, 5, 7);
	CreateSprite(L"NumberTypeCollabo4", Get<Texture>(L"Numbers"), 20, 7, 5, 7);
	CreateSprite(L"NumberTypeCollabo5", Get<Texture>(L"Numbers"), 25, 7, 5, 7);
	CreateSprite(L"NumberTypeCollabo6", Get<Texture>(L"Numbers"), 30, 7, 5, 7);
	CreateSprite(L"NumberTypeCollabo7", Get<Texture>(L"Numbers"), 35, 7, 5, 7);
	CreateSprite(L"NumberTypeCollabo8", Get<Texture>(L"Numbers"), 40, 7, 5, 7);
	CreateSprite(L"NumberTypeCollabo9", Get<Texture>(L"Numbers"), 45, 7, 5, 7);

	CreateSprite(L"NumberTypeExclusive0", Get<Texture>(L"Numbers"), 0, 14, 5, 7);
	CreateSprite(L"NumberTypeExclusive1", Get<Texture>(L"Numbers"), 5, 14, 5, 7);
	CreateSprite(L"NumberTypeExclusive2", Get<Texture>(L"Numbers"), 10, 14, 5, 7);
	CreateSprite(L"NumberTypeExclusive3", Get<Texture>(L"Numbers"), 15, 14, 5, 7);
	CreateSprite(L"NumberTypeExclusive4", Get<Texture>(L"Numbers"), 20, 14, 5, 7);
	CreateSprite(L"NumberTypeExclusive5", Get<Texture>(L"Numbers"), 25, 14, 5, 7);
	CreateSprite(L"NumberTypeExclusive6", Get<Texture>(L"Numbers"), 30, 14, 5, 7);
	CreateSprite(L"NumberTypeExclusive7", Get<Texture>(L"Numbers"), 35, 14, 5, 7);
	CreateSprite(L"NumberTypeExclusive8", Get<Texture>(L"Numbers"), 40, 14, 5, 7);
	CreateSprite(L"NumberTypeExclusive9", Get<Texture>(L"Numbers"), 45, 14, 5, 7);
}

void ResourceManager::CreateameResouresAnimation()
{

#pragma region Entity
	{
		{
			Texture* texture = Get<Texture>(L"GuraLeft");
			Animation* ani = CreateAnimator(L"Gura_IdleLeft");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 64,34 },0.5f }, 3, 0);
			//ani->SetInfo({ texture, L"Gura_IdleLeft", {64,34}, 0, 2, 0, 0.5f });
		}
		{
			Texture* texture = Get<Texture>(L"GuraLeft");
			Animation* ani = CreateAnimator(L"GuraMoveLeft");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 64,34 },0.5f }, 6, 1);
			//ani->SetInfo({ texture, L"GuraMoveLeft",{64,34}, 0, 5, 1, 0.5f });
		}
		{
			Texture* texture = Get<Texture>(L"GuraRight");
			Animation* ani = CreateAnimator(L"Gura_IdleRight");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 64,34 },0.5f }, 3, 0);
			//ani->SetInfo({ texture, L"Gura_IdleRight",{64,34}, 0, 2, 0, 0.5f });
		}
		{
			Texture* texture = Get<Texture>(L"GuraRight");
			Animation* ani = CreateAnimator(L"GuraMoveRight");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 64,34 },0.5f }, 6, 1);
			//ani->SetInfo({ texture, L"GuraMoveRight",{64,34}, 0, 5, 1, 0.5f });
		}
	}
	{
		{
			Texture* texture = Get<Texture>(L"FuburaLeft");
			Animation* ani = CreateAnimator(L"Fubura_MoveLeft");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 82,57 },1.f }, 12, 0);
			//ani->SetInfo({ texture, L"Fubura_MoveLeft",{82,57}, 0, 11, 0, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"FuburaRight");
			Animation* ani = CreateAnimator(L"Fubura_MoveRight");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 82,57 },1.f }, 12, 0);
			//ani->SetInfo({ texture, L"Fubura_MoveRight",{82,57}, 0, 11, 0, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"FuburaLaserStart");
			Animation* ani = CreateAnimator(L"FuburaLaserStart");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 465,50 },1.f }, 23, 0);
			//ani->SetInfo({ texture, L"FuburaLaserStart",{465,50}, 0, 22, 0, 0.8f });
		}
		{
			Texture* texture = Get<Texture>(L"FuburaLaser");
			Animation* ani = CreateAnimator(L"FuburaLaser");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 465,50 },1.f }, 12, 0);
			//ani->SetInfo({ texture, L"FuburaLaser",{465,50}, 0, 11, 0, 1.f });
		}
	}
	{
		{
			Texture* texture = Get<Texture>(L"ShubangelionLeft");
			Animation* ani = CreateAnimator(L"Shubangelion_MoveLeft");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 128,135 },1.f }, 8, 0);
			//ani->SetInfo({ texture, L"Shubangelion_MoveLeft",{128,135}, 0, 7, 0, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"ShubangelionRight");
			Animation* ani = CreateAnimator(L"Shubangelion_MoveRight");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 128,135 },1.f }, 8, 0);
			//ani->SetInfo({ texture, L"Shubangelion_MoveRight",{128,135}, 0, 7, 0, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"ShubangelionCharge");
			Animation* ani = CreateAnimator(L"Shubangelion_Charge");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 128,135 },2.f }, 3, 0);
			//ani->SetInfo({ texture, L"Shubangelion_Charge",{128,135}, 0, 2, 0, 2.f });
		}
		{
			Texture* texture = Get<Texture>(L"ShubagelionAttack");
			Animation* ani = CreateAnimator(L"Shubagelion_Attack");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 128,135 },1.f }, 10, 0);
			//ani->SetInfo({ texture, L"Shubagelion_Attack",{128,135}, 0, 9, 0, 1.f });
		}
	}

#pragma endregion

#pragma region 오브젝트

#pragma region 몬스터 공격 이펙트 애니메이션
	{
		Texture* texture = Get<Texture>(L"FanSpawn");
		Animation* ani = CreateAnimator(L"FanSpawn");
		ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 67,114 },0.25f }, 4, 0, false);
		//ani->SetInfo({ texture, L"FanSpawn",{67,114}, 0, 3, 0, 0.25f,false });
	}
	{
		Texture* texture = Get<Texture>(L"FanDie");
		Animation* ani = CreateAnimator(L"FanDie");
		ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 48,48 },0.5f }, 10, 0, false);
		//ani->SetInfo({ texture, L"FanSpawn",{48,48}, 0, 9, 0, 0.5f,false });
	}
	{
		Texture* texture = Get<Texture>(L"HealObject");
		Animation* ani = CreateAnimator(L"HealObject");
		ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 32,32 },1.f }, 8, 0);
		//ani->SetInfo({ texture, L"HealObject",{32,32}, 0, 7, 0, 1.f });
	}
	{
		Texture* texture = Get<Texture>(L"PlayerDie");
		Animation* ani = CreateAnimator(L"PlayerDie");
		ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 32,32 },1.f }, 4, 0);
		//ani->SetInfo({ texture, L"PlayerDie",{32,32}, 0, 3, 0, 1.f });
	}
#pragma endregion

#pragma region 장비 이펙트 애니메이션
	// 장비
	{
		// 무기
		{
			{
				Texture* texture = Get<Texture>(L"LavaStart");
				Animation* ani = CreateAnimator(L"LavaStart");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 127,127 },0.5f }, 9, 0);
				//ani->SetInfo({ texture, L"LavaStart",{127,127}, 0, 8, 0, 0.5f });
			}
			{
				Texture* texture = Get<Texture>(L"LavaLoop");
				Animation* ani = CreateAnimator(L"LavaLoop");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 127,127 },1.f }, 14, 0);
				//ani->SetInfo({ texture, L"LavaLoop",{127,127}, 0, 13, 0, 1.f });
			}
			{
				Texture* texture = Get<Texture>(L"LavaEnd");
				Animation* ani = CreateAnimator(L"LavaEnd");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 127,127 },0.5f }, 6, 0);
				//ani->SetInfo({ texture, L"LavaEnd",{127,127}, 0, 5, 0, 0.5f });
			}
			{
				Texture* texture = Get<Texture>(L"EnCurse");
				Animation* ani = CreateAnimator(L"EnCurseRight");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 36,21 },0.5f }, 8, 0);
				//ani->SetInfo({ texture, L"EnCurseRight",{36,21}, 0, 7, 0, 0.5f });
			}
			{
				Texture* texture = Get<Texture>(L"EnCurse");
				Animation* ani = CreateAnimator(L"EnCurseLeft");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 36,21 },0.5f }, 8, 1);
				//ani->SetInfo({ texture, L"EnCurseLeft",{36,21}, 0, 7, 1, 0.5f });
			}
			{
				Texture* texture = Get<Texture>(L"FanBeam");
				Animation* ani = CreateAnimator(L"FanBeamRight");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 466,51 },1.f }, 10, 0);
				//ani->SetInfo({ texture, L"FanBeamRight",{466,51}, 0, 9, 0, 1.f });
			}
			{
				Texture* texture = Get<Texture>(L"FanBeam");
				Animation* ani = CreateAnimator(L"FanBeamLeft");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 466,51 },1.f }, 10, 1);
				//ani->SetInfo({ texture, L"FanBeamLeft",{466,51}, 0, 9, 1, 1.f });
			}
			{
				Texture* texture = Get<Texture>(L"Explode");
				Animation* ani = CreateAnimator(L"BombExplode");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 128,128 },1.f }, 13, 0);
				//ani->SetInfo({ texture, L"BombExplode",{128,128}, 0, 12, 0, 1.f });
			}
			{
				Texture* texture = Get<Texture>(L"PsychoAxe");
				Animation* ani = CreateAnimator(L"PsychoAxe");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 46,46 },1.0f }, 8, 0);
				//ani->SetInfo({ texture, L"PsychoAxe",{46,46}, 0, 7, 0, 1.f });
			}
			{
				Texture* texture = Get<Texture>(L"Stick");
				Animation* ani = CreateAnimator(L"Stick");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 46,46 },1.0f }, 8, 0);
				//ani->SetInfo({ texture, L"Stick",{46,46}, 0, 7, 0, 1.f });
			}
			{
				Texture* texture = Get<Texture>(L"StickExplode");
				Animation* ani = CreateAnimator(L"StickExplode");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 93,91 },1.0f }, 7, 0);
				//ani->SetInfo({ texture, L"StickExplode",{93,91}, 0, 6, 0, 1.f });
			}
			{
				Texture* texture = Get<Texture>(L"Sausage");
				Animation* ani = CreateAnimator(L"SausageRight");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 128,128 },1.0f }, 5, 0);
				//ani->SetInfo({ texture, L"SausageRight",{128,128}, 0, 4, 0, 1.f });
			}
			{
				Texture* texture = Get<Texture>(L"Sausage");
				Animation* ani = CreateAnimator(L"SausageLeft");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 128,128 },1.0f }, 5, 1);
				//ani->SetInfo({ texture, L"SausageLeft",{128,128}, 0, 4, 1, 1.f });
			}
			{
				Texture* texture = Get<Texture>(L"Splash");
				Animation* ani = CreateAnimator(L"SplashRight");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 128,128 },0.25f }, 6, 0);
				//ani->SetInfo({ texture, L"SplashRight",{128,128}, 0, 5,0, 0.25f });
			}
			{
				Texture* texture = Get<Texture>(L"Splash");
				Animation* ani = CreateAnimator(L"SplashLeft");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 128,128 },0.25f }, 6, 1);
				//ani->SetInfo({ texture, L"SplashLeft",{128,128}, 0, 5, 1, 0.25f });
			}
			{
				Texture* texture = Get<Texture>(L"TridentObj");
				Animation* ani = CreateAnimator(L"TridentRight");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 200,32 },0.5f }, 7, 0);
				//ani->SetInfo({ texture, L"TridentRight",{200,32}, 0, 6, 0, 0.5f });
			}
			{
				Texture* texture = Get<Texture>(L"TridentObj");
				Animation* ani = CreateAnimator(L"TridentLeft");
				ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 200,32 },0.5f }, 7, 1);
				//ani->SetInfo({ texture, L"TridentLeft",{200,32}, 0, 6, 1, 0.5f });
			}
		}
	}

#pragma endregion

#pragma region 몬스터 애니메이션
	// 몬스터
	{
		{
			Texture* texture = Get<Texture>(L"SukonbuLeft");
			Animation* ani = CreateAnimator(L"Sukonbu_MoveLeft");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 64,64 },1.f }, 3, 0);
			//ani->SetInfo({ texture, L"Sukonbu_MoveLeft",{64,64}, 0, 2, 0, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"SukonbuRight");
			Animation* ani = CreateAnimator(L"Sukonbu_MoveRight");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 64,64 },1.f }, 3, 0);
			//ani->SetInfo({ texture, L"Sukonbu_MoveRight",{64,64}, 0, 2, 0, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"SukonbuTypeB");
			Animation* ani = CreateAnimator(L"SukonbuTypeB_MoveLeft");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 42,32 },1.f }, 2, 1);
			//ani->SetInfo({ texture, L"SukonbuTypeB_MoveLeft",{42,32}, 0, 1, 1, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"SukonbuTypeB");
			Animation* ani = CreateAnimator(L"SukonbuTypeB_MoveRight");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 42,32 },1.f }, 2, 0);
			//ani->SetInfo({ texture, L"SukonbuTypeB_MoveRight",{42,32}, 0, 1, 0, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"SukonbuTypeK");
			Animation* ani = CreateAnimator(L"SukonbuTypeK_MoveLeft");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 32,32 },1.f }, 3, 1);
			//ani->SetInfo({ texture, L"SukonbuTypeK_MoveLeft",{32,32}, 0, 2, 1, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"SukonbuTypeK");
			Animation* ani = CreateAnimator(L"SukonbuTypeK_MoveRight");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 32,32 },1.f }, 3, 0);
			//ani->SetInfo({ texture, L"SukonbuTypeK_MoveRight",{32,32}, 0, 2, 0, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"SukonbuTypeN");
			Animation* ani = CreateAnimator(L"SukonbuTypeN_MoveLeft");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 32,32 },1.f }, 3, 1);
			//ani->SetInfo({ texture, L"SukonbuTypeN_MoveLeft",{32,32}, 0, 2, 1, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"SukonbuTypeN");
			Animation* ani = CreateAnimator(L"SukonbuTypeN_MoveRight");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 32,32 },1.f }, 3, 0);
			//ani->SetInfo({ texture, L"SukonbuTypeN_MoveRight",{32,32}, 0, 2, 0, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"SukonbuTypeT");
			Animation* ani = CreateAnimator(L"SukonbuTypeT_MoveLeft");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 42,36 },1.f }, 2, 1);
			//ani->SetInfo({ texture, L"SukonbuTypeT_MoveLeft",{42,36}, 0, 1, 1, 1.f });
		}
		{
			Texture* texture = Get<Texture>(L"SukonbuTypeT");
			Animation* ani = CreateAnimator(L"SukonbuTypeT_MoveRight");
			ani->AddKeyframesByCount(texture, { { 0.f,0.f },{ 42,36 },1.f }, 2, 0);
			//ani->SetInfo({ texture, L"SukonbuTypeT_MoveRight",{42,36}, 0, 1, 0, 1.f });
		}

#pragma endregion
#pragma endregion

}
