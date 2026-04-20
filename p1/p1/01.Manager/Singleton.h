#pragma once

template <typename T>
class Singleton
{
public:

	static void CreateInstance()
	{
		if (_instance == nullptr)
			_instance = new T();
	}

	static void DestroyInstance()
	{
		if (_instance != nullptr)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

	static T* GetInstance()
	{
		if (_instance == nullptr)
		{
			CreateInstance();
		}
		return _instance;
	}
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

protected:
	Singleton() {};
	virtual ~Singleton() {};

private:
	static T* _instance;
};

template <typename T>
T* Singleton<T>::_instance = nullptr;