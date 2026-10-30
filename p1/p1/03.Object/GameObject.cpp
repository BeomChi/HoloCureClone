#include "pch.h"
#include "GameObject.h"
#include "97.Engin/Component/Component.h"
#include "97.Engin/Component/MonoBehaviour/MonoBehaviour.h"
#include "97.Engin/Component/Animation/Animator.h"
#include "97.Engin/Component/Camera/Camera.h"
#include "97.Engin/Component/Transform/Transform.h"
#include "97.Engin/Component/Renderer/MeshRenderer.h"
#include "../01.Manager/CollisionManager.h"
#include "../04.Component/Collision/Collider.h"
#include "../04.Component/Collision/BoxCollider.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	Clear();
}

void GameObject::Init()
{
	for (Component* component : _components)
	{
		if (component)
			component->Init();
	}

	for (MonoBehaviour* script : _scripts)
	{
		script->Init();
	}
}

void GameObject::Update()
{
	for (Component* component : _components)
	{
		if (component)
			component->Update();
	}

	for (MonoBehaviour* script : _scripts)
	{
		script->Update();
	}
}

void GameObject::Render(HDC hdc)
{
	for (Component* component : _components)
	{
		//component->Render(hdc);
	}
}

void GameObject::OnEnable()
{
}


void GameObject::RemoveComponent(Component* component)
{
	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = nullptr;
		SAFE_DELETE(component);
	}
	else
	{
		auto it = find(_scripts.begin(), _scripts.end(), component);

		if (it == _scripts.end())
			return;

		_scripts.erase(it);
	}

}

//void GameObject::SetSize(Vector size)
//{
//	_size = size;
//	_renderSize = _size * _scale;
//
//	if (_collider && _collider->GetColliderType() == ColliderType::Box)
//		static_cast<BoxCollider*>(_collider)->SetSize({ _renderSize.x , _renderSize.y });
//}
//
//void GameObject::SetScale(Vector scale)
//{
//	_scale = scale;
//	_renderSize = _size * _scale;
//
//	if (_collider && _collider->GetColliderType() == ColliderType::Box)
//		static_cast<BoxCollider*>(_collider)->SetSize({_renderSize.x , _renderSize.y});
//}

void GameObject::Reset()
{
}




void GameObject::OnTriggerEnter(Collider* collider, Collider* other)
{
	// 충돌할 때
}

void GameObject::OnTriggerStay(Collider* collider, Collider* other)
{
	// 충돌 중일 때
}

void GameObject::OnTriggerExit(Collider* collider, Collider* other)
{
	// 충돌이 끝났을 때
}



void GameObject::Clear()
{
	/*if (_collider)
	{
		GET_SINGLE(CollisionManager)->RemoveCollider(_collider);
		_collider = nullptr;
	}*/


	for_each(_components.begin(), _components.end(), [](Component* obj) {  SAFE_DELETE(obj); });
	for_each(_scripts.begin(), _scripts.end(), [](Component* obj) {  SAFE_DELETE(obj); });
	//_components.clear();
}


Component* GameObject::GetFixedComponent(ComponentType type)
{
	uint8 index = static_cast<uint8>(type);
	assert(index < FIXED_COMPONENT_COUNT);

	return _components[index];
}

Collider* GameObject::GetCollider()
{
	Component* component = GetFixedComponent(ComponentType::Collider);
	return static_cast<Collider*>(component);
}

Transform* GameObject::GetTransform()
{
	Component* component = GetFixedComponent(ComponentType::Transform);
	return static_cast<Transform*>(component);
}

Camera* GameObject::GetCamera()
{
	Component* component = GetFixedComponent(ComponentType::Camera);
	return static_cast<Camera*>(component);
}

MeshRenderer* GameObject::GetMeshRenderer()
{
	Component* component = GetFixedComponent(ComponentType::MeshRenderer);
	return static_cast<MeshRenderer*>(component);
}

Animator* GameObject::GetAnimator()
{
	Component* component = GetFixedComponent(ComponentType::Animator);
	return static_cast<Animator*>(component);
}


Transform* GameObject::GetOrAddTransform()
{
	if (GetTransform() == nullptr)
	{
		Transform* transform = new Transform();
		AddComponent(transform);
	}

	return GetTransform();
}

void GameObject::AddComponent(Component* component)
{
	component->SetGameObject(this);

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		_scripts.push_back(dynamic_cast<MonoBehaviour*>(component));
	}
}