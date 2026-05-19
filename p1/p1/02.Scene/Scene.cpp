#include "pch.h"
#include "Scene.h"
#include "../01.Manager/CollisionManager.h"
#include "../01.Manager/GameManager.h"
#include "../01.Manager/SceneManager.h"
#include "../03.Object/GameObject.h"
#include "../03.Object/ObjectPool/ObjectPool.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	Clear();
}

void Scene::Init()
{
	
}

void Scene::Update()
{
	// 풀링을 한 이유
	// 이미 죽은 오브젝트가 점점 쌓이면 쓸데없는 순회가 발생하기 때문에
	// 비활성화 된건 풀로 반환, ui는 예외적으로 업데이트와 렌더만 않하고 유지하도록 함
	// 왜냐하면 게임 상태와 상관없이 UI는 항상 업데이트되어야 하기 때문
	for (int i = 0; i < LAYER_MAXCOUNT; ++i)
	{
		// 임시 보관소에 있던 오브젝트들을 추가
		_objects[i].insert(_objects[i].end(),
			_pendingObjects[i].begin(), _pendingObjects[i].end());

		_pendingObjects[i].clear();

	}
		//for (GameObject* obj : _objects[i])
		//{
		//	if (obj == nullptr)
		//		continue;

		//	//wcout << "[DEBUG] Update 호출. this: " << obj->GetKey() << endl;
		//	if (!obj->GetIsActivity())
		//	{
		//		continue;
		//	}

		//	obj->Update();
		//}
		//cout << "_objects[i].size(): " << _objects[i].size() << endl;
		//for (GameObject* obj : _objects[i])
		//{
		//	if (obj == nullptr)
		//		continue;

		//	if (!obj->GetIsActivity())
		//	{
		//		RemoveObject(obj);
		//	}
		//}
	for (int i = 0; i < LAYER_MAXCOUNT; ++i)
	{
		if (!CheckGameStateInLayer(i))
			continue;

		for (int j = 0; j < _objects[i].size(); ++j)
		{
			GameObject* obj = _objects[i][j];

			if (obj == nullptr)
				continue;

			if (!obj->GetIsActivity())
			{
				// UI는 게임 상태와 상관없이 항상 업데이트되어야 하므로 예외 처리
				if (obj->GetLayer() != LAYER_UI)
					RemoveObject(obj); // pending에만 넣음

				continue;
			}

			obj->Update();
		}

	}

	for (int i = 0; i < LAYER_MAXCOUNT; ++i)
	{
		// 임시 제거 보관소에 있는 오브젝트들을 제거
		auto& v = _objects[i];
		for (GameObject* obj : _pendingRemoveObjects[i])
		{
			auto it = find(v.begin(), v.end(), obj);

			if (it != v.end())
			{
				GET_SINGLE(ObjectPool)->ReturnObject(obj->GetKey(), obj);
				v.erase(it);
			}
		}

		_pendingRemoveObjects[i].clear();
	}

	GET_SINGLE(CollisionManager)->Update();

}

void Scene::Render(HDC hdc)
{
	for (const vector<GameObject*>& gameObj : _objects)
		for (GameObject* obj : gameObj)
		{
			if (obj == nullptr)
				continue;

			if (!obj->GetIsActivity())
				continue;

			obj->Render(hdc);
		}
}

void Scene::RemoveObject(GameObject* object)
{
	if (object == nullptr)
		return;

	int layer = object->GetLayer();

	auto& pending = _pendingRemoveObjects[layer];

	// 중복제거 방지
	if (find(pending.begin(), pending.end(), object) != pending.end())
		return;

	pending.push_back(object);
}

void Scene::AddObject(GameObject* object)
{
	if (object == nullptr)
		return;

	LAYER_TYPE layer = object->GetLayer();

	
	// 이미 존재하는 오브젝트는 추가하지 않음
	auto& v = _objects[object->GetLayer()];
	auto it = find(v.begin(), v.end(), object);

	if (it != v.end())
		return;

	auto& pending = _pendingObjects[layer];

	if (find(pending.begin(), pending.end(), object) != pending.end())
		return;

	if (layer < 0 || layer >= LAYER_MAXCOUNT)
		return;

	_pendingObjects[layer].push_back(object);
}

void Scene::Clear()
{
	for (auto* obj : _objects[LAYER_UI])
		SAFE_DELETE(obj);

	_objects[LAYER_UI].clear();

	for (const vector<GameObject*>& gameObj : _objects)
		for (GameObject* obj : gameObj)
			SAFE_DELETE(obj);

	for (int i = 0; i < LAYER_MAXCOUNT; ++i)
		_objects[i].clear();

}

bool Scene::CheckGameStateInLayer(int layer)
{
	if (GET_SINGLE(GameManager)->GetState() == GameState::Playing || 
		GET_SINGLE(GameManager)->GetState() == GameState::Title)
		return true;

	return layer == LAYER_UI;
}
