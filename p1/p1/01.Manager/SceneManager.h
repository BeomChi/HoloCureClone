#pragma once
#include "Singleton.h"
class Scene;

class SceneManager //: public Singleton<SceneManager>
{
	//friend class Singleton<SceneManager>;
public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

	void ChangeScene(SceneType sceneType);
	Scene* GetCurrentScene() { return _scene; }

	Vector GetCameraPos() { return _cameraPos; }
	void SetCameraPos(Vector pos) { _cameraPos = pos; }

	Vector WorldToScreen(Vector pos);
	Vector ScreenToWorld(Vector pos);

	void SetNextSceneType(SceneType type) { _nextSceneType = type; }
	SceneType GetSceneType() { return _sceneType; }
	SceneType GetNextSceneType() { return _nextSceneType; }

	void GoToTitle();
private:
	Scene* _scene = nullptr;
	SceneType _sceneType = SceneType::None;
	SceneType _nextSceneType = SceneType::None;

	Vector _cameraPos = {};
};

