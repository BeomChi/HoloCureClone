#pragma once
#include "../Scene.h"

class Sound;
class Player;
class UiLayoutManager;

class DevScene : public Scene
{
	using Super = Scene;
public:
	DevScene();
	virtual ~DevScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	

private:
	Sound* sound = nullptr;
	bool _debug = false;
	Player* _player;
	UiLayoutManager* _uiLayoutManager;
};

