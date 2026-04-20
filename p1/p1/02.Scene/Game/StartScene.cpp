#include "pch.h"
#include "StartScene.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../04.Component/2D/SpriteRenderer.h"
#include "../../05.Resource/2D/Sprite.h"
#include "../../06.Ui/Button.h"
#include "../../06.Ui/Image.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
	//_ui->SetIsActivity(false);
	for (auto ui : _uis)
	{
		ui->SetIsActivity(false);
	}
	Clear();
}

void StartScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadSound(L"Stage01BGM", L"Sound\\Stage01\\Stage01BGM.wav");

	GET_SINGLE(ResourceManager)->LoadTexture(L"Start", L"Sprite\\Ui\\Start.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"Title", L"Sprite\\Ui\\Title.bmp");
	GET_SINGLE(ResourceManager)->LoadTexture(L"MenuBackground", L"Sprite\\Ui\\menuBackground.bmp");

	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Title", GET_SINGLE(ResourceManager)->GetTexture(L"Title"));
	GET_SINGLE(ResourceManager)->CreateSprite(L"MenuBackground", GET_SINGLE(ResourceManager)->GetTexture(L"MenuBackground"));

	// 버튼 이미지 찾으면 교체하자
	_ui = new Button();
	_ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_Off"), BS_Default);
	_ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_On"), BS_Pressed);
	_ui->SetPos({ 400 ,400 });
	_ui->SetSize({ 150,150 });

	_ui->SetLayer(LAYER_UI);
	_ui->SetKey(L"StartButton");
	_ui->AddOnClickDelegate(this, &StartScene::GameStart);
	_uis.push_back(_ui);
	AddObject(_ui);

	{
		Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Title");

		Image* Title = new Image();
		Title->SetSprite(sprite);
		const Vec2Int size = sprite->GetSize();
		Title->SetSize({ (float)sprite->GetSize().x, (float)sprite->GetSize().y });

		Title->SetPos({400,200});

		AddObject(Title);
		_uis.push_back(Title);
	}
	{
		{
			Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"MenuBackground");

			Image* background = new Image();
			background->SetSprite(sprite);
			background->SetLayer(LAYER_BACKGROUND);
			const Vec2Int size = sprite->GetSize();
			background->SetSize({ (float)sprite->GetSize().x, (float)sprite->GetSize().y });
			background->SetScale({ 2,2 });
			background->SetPos({ 0,50 });

			AddObject(background);
			_uis.push_back(background);
		}
	}


	Super::Init();
}

void StartScene::Update()
{
	Super::Update();
}

void StartScene::Render(HDC hdc)
{
	Super::Render(hdc);
}

void StartScene::GameStart()
{
	GET_SINGLE(SceneManager)->ChangeScnee(SceneType::DevScene);
}
