#pragma once
//#include "Scene.h"

class GameObject;
class Transform;

enum class ComponentType : uint8
{
	Transform,
	MeshRenderer,
	Camera,
	Animator,
	Collider,
	Sprite,
	SpriteRenderer,

	Script,
	End
};

enum
{
	FIXED_COMPONENT_COUNT = static_cast<uint8>(ComponentType::End) - 1
};

class Component
{
public:
	Component(ComponentType type);
	virtual ~Component();

	virtual void Init() {}
	virtual void Start() {}
	
	virtual void Update() {}
	virtual void LateUpdate() {}
	virtual void FixedUpdate() {}

	GameObject* GetGameObject();
	Transform* GetTransform();

	ComponentType GetType() { return _type; }

private:
	friend class GameObject;
	void SetGameObject(GameObject* gameObject) { _gameObject = gameObject; }

protected:
	ComponentType _type;
	GameObject* _gameObject;
};

