#include "pch.h"
#include "GameObject.h"
#include "../04.Component/Component.h"
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
		component->Init();
	}
}

void GameObject::Update()
{

	for (Component* component : _components)
	{
		component->Update();
	}
}

void GameObject::Render(HDC hdc)
{
	for (Component* component : _components)
	{
		component->Render(hdc);
	}
}

void GameObject::OnEnable()
{
}

void GameObject::AddComponent(Component* component)
{
	component->SetOwner(this);
	_components.push_back(component);
}

void GameObject::RemoveComponent(Component* component)
{
	auto it = find(_components.begin(), _components.end(), component);

	if (it == _components.end())
		return;

	_components.erase(it);
}

void GameObject::SetSize(Vec2 size)
{
	_size = size;
	_renderSize = _size * _scale;

	if (_collider && _collider->GetColliderType() == ColliderType::Box)
		static_cast<BoxCollider*>(_collider)->SetSize({ _renderSize.x , _renderSize.y });
}

void GameObject::SetScale(Vec2 scale)
{
	_scale = scale;
	_renderSize = _size * _scale;

	if (_collider && _collider->GetColliderType() == ColliderType::Box)
		static_cast<BoxCollider*>(_collider)->SetSize({_renderSize.x , _renderSize.y});
}

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
	if (_collider)
	{
		GET_SINGLE(CollisionManager)->RemoveCollider(_collider);
		_collider = nullptr;
	}

	for_each(_components.begin(), _components.end(), [](Component* obj) {  delete obj; });
	_components.clear();
}
