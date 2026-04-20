#include "pch.h"
#include "SausageObj.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../05.Resource/2D/Animator.h"
#include "../../05.Resource/2D/Texture.h"

SausageObj::SausageObj()
{
}

SausageObj::~SausageObj()
{
}

void SausageObj::Init()
{


	// component
	{
		{
			_dirAni[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"SausageLeft");
			_dirAni[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"SausageRight");

			_ani = new AnimationComponent();
			_ani->SetAnimation(_dirAni[DIR_RIGHT]);

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
	Super::Init();
}

void SausageObj::Update()
{
	Super::Update();

	if (_ani->CheckCurrentAnimationEnd())
	{
		_isActivity = false;
	}
}

void SausageObj::Render(HDC hdc)
{
	Super::Render(hdc);

	//Utils::DrawCircle(hdc, _pos, _size);
}

void SausageObj::OnTriggerEnter(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
		cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
	}
}



void SausageObj::Reset()
{
	_ani->Reset();
	
	_collider->ClearCollisionMap();
}

void SausageObj::SetState(DirState dir)
{
	if (_dir == dir)
		return;

	_dir = dir;
	UpdateAnimation();
}

void SausageObj::UpdateAnimation()
{
	switch (_dir)
	{
	case DirState::Left:
		_ani->GetAnimator()->GetInfo().texture->SetPivot({ 1,0.5f });
		_ani->SetAnimation(_dirAni[DIR_LEFT]);

		if (_collider)
			_collider->SetOffset({ -_renderSize.x * 0.5f, 0 });  // 왼쪽으로 이동
		break;
	case DirState::Right:
		_ani->GetAnimator()->GetInfo().texture->SetPivot({ 0,0.5f });
		_ani->SetAnimation(_dirAni[DIR_RIGHT]);

		if (_collider)
			_collider->SetOffset({ _renderSize.x * 0.5f, 0 });   // 오른쪽으로 이동
		break;
	}
}
