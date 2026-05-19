#include "pch.h"
#include "BLBookObj.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/SpriteRenderer.h"
#include "../../05.Resource/2D/Sprite.h"

BLBookObj::BLBookObj()
{
}

BLBookObj::~BLBookObj()
{
}

void BLBookObj::Init()
{
	// component
	{
		{
			Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"BLBook");
			SpriteRenderer* renderer = new SpriteRenderer();
			renderer->SetSprite(sprite);
			SetSize({ (float)sprite->GetSize().x, (float)sprite->GetSize().y });


			AddComponent(renderer);
		}
		// collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize(_renderSize);
			collider->SetShowDebug(false);

			AddComponent(collider);
			SetCollider(collider);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
		}
		
	}
	Super::Init();
}

void BLBookObj::Update()
{
	Super::Update();

	//float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	 
	//_sumTime += deltaTime;

	//if (_sumTime >= _info._duration)
	{
		//SetIsActivity(false);
	}
}

void BLBookObj::Render(HDC hdc)
{
	Super::Render(hdc);
}

void BLBookObj::OnTriggerEnter(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
		//cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;

	}
}

void BLBookObj::OnTriggerExit(Collider* collider, Collider* other)
{
}

void BLBookObj::Reset()
{
	_info._sumTime = 0.f;
}
