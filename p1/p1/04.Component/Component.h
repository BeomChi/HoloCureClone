#pragma once

class GameObject;

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetOwner(GameObject* owner) { _owner = owner; }
	GameObject* GetOwner() { return _owner; }

protected:
	GameObject* _owner;
};

