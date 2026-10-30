#include "pch.h"
#include "Component.h"
#include "03.Object/GameObject.h"

Component::Component(ComponentType type) : _type(type)
{
}

Component::~Component()
{
	_gameObject = nullptr;
}

GameObject* Component::GetGameObject()
{
	return _gameObject;
}

Transform* Component::GetTransform()
{
	return _gameObject->GetTransform();
}
