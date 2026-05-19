#include "pch.h"
#include "Axe.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../05.Resource/2D/Animator.h"

Axe::Axe()
{
}

Axe::~Axe()
{
}

void Axe::Init()
{

	// component
	{
		{
			_animation = GET_SINGLE(ResourceManager)->GetAnimator(L"PsychoAxe");
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
			//collider->SetShowDebug(true);
			AddComponent(collider);
			SetCollider(collider);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
		}
		
	}
	Super::Init();
}

void Axe::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_info._sumTime += deltaTime;

	
	float angle = _angle - _info._sumTime * _angularSpeed;
	float radius = _baseRadius + _info._sumTime * _radiusGrowth;

	Vec2 center = _startPos; // 시작 위치

	Vec2 offset = 
	{
		cosf(angle) * radius,
		sinf(angle) * radius
	};

	SetPos(center + offset);
	
	if (_info._sumTime >= _info._duration)
	{
		SetIsActivity(false);
	}
	

}

void Axe::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Axe::OnTriggerEnter(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
		//cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
	}
}



void Axe::Reset()
{
	_info._sumTime = 0;

	Vec2 _startPos = {};
	_ani->Reset();
}


