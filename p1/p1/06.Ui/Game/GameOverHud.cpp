#include "pch.h"
#include "GameOverHud.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/StageManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../05.Resource/2D/Sprite.h"
#include "../../06.Ui/Image.h"
#include "../../06.Ui/Game/HpBar.h"
#include "../../06.Ui/Button.h"
#include "../../06.Ui/Text.h"



// 무조건 플레이어 생성된 이후 만들긴
GameOverHud::GameOverHud()
{
	cout << "[DEBUG] GameOverHudPanel 생성됨" << endl;


	{
		// 이거 게임 오버 배경? 큰 틀 이미지로 바꿔야 함
		Image* hud = new Image();

		hud->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"SettingMenuBG"));

		hud->SetSize({ (float)hud->GetSprite()->GetSize().x, (float)hud->GetSprite()->GetSize().y });
		hud->SetPos({ 400,250 });
		hud->SetKey(L"SettingMenuBG");
		hud->SetLayer(LAYER_UI);

		AddPanel(hud);
	}
	{
		Image* Icon = new Image();

		Icon->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"GuraIcon"));

		Icon->SetSize({ (float)Icon->GetSprite()->GetSize().x, (float)Icon->GetSprite()->GetSize().y });
		Icon->SetPos({ 400 ,250 });
		Icon->SetKey(L"GuraIcon");
		Icon->SetLayer(LAYER_UI);

		AddPanel(Icon);
	}
	{
		Image* Coin = new Image();

		Coin->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Coin"));

		Coin->SetSize({ (float)Coin->GetSprite()->GetSize().x, (float)Coin->GetSprite()->GetSize().y });
		Coin->SetScale({ 1.5f,1.5f });
		Coin->SetPos({ 400.f, 330.f });
		Coin->SetKey(L"Coin");
		Coin->SetLayer(LAYER_UI);
		AddPanel(Coin);
	}
	{
		Image* KillCountUi = new Image();

		KillCountUi->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"KillCount"));

		KillCountUi->SetSize({ (float)KillCountUi->GetSprite()->GetSize().x, (float)KillCountUi->GetSprite()->GetSize().y });
		KillCountUi->SetScale({ 1.5f,1.5f });
		KillCountUi->SetPos({ 400.f, 290.f });
		KillCountUi->SetKey(L"KillCount");
		KillCountUi->SetLayer(LAYER_UI);
		AddPanel(KillCountUi);
	}
	{
		_levelText = new Text();
		_levelText->SetText(format(L"Lv.{0}", 1));
		_levelText->SetFontSize(28);
		_levelText->SetPos({ 400.f,50.f });
		_levelText->SetKey(L"LevelText");
		_levelText->SetLayer(LAYER_UI);
		_levelConn = move(GET_SINGLE(GameManager)->GetPlayer()->OnLevelChanged += [this](int32 arg)
			{
				_levelText->SetText(format(L"Lv.{0}", arg));
			});
		AddPanel(_levelText);
	}
	{
		_killText = new Text();
		_killText->SetText(format(L"{0}", 0));
		_killText->SetFontSize(28);
		_killText->SetPos({ 400.f,200.f });
		_killText->SetKey(L"KillCountText");
		_killText->SetLayer(LAYER_UI);
		_killConn = (GET_SINGLE(StageManager)->OnKillCountChanged += [this](int32 arg)
			{
				_killText->SetText(format(L"{0}", arg));
			});
		AddPanel(_killText);
	}
	{
		_coinText = new Text();
		_coinText->SetText(format(L"{0}", 0));
		_coinText->SetFontSize(28);
		_coinText->SetPos({ 400.f,100.f });
		_coinText->SetKey(L"CoinText");
		_coinText->SetLayer(LAYER_UI);
		_coinConn = (GET_SINGLE(StageManager)->OnCoinCountChanged += [this](int32 arg)
			{
				_coinText->SetText(format(L"{0}", arg));
			});
		AddPanel(_coinText);
	}
	{
		_timeText = new Text();
		_timeText->SetText(format(L"Play Time : {0}:{1}", 0, 0));
		_timeText->SetFontSize(28);
		_timeText->SetPos({ 400.f,200.f });
		_timeText->SetKey(L"TimeText");
		_timeText->SetLayer(LAYER_UI);
		_timeConn = (GET_SINGLE(StageManager)->OnTimeChanged += [this](int32 arg)
			{
				_timeText->SetText(FormatTimeMMSS(arg));
			});
		AddPanel(_timeText);
	}
	{
		// 버튼 추가
		_titleButton = new Button();
		// 버튼 이미지랑 크기 좌표 설정 구역
		_titleButton->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"DefaultButton"),BS_Default);
		_titleButton->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"DefaultButtonPress"),BS_Pressed);
		_titleButton->SetPos({ 400,400 });
		_titleButton->SetSize({ 180,29 });
		_titleButton->SetKey(L"TitleButton");
		_titleButton->SetLayer(LAYER_UI);
		_titleButton->AddOnClickDelegate(GET_SINGLE(SceneManager), &SceneManager::GoToTitle);
		AddPanel(_titleButton);
	}
	{
		_titleText = new Text();
		_titleText->SetText(L"Title");
		_titleText->SetFontSize(28);
		_titleText->SetPos({ 400.f,600.f });
		_titleText->SetKey(L"TitleText");
		_titleText->SetLayer(LAYER_UI);
		_titleText->SetColor(RGB(40, 40, 40));
		AddPanel(_titleText);
	}
	{
		_ActivityConn = (GET_SINGLE(GameManager)->OnGameOverHudActivity += [this](bool isActive)
			{
				this->SetIsActivity(isActive);
			});
	}
}

GameOverHud::~GameOverHud()
{
	_levelConn.Disconnect();
	_killConn.Disconnect();
	_coinConn.Disconnect();
	_timeConn.Disconnect();
}

void GameOverHud::Init()
{
	Super::Init();

	
}

void GameOverHud::Update()
{
	Super::Update();
	
	
}

void GameOverHud::Render(HDC hdc)
{
	Super::Render(hdc);
	


	//Utils::DrawTextFont(
	//	hdc,
	//	{400.f,305.f},
	//	L"Lv.00",
	//	//_levelText,
	//	30,
	//	RGB(255, 255, 255),
	//	L"맑은 고딕",
	//	100, 50
	//);


	//Utils::DrawTextFont(
	//	hdc,
	//	{ 450.f,290.f },
	//	L"K.00",
	//	//_killText,
	//	32,
	//	RGB(255, 255, 255),
	//	L"맑은 고딕",
	//	100, 50
	//);

	//Utils::DrawTextFont(
	//	hdc,
	//	{ 450.f,330.f },
	//	L"C.00",
	//	//_coinText,
	//	32,
	//	RGB(255, 255, 255),
	//	L"맑은 고딕",
	//	100, 50
	//);

	//Utils::DrawTextFont(
	//	hdc,
	//	{ 400.f,20.f },
	//	L"Stage",
	//	18,
	//	RGB(255, 255, 255),
	//	L"맑은 고딕",
	//	50, 50
	//);
	//Utils::DrawTextFont(
	//	hdc,
	//	{ 400.f,32.f },
	//	L"00:00",
	//	//_timeText,
	//	32,
	//	RGB(255, 255, 255),
	//	L"맑은 고딕",
	//	100, 50
	//);
	
}

wstring GameOverHud::FormatTimeMMSS(int totalTime)
{
	int minutes = totalTime / 60;
	int seconds = totalTime % 60;

	return format(L"{0}:{1} ", minutes, seconds);
}