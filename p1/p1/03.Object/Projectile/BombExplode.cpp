#include "pch.h"
#include "BombExplode.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "97.Engin/Component/Animation/Animator.h"
#include "97.Engin/Resource/Animation.h"

BombExplode::BombExplode()
{
}

BombExplode::~BombExplode()
{
}

void BombExplode::Init()
{
	

	// component
	{
		{
			_animation = RESOURCE->Get<Animation>(L"BombExplode");

			_ani = new Animator();
			_ani->SetAnimation(_animation);

			//Vec2Int size = _ani->Get<Animation>()->GetInfo().size;
			//SetSize({ (float)size.x , (float)size.y });


			AddComponent(_ani);
		}
		// collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize(_ani->GetCurrentAnimation()->GetKeyframe(0).size);
			collider->SetShowDebug(false);
			AddComponent(collider);
			//SetCollider(collider);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
		}

	}

	Super::Init();
}

void BombExplode::Update()
{
	Super::Update();
	

	if (_ani->GetCurrentAinmationEndIndex())
	{
		_isActivity = false;
	}
}

void BombExplode::Render(HDC hdc)
{
	Super::Render(hdc);
	
}


void BombExplode::OnTriggerEnter(Collider* collider, Collider* other)
{
	if (other->GetGameObject()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetGameObject())->TakeDamage(_damageInfo);
		//cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
	}
}


void BombExplode::Reset()
{

	_ani->Reset();
	GetCollider()->ClearCollisionMap();
	//_collider->ClearCollisionMap();
}
