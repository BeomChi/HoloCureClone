#include "pch.h"
#include "StickExplode.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "97.Engin/Component/Animation/Animator.h"
#include "97.Engin/Resource/Animation.h"

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
			_animation = RESOURCE->Get<Animation>(L"StickExplode");
			_ani = new Animator();
			_ani->SetAnimation(_animation);

			//Vec2Int size = _ani->GetAnimator()->GetInfo().size;
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

	SetLayer(LAYER_AREAATTACK);
	Super::Init();
}

void StickExplode::Update()
{
	Super::Update();

	if (_ani->GetCurrentAinmationEndIndex())
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
	if (other->GetGameObject()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetGameObject())->TakeDamage(_damageInfo);
		//cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
	}
}



void StickExplode::Reset()
{
	_ani->Reset();

	_collider->ClearCollisionMap();
}
