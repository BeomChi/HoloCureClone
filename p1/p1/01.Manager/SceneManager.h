#pragma once
//#include "Singleton.h"
class Scene;

class Graphics;

class SceneManager //: public Singleton<SceneManager>
{
	//friend class Singleton<SceneManager>;
public:
	SceneManager(Graphics* graphics);
	~SceneManager();

	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

	void ChangeScene(SceneType sceneType);
	Scene* GetCurrentScene() { return _scene; }

	Vector GetCameraPos() { return _cameraPos; }
	void SetCameraPos(Vector pos) { _cameraPos = pos; }

	Vec3 WorldToScreen(Vec2 pos);
	Vec3 ScreenToWorld(Vec2 screenPos);

	void SetNextSceneType(SceneType type) { _nextSceneType = type; }
	SceneType GetSceneType() { return _sceneType; }
	SceneType GetNextSceneType() { return _nextSceneType; }

	void GoToTitle();

	Graphics* GetGraphics() { return _graphics; }
private:

	Graphics* _graphics;

	Scene* _scene = nullptr;
	SceneType _sceneType = SceneType::None;
	SceneType _nextSceneType = SceneType::None;

	Vector _cameraPos = {};
};

