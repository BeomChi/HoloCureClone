#include "pch.h"
#include "StickExplode.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../05.Resource/2D/Animator.h"

StickExplode::StickExplode()
{
}

StickExplode::~StickExplode()
{
}

void StickExplode::Init()
{
	// component
	{
		{
			_animation = GET_SINGLE(ResourceManager)->GetAnimator(L"StickExplode");
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
			collider->SetShowDebug(false);

			AddComponent(collider);
			SetCollider(collider);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
		}
		
	}

	SetLayer(LAYER_AREAATTACK);
	Super::Init();
}

void StickExplode::Update()
{
	Super::Update();

	if (_ani->CheckCurrentAnimationEnd())
	{
		_isActivity = false;
	}
}

void StickExplode::Render(HDC hdc)
{
	Super::Render(hdc);
}

void StickExplode::OnTriggerEnter(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
		cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
	}
}



void StickExplode::Reset()
{
	_ani->Reset();

	_collider->ClearCollisionMap();
}
