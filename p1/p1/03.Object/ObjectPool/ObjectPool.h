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

	bool CreateNewObject(wstring key);

	void Clear();
	void Debug();
private:
	ObjectFactory _factory;
	unordered_map<wstring,vector<GameObject*>> _objectPool;
	unordered_map<wstring, function<GameObject* ()>> _creators;
};

template<typename T>
inline T* ObjectPool::Get(wstring key)
{
	auto it = _objectPool.find(key);
	if (it == _objectPool.end())
		return nullptr;

	auto& pool = it->second;
	

	if (pool.empty())
	{
		if (!CreateNewObject(key))
			return nullptr;
	}
	if (pool.empty())
		return nullptr;

	static_assert(is_base_of_v<GameObject, T>, "T X GameObject");
	T* obj = static_cast<T*>(pool.back());
	pool.pop_back();

	//wcout << L"[GET] key = " << key << L" size after pop = " << pool.size() << endl;
	
	obj->SetIsActivity(true);

	return obj;
}

template<typename T>
inline void ObjectPool::ReturnObject(wstring key,T* obj)
{
	if (obj == nullptr)
		return;

	//wcout << L"[RET] key = " << key << endl;
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

