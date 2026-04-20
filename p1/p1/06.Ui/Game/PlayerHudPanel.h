#pragma once
#include "../Panel.h"
#include "Signal.hpp"

class HpBar;

class PlayerHudPanel : public Panel
{
	using Super = Panel;
public:
	PlayerHudPanel();
	virtual ~PlayerHudPanel() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	wstring FormatTimeMMSS(int totalTime);
private:
	Connection _hpConn;
	Connection _expConn;
	Connection _levelConn;
	Connection _killConn;
	Connection _coinConn;
	Connection _timeConn;

	HpBar* _hpBar = nullptr; // 체력 바
	HpBar* _expBar = nullptr; // 체력 바

	wstring _levelText;
	wstring _hpText;
	wstring _killText;
	wstring _coinText;
	wstring _timeText;
};

