#pragma once
#include "../Panel.h"
#include "Signal.hpp"

class Text;
class Button;

class GameOverHud : public Panel
{
	using Super = Panel;
public:
	GameOverHud();
	virtual ~GameOverHud() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	wstring FormatTimeMMSS(int totalTime);
private:
	Connection _ActivityConn;
	Connection _levelConn;
	Connection _killConn;
	Connection _coinConn;
	Connection _timeConn;

	Text* _levelText;
	Text* _killText;
	Text* _coinText;
	Text* _timeText;
	Text* _titleText;

	Button* _titleButton;
};

