#pragma once
#include "Singleton.h"
#include "../03.Object/ObjectFactory.h"

class GameObject;


class ObjectManager : public Singleton<ObjectManager>
{
	friend class Singleton<ObjectManager>;
public:
	virtual ~ObjectManager() override;

	template<typename T>
	T* CreateAddGameObject();

	void UpdateAll();
	void RenderAll(HDC hdc);
	void Clear();

	void RemoveObject(GameObject* object);
	void AddObject(GameObject* object);

	const vector<GameObject*>& GetGameObjects(int layer) const { return _objects[layer]; }
	
private:
	vector<GameObject*> _objects[LAYER_MAXCOUNT];
	vector<GameObject*> _pendingObjects[LAYER_MAXCOUNT];

	ObjectFactory _factory;
};

template<typename T>  
inline T* ObjectManager::CreateAddGameObject()  
{  
   T* obj = _factory.CreateObject<T>();  
   _pendingObjects[obj->GetLayer()].push_back(obj); // Fix: Access the correct layer in _pendingObjects array.  

   return obj;  
}
