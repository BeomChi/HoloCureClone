#include "pch.h"
#include "PlayerHudPanel.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/StageManager.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../05.Resource/2D/Sprite.h"
#include "../../06.Ui/Image.h"
#include "../../06.Ui/Game/HpBar.h"



// 무조건 플레이어 생성된 이후 만들긴
PlayerHudPanel::PlayerHudPanel()
{
	cout << "[DEBUG] PlayerHudPanel 생성됨" << endl;

	// Ui 매니저 만들면 거기서 가져오는 걸로
	auto _info = GET_SINGLE(GameManager)->GetPlayer()->GetInfo();
	{
		// 밑 이미지
		HpBar* hpBar = new HpBar();

		hpBar->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PlayerHpBarRed"));

		hpBar->SetSize({ (float)hpBar->GetSprite()->GetSize().x, (float)hpBar->GetSprite()->GetSize().y });
		hpBar->SetPos({ 70, 24 });
		hpBar->SetBarLength((float)hpBar->GetSprite()->GetSize().x);
		hpBar->SetValue((float)_info._currentHp, (float)_info._maxHp);

		hpBar->SetLayer(LAYER_UI);

		AddPanel(hpBar);
	}
	{
		// 실제 체력바
		_hpBar = new HpBar();

		_hpBar->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PlayerHpBarGreen"));

		_hpBar->SetSize({ (float)_hpBar->GetSprite()->GetSize().x, (float)_hpBar->GetSprite()->GetSize().y });
		_hpBar->SetPos({ 70, 24 });
		_hpBar->SetBarLength((float)_hpBar->GetSprite()->GetSize().x);
		_hpBar->SetValue((float)_info._currentHp, (float)_info._maxHp);
		_hpBar->SetLayer(LAYER_UI);

		auto* player = GET_SINGLE(GameManager)->GetPlayer();
		cout << "[DEBUG] PlayerHudPanel - Player 주소: " << player << endl;
		cout << "[DEBUG] PlayerHudPanel - OnHpChanged 주소: " << &(player->OnHpChanged) << endl;
		_hpConn = GET_SINGLE(GameManager)->GetPlayer()->OnHpChanged +=
			[this](float current, float max)
			{
				cout << "[DEBUG] OnHpChanged 호출됨: " << current << "/" << max << endl;
				if (_hpBar)
					_hpBar->SetValue(current, max);
				_hpText = format(L"{0}/{1}", current, max);

			};

		_hpText = format(L"{0}/{1}", player->GetInfo()._currentHp, player->GetInfo()._maxHp);
		/*Player* player = GET_SINGLE(GameManager)->GetPlayer();
		if (player == nullptr)
			cout << "플레이어 없음" << endl;

		_hpConn = move(GET_SINGLE(GameManager)->GetPlayer()->OnHpChanged += [this](float current, float max)
			{
				_hpBar->SetValue(current, max);
			});*/

		AddPanel(_hpBar);
        
	}
	{
		Image* hud = new Image();

		hud->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"PlayerHUD1"));

		hud->SetSize({ (float)hud->GetSprite()->GetSize().x, (float)hud->GetSprite()->GetSize().y });
		hud->SetPos({ (float)hud->GetSprite()->GetSize().x * 0.5f,50 });

		hud->SetLayer(LAYER_UI);

		AddPanel(hud);
	}
	{
		Image* Icon = new Image();

		Icon->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"GuraIcon"));

		Icon->SetSize({ (float)Icon->GetSprite()->GetSize().x, (float)Icon->GetSprite()->GetSize().y });
		Icon->SetPos({ (float)Icon->GetSprite()->GetSize().x * 0.5f,39 });

		Icon->SetLayer(LAYER_UI);

		AddPanel(Icon);
	}
	{
		// 경험치 바 배경
		Image* ExpBarBg = new Image();

		ExpBarBg->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"ExpBarBG"));

		ExpBarBg->SetSize({ (float)ExpBarBg->GetSprite()->GetSize().x, (float)ExpBarBg->GetSprite()->GetSize().y });
		ExpBarBg->SetScale({ 1.248f,1 });
		ExpBarBg->SetPos({ (float)ExpBarBg->GetSprite()->GetSize().x * 0.5f,(float)ExpBarBg->GetSprite()->GetSize().y * 0.5f });

		ExpBarBg->SetLayer(LAYER_UI);
		AddPanel(ExpBarBg);
	}
	{
		//경험치 바 이미지
		_expBar = new HpBar();

		_expBar->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"ExpBarFull"));

		_expBar->SetSize({ (float)_expBar->GetSprite()->GetSize().x, (float)_expBar->GetSprite()->GetSize().y });
		_expBar->SetScale({ 1.248f,1 });
		_expBar->SetPos({ 0, 13 });
		_expBar->SetBarLength((float)_expBar->GetSprite()->GetSize().x * 1.248f);
		_expBar->SetValue((float)_info._exp, (float)_info._maxExp);

		_expConn = move(GET_SINGLE(GameManager)->GetPlayer()->OnExpChanged += [this](float current, float max)
			{
				_expBar->SetValue(current, max);
			});
		_expBar->SetLayer(LAYER_UI);

		AddPanel(_expBar);
	}
	{
		// 경험치 바 프레임
		Image* ExpBarFrame = new Image();

		ExpBarFrame->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"ExpBarFrame"));

		ExpBarFrame->SetSize({ (float)ExpBarFrame->GetSprite()->GetSize().x, (float)ExpBarFrame->GetSprite()->GetSize().y });
		ExpBarFrame->SetScale({ 1.248f,1 });
		ExpBarFrame->SetPos({ (float)ExpBarFrame->GetSprite()->GetSize().x * 0.5f,(float)ExpBarFrame->GetSprite()->GetSize().y * 0.5f });

		ExpBarFrame->SetLayer(LAYER_UI);
		AddPanel(ExpBarFrame);
	}
	{
		_levelText = format(L"Lv.{0}", 1);
		_levelConn = move(GET_SINGLE(GameManager)->GetPlayer()->OnLevelChanged += [this](int32 arg)
			{
				_levelText = format(L"Lv.{0}", arg);
			});
	}
	{
		Image* Coin = new Image();

		Coin->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"Coin"));

		Coin->SetSize({ (float)Coin->GetSprite()->GetSize().x, (float)Coin->GetSprite()->GetSize().y });
		Coin->SetScale({ 1.5f,1.5f });
		Coin->SetPos({ 675.f, 50.f });
		Coin->SetLayer(LAYER_UI);
		AddPanel(Coin);
	}
	{
		Image* KillCountUi = new Image();

		KillCountUi->SetSprite(GET_SINGLE(ResourceManager)->GetSprite(L"KillCount"));

		KillCountUi->SetSize({ (float)KillCountUi->GetSprite()->GetSize().x, (float)KillCountUi->GetSprite()->GetSize().y });
		KillCountUi->SetScale({ 1.5f,1.5f });
		KillCountUi->SetPos({ 675.f, 90.f });
		KillCountUi->SetLayer(LAYER_UI);
		AddPanel(KillCountUi);
	}
	{
		_killText = format(L"{0}", 0);
		_killConn = move(GET_SINGLE(StageManager)->OnKillCountChanged += [this](int32 arg)
			{
				_killText = format(L"Lv.{0}", arg);
			});
	}
	{
		_coinText = format(L"{0}", 0);
		_coinConn = move(GET_SINGLE(StageManager)->OnCoinCountChanged += [this](int32 arg)
			{
				_coinText = format(L"{0}", arg);
			});
	}
	{
		_timeText = format(L"{0}:{1}", 0, 0);
		_timeConn = move(GET_SINGLE(StageManager)->OnTimeChanged += [this](int32 arg)
			{
				_timeText = FormatTimeMMSS(arg);
			});
	}
}

PlayerHudPanel::~PlayerHudPanel()
{
	_hpConn.Disconnect();     // 먼저 안전 해제
	_expConn.Disconnect();
	_levelConn.Disconnect();
	_killConn.Disconnect();
	_coinConn.Disconnect();
	_timeConn.Disconnect();
}

void PlayerHudPanel::Init()
{
	Super::Init();

	
}

void PlayerHudPanel::Update()
{
	Super::Update();
	
	
}

void PlayerHudPanel::Render(HDC hdc)
{
	Super::Render(hdc);
	


	Utils::DrawTextFont(
		hdc,
		{745.f,-5.f},
		_levelText,
		30,
		RGB(255, 255, 255),
		L"맑은 고딕",
		100, 50
	);

	Utils::DrawTextFont(
		hdc,
		{ 210.f,18.f },
		_hpText,
		16,
		RGB(255, 255, 255),
		L"맑은 고딕",
		100, 50
	);

	Utils::DrawTextFont(
		hdc,
		{ 700.f,35.f },
		_killText,
		32,
		RGB(255, 255, 255),
		L"맑은 고딕",
		100, 50
	);

	Utils::DrawTextFont(
		hdc,
		{ 700.f,75.f },
		_coinText,
		32,
		RGB(255, 255, 255),
		L"맑은 고딕",
		100, 50
	);

	Utils::DrawTextFont(
		hdc,
		{ 400.f,20.f },
		L"Stage",
		18,
		RGB(255, 255, 255),
		L"맑은 고딕",
		50, 50
	);
	Utils::DrawTextFont(
		hdc,
		{ 400.f,32.f },
		_timeText,
		32,
		RGB(255, 255, 255),
		L"맑은 고딕",
		100, 50
	);
	
}

wstring PlayerHudPanel::FormatTimeMMSS(int totalTime)
{
	int minutes = totalTime / 60;
	int seconds = totalTime % 60;

	return format(L"{0}:{1} ", minutes, seconds);
}



