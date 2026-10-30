#include "pch.h"
#include "StartScene.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../04.Component/2D/SpriteRenderer.h"
#include "97.Engin/Resource/Sprite.h"
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
	cout << "Scene Start State: " << (int)GAMEMANAGER->GetState() << endl;
	RESOURCE->LoadSound(L"Stage01BGM", L"Sound\\Stage01\\Stage01BGM.wav");

	RESOURCE->LoadTexture(L"Start", L"Sprite\\Ui\\Start.bmp");
	RESOURCE->LoadTexture(L"Title", L"Sprite\\Ui\\Title.bmp");
	RESOURCE->LoadTexture(L"MenuBackground", L"Sprite\\Ui\\menuBackground.bmp");

	RESOURCE->CreateSprite(L"Start_Off", RESOURCE->Get<Texture>(L"Start"), 0, 0, 150, 150);
	RESOURCE->CreateSprite(L"Start_On", RESOURCE->Get<Texture>(L"Start"), 150, 0, 150, 150);
	RESOURCE->CreateSprite(L"Title", RESOURCE->Get<Texture>(L"Title"));
	RESOURCE->CreateSprite(L"MenuBackground", RESOURCE->Get<Texture>(L"MenuBackground"));

	// 버튼 이미지 찾으면 교체하자
	_ui = new Button();
	_ui->SetSprite(RESOURCE->Get<Sprite>(L"Start_Off"), BS_Default);
	_ui->SetSprite(RESOURCE->Get<Sprite>(L"Start_On"), BS_Pressed);
	_ui->SetPos({ 400 ,400 });
	_ui->SetSize({ 150,150 });

	_ui->SetLayer(LAYER_UI);
	_ui->SetKey(L"StartButton");
	_ui->AddOnClickDelegate(this, &StartScene::GameStart);
	_uis.push_back(_ui);
	AddObject(_ui);

	{
		Sprite* sprite = RESOURCE->Get<Sprite>(L"Title");

		Image* Title = new Image();
		Title->SetSprite(sprite);
		const Vec2 size = sprite->GetSize();
		Title->SetSize({ (float)sprite->GetSize().x, (float)sprite->GetSize().y });

		Title->SetPos({400,200});

		AddObject(Title);
		_uis.push_back(Title);
	}
	{
		{
			Sprite* sprite = RESOURCE->Get<Sprite>(L"MenuBackground");

			Image* background = new Image();
			background->SetSprite(sprite);
			background->SetLayer(LAYER_BACKGROUND);
			const Vec2 size = sprite->GetSize();
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

// 씬전환 도중 전에 씬은 계속 업데이트 중이라
// 이미 지워진 포인터에 접근하는 문제를 막고자
// 씬 전환을 지연 시키는 방향으로 수정
// 단점이 생긴다면 매프레임마다 검사를 한다는 건데 뭐 그 정도는 괜찮겠지
void StartScene::GameStart()
{
	GAMEMANAGER->SetState(GameState::Playing);
	SCENE->SetNextSceneType(SceneType::DevScene);
	//GET_SINGLE(SceneManager)->ChangeScnee(SceneType::DevScene);
}

void StartScene::StartEditMode()
{
	GAMEMANAGER->SetState(GameState::Playing);
	SCENE->SetNextSceneType(SceneType::EditScene);
}


