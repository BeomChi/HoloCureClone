#include "pch.h"
#include "ObjectManager.h"
#include "../03.Object/GameObject.h"
#include "../03.Object/ObjectPool/ObjectPool.h"

ObjectManager::~ObjectManager()
{

}

void ObjectManager::UpdateAll()
{
	vector<GameObject*> toRemove[LAYER_MAXCOUNT];

	for (int i = 0; i < LAYER_MAXCOUNT; ++i)
	{
		for (GameObject* obj : _objects[i])
			obj->Update();


		for (GameObject* obj : _objects[i])
		{
			if (!obj->GetIsActivity())
			{
				GET_SINGLE(ObjectPool)->ReturnObject(obj->GetKey(), obj);
				toRemove[i].push_back(obj);
			}
		}

		// 오브젝트 제거
		for (GameObject* obj : toRemove[i])
			RemoveObject(obj);

		// 임시 보관소에 있던 오브젝트들을 추가
		_objects[i].insert(_objects[i].end(),
			_pendingObjects[i].begin(), _pendingObjects[i].end());

		_pendingObjects[i].clear();
	}
}

// 전체 렌더
void ObjectManager::RenderAll(HDC hdc)
{
	for (const vector<GameObject*>& gameObj : _objects)
		for (GameObject* obj : gameObj)
			obj->Render(hdc);

}

// 오브젝트 전체 삭제
void ObjectManager::Clear()
{
	for(const vector<GameObject*>& gameObj : _objects)
		for (GameObject* obj : gameObj)
			SAFE_DELETE(obj);

	for (int i = 0; i < LAYER_MAXCOUNT; ++i)
		_objects[i].clear();
}

// 오브젝트 제거
void ObjectManager::RemoveObject(GameObject* object)
{
	auto& v = _objects[object->GetLayer()];

	auto it = find(v.begin(), v.end(), object);

	if (it == v.end())
		return;

	v.erase(it);
}

// 임시 저장소에 추가
void ObjectManager::AddObject(GameObject* object)
{
	_pendingObjects[object->GetLayer()].push_back(object);
}
