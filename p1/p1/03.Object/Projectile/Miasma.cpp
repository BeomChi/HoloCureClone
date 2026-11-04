#include "pch.h"
#include "Miasma.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../03.Object/Item/Equipment/Equipment.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/SpriteRenderer.h"
#include "97.Engin/Resource/Sprite.h"

Miasma::Miasma()
{
}

Miasma::~Miasma()
{
}

void Miasma::Init()
{
	// component
	{
		{
			Sprite* sprite = RESOURCE->Get<Sprite>(L"Miasma");
			SpriteRenderer* renderer = new SpriteRenderer();
			renderer->SetSprite(sprite);
			//SetSize({ (float)sprite->GetSize().x, (float)sprite->GetSize().y });


			AddComponent(renderer);
		}
		// collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize(renderer->GetSprite()->GetSize());
			collider->SetShowDebug(false);

			AddComponent(collider);
			//SetCollider(collider);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
		}
		
	}

	SetLayer(LAYER_AREAATTACK);
	Super::Init();
}

void Miasma::Update()
{
	Super::Update();

	_sumTime += TIME->GetDeltaTime();

	GetTransform()->SetPosition(GAMEMANAGER->GetPlayer()->GetTransform()->GetPosition());
}

void Miasma::Render(HDC hdc)
{
	Super::Render(hdc);
}



void Miasma::OnTriggerStay(Collider* collider, Collider* other)  
{  
   if (other->GetGameObject()->GetEntityType() == EntityType::Monster)  
   {  
	   if (other->GetGameObject()->GetEntityType() == EntityType::Monster)
	   {
		   auto it = _hitCooldownMap.find(other);

		   if (it == _hitCooldownMap.end())
		   {
			   static_cast<Entity*>(other->GetGameObject())->TakeDamage(_damageInfo);
			   _hitCooldownMap[other] = _sumTime;
		   }
		   else
		   {
			   if (_sumTime - it->second >= _info._attackDelay)
			   {
				   static_cast<Entity*>(other->GetGameObject())->TakeDamage(_damageInfo);
				   it->second = _sumTime;
			   }
		   }

	   }
   }  
}



void Miasma::Reset()
{

}
