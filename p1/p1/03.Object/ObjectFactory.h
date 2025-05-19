#pragma once
class ObjectFactory
{
public:
	template<typename T>
	T* CreateObject()
	{
		T* obj = new T();
		obj->Init();

		return obj;
	}
};

