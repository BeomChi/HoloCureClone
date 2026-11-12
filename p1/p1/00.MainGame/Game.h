#pragma once

class SceneManager;
class TimeManager;
class InputManager;
class GameManager;
class ResourceManager;
class EquipmentManager;
class SoundManager;
class RenderManager;

class Game
{
public:
	Game();
	~Game();

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

public:
	SceneManager* GetSceneManager() { return _sceneManager; }
	TimeManager* GetTimeManager() { return _timeManager; }
	InputManager* GetInputManager() { return _inputManager; }
	GameManager* GetGameManager() { return _gameManager; }
	ResourceManager* GetResourceManager() { return _resourceManager; }
	EquipmentManager* GetEquipmentManager() { return _equipmentManager; }
	SoundManager* GetSoundManager() { return _soundManager; }
	RenderManager* GetRenderManager() { return _renderManager; }

	HDC GetHdcBack() { return hdcBack; }
	HDC GetHdc() { return hdc; }

private:
	HWND _hwnd = {};
	HDC hdc = {};
	uint32 _width = 0;
	uint32 _height = 0;

private:
	RECT _rect = {};
	HDC hdcBack = {};
		
	HBITMAP _bmpBack = {};

private:
	Graphics* _graphics;

private:
	SceneManager* _sceneManager;
	TimeManager* _timeManager;
	InputManager* _inputManager;
	GameManager* _gameManager;
	ResourceManager* _resourceManager;
	EquipmentManager* _equipmentManager;
	SoundManager* _soundManager;
	RenderManager* _renderManager;
};

extern Game* GGame;
