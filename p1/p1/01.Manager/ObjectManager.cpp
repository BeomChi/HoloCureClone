#include "../pch.h"
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

		for (GameObject* obj : toRemove[i])
			RemoveObject(obj);

		_objects[i].insert(_objects[i].end(),
			_pendingObjects[i].begin(), _pendingObjects[i].end());
		_pendingObjects[i].clear();
	}
}

void ObjectManager::RenderAll(HDC hdc)
{
	for (const vector<GameObject*>& gameObj : _objects)
		for (GameObject* obj : gameObj)
			obj->Render(hdc);

}

void ObjectManager::Clear()
{
	for(const vector<GameObject*>& gameObj : _objects)
		for (GameObject* obj : gameObj)
			SAFE_DELETE(obj);

	for (int i = 0; i < LAYER_MAXCOUNT; ++i)
		_objects[i].clear();
}

void ObjectManager::RemoveObject(GameObject* object)
{
	auto& v = _objects[object->GetLayer()];

	auto it = find(v.begin(), v.end(), object);

	if (it == v.end())
		return;

	v.erase(it);
}

void ObjectManager::AddObject(GameObject* object)
{
	_pendingObjects[object->GetLayer()].push_back(object);
	int a = 0;
}
