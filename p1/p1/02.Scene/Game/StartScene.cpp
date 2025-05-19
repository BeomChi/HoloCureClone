#include "../../pch.h"
#include "StartScene.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/ObjectManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../05.Resource/2D/Sprite.h"
#include "../../06.Ui/Button.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
	_ui->SetIsActivity(false);
}

void StartScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadTexture(L"Start", L"Sprite\\Ui\\Start.bmp");

	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_Off", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 0, 0, 150, 150);
	GET_SINGLE(ResourceManager)->CreateSprite(L"Start_On", GET_SINGLE(ResourceManager)->GetTexture(L"Start"), 150, 0, 150, 150);

	_ui = new Button();
	_ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_Off"), BS_Default);
	_ui->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Start_On"), BS_Pressed);
	_ui->SetPos({ 400 ,300 });
	_ui->SetSize({ 150,150 });

	_ui->SetLayer(LAYER_UI);
	_ui->SetKey(L"StartButton");
	_ui->AddOnClickDelegate(this, &StartScene::GameStart);
	GET_SINGLE(ObjectManager)->AddObject(_ui);


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
