#include "pch.h"
#include "BombExplode.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../05.Resource/2D/Animator.h"

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
			_animation = GET_SINGLE(ResourceManager)->GetAnimator(L"BombExplode");

			_ani = new AnimationComponent();
			_ani->SetAnimation(_animation);

			Vec2Int size = _ani->GetAnimator()->GetInfo().size;
			SetSize({ (float)size.x , (float)size.y });


			AddComponent(_ani);
		}
		// collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize(_renderSize);
			collider->SetShowDebug(true);
			AddComponent(collider);
			SetCollider(collider);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
		}

	}

	Super::Init();
}

void BombExplode::Update()
{
	Super::Update();
	

	if (_ani->CheckCurrentAnimationEnd())
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
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetOwner())->TakeDamage(_info._dmg);
		cout << "데미지 들어감 : " << _info._dmg << endl;
	}
}

void BombExplode::OnTriggerStay(Collider* collider, Collider* other)
{
	
}

void BombExplode::OnTriggerExit(Collider* collider, Collider* other)
{
}

void BombExplode::Reset()
{
	_info._dmg = 0;
	_ani->Reset();

	_collider->ClearCollisionMap();
}
