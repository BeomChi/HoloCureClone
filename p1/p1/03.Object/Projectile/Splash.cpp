#include "pch.h"
#include "Splash.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../05.Resource/2D/Animator.h"
#include "../../05.Resource/2D/Texture.h"

Splash::Splash()
{
}

Splash::~Splash()
{
}

void Splash::Init()
{


	// component
	{
		{
			_dirAni[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"SplashLeft");
			_dirAni[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"SplashRight");

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

void Splash::Update()
{
	Super::Update();

	if (_ani->CheckCurrentAnimationEnd())
	{
		_isActivity = false;
	}
}

void Splash::Render(HDC hdc)
{
	Super::Render(hdc);

	//Utils::DrawCircle(hdc, _pos, _size);
}

void Splash::OnTriggerEnter(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
		Knockback(collider->GetOwner(), other->GetOwner(), 800.f);
		////// 넉백을 추가해야함
		//Vec2 dir = other->GetOwner()->GetPos() - GET_SINGLE(GameManager)->GetPlayer()->GetPos();
		//dir.Normalize();

		//// 넉백 거리 만큼 dir을 곱해주고 거기에다가 객체의 위치를 더해서 위치를 설정하면 텔포가 되어버리는 데 음
		//if (dir.Length() == 0)
		//	dir = { 1,0 };
		//else
		//	dir.Normalize();

		//float knockPower = 800.f;
		//static_cast<Entity*>(other->GetOwner())->SetState(State::Stagger);
		//other->GetOwner()->AddVelocity(dir * knockPower);

		cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
	}
}


void Splash::Reset()
{
	_ani->Reset();
	
	_collider->ClearCollisionMap();
}

void Splash::SetState(DirState dir)
{
	if (_dir == dir)
		return;

	_dir = dir;
	UpdateAnimation();
}

void Splash::UpdateAnimation()
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
