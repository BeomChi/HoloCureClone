#pragma once
#include "Singleton.h"
class Scene;

class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;
public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void Clear();

	void ChangeScnee(SceneType sceneType);
	Scene* GetCurrentScene() { return _scene; }

	Vec2 GetCameraPos() { return _cameraPos; }
	void SetCameraPos(Vec2 pos) { _cameraPos = pos; }

	Vec2 WorldToScreen(Vec2 pos);
	Vec2 ScreenToWorld(Vec2 pos);

private:
	Scene* _scene = nullptr;
	SceneType _sceneType = SceneType::None;

	Vec2 _cameraPos = {};
};

