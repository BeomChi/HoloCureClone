#include "pch.h"
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

			// 몬스터끼리 충돌 무시
			if (src->GetOwner()->GetEntityType() == EntityType::Monster
				&& dest->GetOwner()->GetEntityType() == EntityType::Monster)
				continue;

			// 비활성 상태이면 충돌 무시
			if (!src->GetOwner()->GetIsActivity() || !dest->GetOwner()->GetIsActivity())
				continue;


			// 충돌 체크
			if (src->CheckCollision(dest))
			{

				// 처음으로 충돌하면
				if (src->GetCollisionMap().contains(dest) == false)
				{
					src->GetOwner()->OnTriggerEnter(src, dest);
					dest->GetOwner()->OnTriggerEnter(dest, src);
					
					src->GetCollisionMap().insert(dest);
					dest->GetCollisionMap().insert(src);
				}
				// 충돌 중일경우
				else if (src->GetCollisionMap().contains(dest) == true)
				{
					src->GetOwner()->OnTriggerStay(src, dest);
					dest->GetOwner()->OnTriggerStay(dest, src);
				}
			}
			else
			{
				// 충돌하다가 범위 밖으로 나간 경우
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

// 매니저 콜라이더 추가
void CollisionManager::AddCollider(Collider* collider)
{
	if (collider == nullptr)
		return;

	_colliders.push_back(collider);
}

// 매니저에서 콜라이더 제거
void CollisionManager::RemoveCollider(Collider* collider)
{
	auto it = find(_colliders.begin(), _colliders.end(), collider);

	if (it == _colliders.end())
		return;

	_colliders.erase(it);
}

// 원래는 사용했지만 게임오브젝트에서 컴포넌트를 일괄적으로 관리를 해서 지금은 사용안함 
// 언제 다시 사용할지 모르니 남겨놓은 상황
void CollisionManager::Clear()
{
	//for_each(_colliders.begin(), _colliders.end(), [](Collider* col) {SAFE_DELETE(col); });
		
	//for (auto collider : _colliders)
	//	SAFE_DELETE(collider);
		
	//_colliders.clear();
}
