#include "pch.h"
#include "Scene.h"
#include "../01.Manager/CollisionManager.h"
#include "../01.Manager/GameManager.h"
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
	for (int i = 0; i < LAYER_MAXCOUNT; ++i)
	{
		if (!CheckGameStateInLayer(i))
			continue;

		for (GameObject* obj : _objects[i])
		{
			if (!obj->GetIsActivity())
			{
				GET_SINGLE(ObjectPool)->ReturnObject(obj->GetKey(), obj);
				RemoveObject(obj);
			}
		}


		// 임시 보관소에 있던 오브젝트들을 추가
		_objects[i].insert(_objects[i].end(),
			_pendingObjects[i].begin(), _pendingObjects[i].end());

		_pendingObjects[i].clear();

		for (GameObject* obj : _objects[i])
		{
			if (obj == nullptr)
				continue;

			//wcout << "[DEBUG] Update 호출. this: " << obj->GetKey() << endl;
			if (!obj->GetIsActivity())
				continue;

			obj->Update();
		}
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
	auto& v = _objects[object->GetLayer()];

	auto it = find(v.begin(), v.end(), object);

	if (it == v.end())
		return;

	v.erase(it);
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
	if (GET_SINGLE(GameManager)->GetState() == GameState::Playing)
		return true;

	return layer == LAYER_UI;
}
