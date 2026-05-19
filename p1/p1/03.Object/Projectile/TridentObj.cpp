#include "pch.h"
#include "TridentObj.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../05.Resource/2D/Animator.h"
#include "../../05.Resource/2D/Texture.h"

TridentObj::TridentObj()
{
}

TridentObj::~TridentObj()
{
}

void TridentObj::Init()
{


	// component
	{
		{
			_dirAni[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"TridentLeft");
			_dirAni[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"TridentRight");

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

void TridentObj::Update()
{
	Super::Update();

	if (_ani != nullptr &&_ani->CheckCurrentAnimationEnd())
	{
		_isActivity = false;
	}
}

void TridentObj::Render(HDC hdc)
{
	Super::Render(hdc);

	//Utils::DrawCircle(hdc, _pos, _size);
}

void TridentObj::OnTriggerEnter(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
		//cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
	}
}



void TridentObj::Reset()
{
	_ani->Reset();
	
	_collider->ClearCollisionMap();
}

void TridentObj::SetState(DirState dir)
{
	if (_dir == dir)
		return;

	_dir = dir;
	UpdateAnimation();
}

void TridentObj::UpdateAnimation()
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
