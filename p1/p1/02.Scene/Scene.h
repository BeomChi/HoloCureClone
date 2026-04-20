#pragma once
#include "../03.Object/ObjectFactory.h"

class GameObject;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	template<typename T>
	T* CreateAddGameObject();

	void RemoveObject(GameObject* object);
	void AddObject(GameObject* object);
	void Clear();

	const vector<GameObject*>& GetGameObjects(int layer) const { return _objects[layer]; }

private:
	vector<GameObject*> _objects[LAYER_MAXCOUNT];
	vector<GameObject*> _pendingObjects[LAYER_MAXCOUNT];
	ObjectFactory _factory;
};

template<typename T>
inline T* Scene::CreateAddGameObject()
{
	T* obj = _factory.CreateObject<T>();
	_pendingObjects[obj->GetLayer()].push_back(obj); // Fix: Access the correct layer in _pendingObjects array.  

	return obj;
}