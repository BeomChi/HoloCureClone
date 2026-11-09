#include "pch.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "../02.Scene/Game/DevScene.h"
#include "../02.Scene/Game/StartScene.h"
#include "../02.Scene/Game/EditScene.h"
#include "../03.Object/GameObject.h"
#include "97.Engin/Component/Camera/Camera.h"

SceneManager::SceneManager(Graphics* graphics) :_graphics(graphics)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
}

void SceneManager::Update()
{
	
	if (_scene)
		_scene->Update();

	// 씬 전환을 예약으로 변경으로 인해, 매 프레임마다 씬 전환이 필요한지 체크를
	// 업데이트가 끝난 뒤로 옮김
	if (_sceneType != _nextSceneType)
		ChangeScene(_nextSceneType);
}

void SceneManager::Render(HDC hdc)
{
	if (_scene)
		_scene->Render(hdc);

	//// 현재 카메라 좌표
	//{
	//	wstring str = std::format(L"카메라 위치({0}, {1})", _cameraPos.x, _cameraPos.y);
	//	::TextOut(hdc, GWinSizeX / 2, 50, str.c_str(), static_cast<int32>(str.size()));
	//}

}

void SceneManager::Clear()
{
	SAFE_DELETE(_scene);
}

void SceneManager::ChangeScene(SceneType sceneType)
{
	if (_sceneType == sceneType)
		return;

	Scene* newScene = nullptr;

	switch (sceneType)
	{
	case SceneType::DevScene:
		newScene = new DevScene();
		break;
	case SceneType::GameScene:
		break;
	case SceneType::StartScene:
		newScene = new StartScene();
		break;
	case SceneType::EditScene:
		newScene = new EditScene();
		break;
	}

	SAFE_DELETE(_scene);
	_scene = newScene;
	_sceneType = sceneType;
	_nextSceneType = _sceneType;

	newScene->Init();
}

Vec3 SceneManager::WorldToScreen(Vec2 pos)
{
	Vec3 worldPos = { pos.x, pos.y, 0 };

	Vec4 clipPos = Vec4::Transform(
		Vec4(worldPos.x, worldPos.y, worldPos.z, 1.0f),
		Camera::s_matView * Camera::s_matProjection
	);

	float ndcX = clipPos.x / clipPos.w;
	float ndcY = clipPos.y / clipPos.w;
	float screenX = (ndcX + 1.0f) * 0.5f * GWinSizeX;
	float screenY = (1.0f - ndcY) * 0.5f * GWinSizeY;

	return { screenX, screenY, 0 };
}

Vec3 SceneManager::ScreenToWorld(Vec2 screenPos)
{
	//return pos + _cameraPos - Vector(GWinSizeX / 2, GWinSizeY / 2);
	Vec3 worldPos = {};

	// 화면 좌표 -> NDC
	// -1 ~ 1 범위로 바꾸기 위해
	float ndcX = (screenPos.x / GWinSizeX) * 2.0f - 1.0f;
	float ndcY = 1.0f - (screenPos.y / GWinSizeY) * 2.0f;

	// 역 View * Projection 변환
	Matrix invViewProjection =
		(Camera::s_matView * Camera::s_matProjection).Invert();

	Vec3 ndcPos = { ndcX, ndcY, 0.0f };

	Vec3::Transform(ndcPos, invViewProjection);

	return ndcPos;
}

void SceneManager::GoToTitle()
{
	GAMEMANAGER->SetState(GameState::Title);
	SetNextSceneType(SceneType::StartScene);
}
