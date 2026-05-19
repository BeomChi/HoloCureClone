#include "pch.h"
#include "FanBeamObj.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../05.Resource/2D/Animator.h"
#include "../../05.Resource/2D/Texture.h"

FanBeamObj::FanBeamObj()
{
}

FanBeamObj::~FanBeamObj()
{
}

void FanBeamObj::Init()
{


	// component
	{
		{
			// 좌우 애니메이션 설정
			_dirAni[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"FanBeamLeft");
			_dirAni[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"FanBeamRight");

			_ani = new AnimationComponent();
			_ani->SetAnimation(_dirAni[DIR_RIGHT]);

			// 크기를 애니메이션 크기에 맞춰서 설정 SetSize 함수 안에 RenderSize도 같이 설정해줌
			Vec2Int size = _ani->GetAnimator()->GetInfo().size;
			SetSize({ (float)size.x , (float)size.y });


			AddComponent(_ani);
		}
		// collider
		{
			// 콜라이더
			// 콜라이터 크기를 렌더 사이즈 맞춰서 설정해줌
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

void FanBeamObj::Update()
{
	Super::Update();

	// 애니메이션이 끝부분에 도달시 비활성화
	if (_ani->CheckCurrentAnimationEnd())
	{
		_isActivity = false;
	}
}

void FanBeamObj::Render(HDC hdc)
{
	Super::Render(hdc);

	//Utils::DrawCircle(hdc, _pos, _size);
}

void FanBeamObj::OnTriggerEnter(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
		//cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
		_collsion.push_back(other);
	}
}

void FanBeamObj::OnTriggerStay(Collider* collider, Collider* other)
{
}

void FanBeamObj::OnTriggerExit(Collider* collider, Collider* other)
{
}

void FanBeamObj::Reset()
{
	_ani->Reset();
	
	_collider->ClearCollisionMap();
	_collsion.clear();
}


// 상태 설정(여기서는 좌,우 방향)
void FanBeamObj::SetState(DirState dir)
{
	if (_dir == dir)
		return;

	_dir = dir;
	UpdateAnimation();
}


// 상태에 따라 애니메이션 업데이트
void FanBeamObj::UpdateAnimation()
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
