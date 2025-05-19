#pragma once
#include "../Scene.h"

class Button;

class StartScene : public Scene
{
	using Super = Scene;
public:
	StartScene();
	virtual ~StartScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void GameStart();

private:
	Button* _ui = nullptr;
};
