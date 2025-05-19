#include "../pch.h"
#include "CollisionManager.h"
#include "../04.Component/Collision/Collider.h"
#include "../03.Object/GameObject.h"

CollisionManager::~CollisionManager()
{
	
}

void CollisionManager::Init()
{

}

void CollisionManager::Update()
{
	vector<Collider*>& col = _colliders;

	for (int32 i = 0; i < col.size(); i++)
	{
		for (int32 j = i + 1; j < col.size(); j++)
		{
			Collider* src = col[i];
			Collider* dest = col[j];

			if (src->CheckCollision(dest))
			{
				if (src->GetCollisionMap().contains(dest) == false)
				{
					src->GetOwner()->OnTriggerEnter(src, dest);
					dest->GetOwner()->OnTriggerEnter(dest, src);
					
					src->GetCollisionMap().insert(dest);
					dest->GetCollisionMap().insert(src);
				}
				else if (src->GetCollisionMap().contains(dest) == true)
				{
					src->GetOwner()->OnTriggerStay(src, dest);
					dest->GetOwner()->OnTriggerStay(dest, src);
				}
			}
			else
			{
				if (src->GetCollisionMap().contains(dest) == true)
				{
					src->GetOwner()->OnTriggerExit(src, dest);
					dest->GetOwner()->OnTriggerExit(dest, src);

					src->GetCollisionMap().erase(dest);
					dest->GetCollisionMap().erase(src);
				}
			}
		}
	}
}

void CollisionManager::AddCollider(Collider* collider)
{
	if (collider == nullptr)
		return;

	_colliders.push_back(collider);
}

void CollisionManager::RemoveCollider(Collider* collider)
{
	auto it = find(_colliders.begin(), _colliders.end(), collider);

	if (it == _colliders.end())
		return;

	_colliders.erase(it);
}

void CollisionManager::Clear()
{
	//for_each(_colliders.begin(), _colliders.end(), [](Collider* col) {SAFE_DELETE(col); });
		
	//for (auto collider : _colliders)
	//	SAFE_DELETE(collider);
		
	//_colliders.clear();
}
