#pragma once
#include "../Scene.h"

class Button;
class GameObject;

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
	void StartEditMode();

private:
	Button* _ui = nullptr;
	vector<GameObject*> _uis;
};
