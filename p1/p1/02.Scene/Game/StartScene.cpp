#include "pch.h"
#include "StartScene.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../04.Component/2D/SpriteRenderer.h"
#include "97.Engin/Resource/Sprite.h"
#include "../../06.Ui/Button.h"
#include "../../06.Ui/Image.h"
#include "97.Engin/Component/Transform/Transform.h"
#include "97.Engin/Component/Renderer/MeshRenderer.h"
#include "97.Engin/Component/Camera/Camera.h"

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
	//RESOURCE->LoadSound(L"Stage01BGM", L"Sound\\Stage01\\Stage01BGM.wav");

	//RESOURCE->LoadTexture(L"Title", L"Sprite/Ui/Title.png");
	//RESOURCE->LoadTexture(L"MenuBackground", L"Sprite\\Ui\\menuBackground.bmp");
	//RESOURCE->LoadTexture(L"Start", L"Sprite\\Ui\\Start.bmp");

	//RESOURCE->CreateSprite(L"Start_Off", RESOURCE->Get<Texture>(L"Start"), 0, 0, 150, 150);
	//RESOURCE->CreateSprite(L"Start_On", RESOURCE->Get<Texture>(L"Start"), 150, 0, 150, 150);
	//RESOURCE->CreateSprite(L"Title", RESOURCE->Get<Texture>(L"Title"));
	//RESOURCE->CreateSprite(L"MenuBackground", RESOURCE->Get<Texture>(L"MenuBackground"));

	// Camera
	{
		GameObject* camera = new GameObject();
		{
			camera->GetOrAddTransform();
			camera->GetTransform()->SetPosition({ 100, 0, 0});
			camera->AddComponent(new Camera());
			AddObject(camera);
		}
	}

	// 버튼 이미지 찾으면 교체하자
	_ui = new Button();
	auto meshRenderer = new MeshRenderer(SCENE->GetGraphics()->GetDevice(), SCENE->GetGraphics()->GetDeviceContext());
	_ui->AddComponent(meshRenderer);

	auto material = RESOURCE->Get<Material>(L"Default");
	meshRenderer->SetMaterial(material);

	auto mesh = RESOURCE->Get<Mesh>(L"Rectangle");
	meshRenderer->SetMesh(mesh);

	_ui->SetSprite(RESOURCE->Get<Sprite>(L"Start_Off"), BS_Default);
	_ui->SetSprite(RESOURCE->Get<Sprite>(L"Start_On"), BS_Pressed);
	_ui->GetOrAddTransform()->SetPosition({ 0, -100,0 });
	_ui->GetTransform()->SetScale({ 1.f, 1.f,1 });

	auto spriteRenderer = new SpriteRenderer();
	_ui->AddComponent(spriteRenderer);
	spriteRenderer->SetSprite(_ui->GetSprite(BS_Default));
	_ui->SetRenderSize(spriteRenderer->GetSprite()->GetSize());

	Vec3 pos = _ui->GetOrAddTransform()->GetPosition();

	cout << "BUTTON POS : "
		<< pos.x << " "
		<< pos.y << endl;

	_ui->SetLayer(LAYER_UI);
	_ui->SetKey(L"StartButton");
	_ui->AddOnClickDelegate(this, &StartScene::GameStart);
	_ui->Init();
	_uis.push_back(_ui);
	AddObject(_ui);

	{
		Sprite* sprite = RESOURCE->Get<Sprite>(L"Title");

		GameObject* Title = new GameObject();
		Title->GetOrAddTransform()->SetPosition({0,100,0});
		auto meshRenderer = new MeshRenderer(SCENE->GetGraphics()->GetDevice(), SCENE->GetGraphics()->GetDeviceContext());
		Title->AddComponent(meshRenderer);

		auto material = RESOURCE->Get<Material>(L"Default");
		meshRenderer->SetMaterial(material);

		auto mesh = RESOURCE->Get<Mesh>(L"Rectangle");
		meshRenderer->SetMesh(mesh);
		//Title->SetSprite(sprite);

		auto spriteRenderer = new SpriteRenderer();
		spriteRenderer->SetSprite(sprite);
		Title->AddComponent(spriteRenderer);
		Title->SetLayer(LAYER_UI);
		//const Vec2 size = sprite->GetSize();
		//Title->SetSize({ (float)sprite->GetSize().x, (float)sprite->GetSize().y });


		AddObject(Title);
		_uis.push_back(Title);
	}
	//{
	//	{
	//		Sprite* sprite = RESOURCE->Get<Sprite>(L"MenuBackground");

	//		Image* background = new Image();
	//		background->SetSprite(sprite);
	//		background->SetLayer(LAYER_BACKGROUND);

	//		auto spriteRenderer = new SpriteRenderer();
	//		spriteRenderer->SetSprite(sprite);
	//		background->AddComponent(spriteRenderer);

	//		//const Vec2 size = sprite->GetSize();
	//		//background->SetSize({ (float)sprite->GetSize().x, (float)sprite->GetSize().y });
	//		background->GetOrAddTransform()->SetScale({ 2,2,1 });
	//		background->GetTransform()->SetPosition({ 0,50,0 });

	//		AddObject(background);
	//		_uis.push_back(background);
	//	}
	//}


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


