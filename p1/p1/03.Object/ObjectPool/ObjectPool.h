#pragma once
#include "../../01.Manager/Singleton.h"
#include "../ObjectFactory.h"

class GameObject;


class ObjectPool : public Singleton<ObjectPool>
{
	friend class Singleton<ObjectPool>;
public:
	void Init();

	template<typename T>
	T* Get(wstring key);

	template<typename T>
	void ReturnObject(wstring key,T* obj);

	template<typename T>
	void ReigsterCreator(wstring key);

	void CreateNewObject(wstring key);

	void Clear();

private:
	ObjectFactory _factory;
	unordered_map<wstring,vector<GameObject*>> _objectPool;
	unordered_map<wstring, function<GameObject* ()>> _creators;
};

template<typename T>
inline T* ObjectPool::Get(wstring key)
{
	auto& pool = _objectPool[key];
	
	if (pool.empty())
	{
		CreateNewObject(key);
	}
	static_assert(std::is_base_of_v<GameObject, T>, "T X GameObject");

	T* obj = static_cast<T*>(pool.back());
	pool.pop_back();
	
	obj->SetIsActivity(true);

	return obj;
}

template<typename T>
inline void ObjectPool::ReturnObject(wstring key,T* obj)
{
	if (obj == nullptr)
		return;

	obj->Reset();
	_objectPool[key].push_back(obj);
}

template<typename T>
inline void ObjectPool::ReigsterCreator(wstring key)
{
	static_assert(std::is_base_of_v<GameObject, T>, "T X GameObject");

	

	_creators[key] = [this]() -> GameObject*
	{
		return _factory.CreateObject<T>();
	};
}

