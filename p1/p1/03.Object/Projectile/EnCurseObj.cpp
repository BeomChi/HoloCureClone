#include "pch.h"
#include "EnCurseObj.h"
#include "../../01.Manager/TimeManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../01.Manager/ObjectManager.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../05.Resource/2D/Animator.h"

EnCurseObj::EnCurseObj()
{
}

EnCurseObj::~EnCurseObj()
{
}

void EnCurseObj::Init()
{
	_info._speed = 500;

	// component
	{
		{
			_dirAni[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"EnCurseLeft");
			_dirAni[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"EnCurseRight");

			_ani = new AnimationComponent();
			_ani->SetAnimation(_dirAni[DIR_LEFT]);

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

void EnCurseObj::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();


	if (_dir == DirState::Right)
	{
		_pos.x += _info._speed * deltaTime;
	}
	else
	{
		_pos.x -= _info._speed * deltaTime;
	}
	
	Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(_pos);

	if (pos.x <= 0 || pos.y <= 0 ||
		pos.x >= GWinSizeX || pos.y >= GWinSizeY)
	{
		_isActivity = false;
	}
}

void EnCurseObj::Render(HDC hdc)
{
	Super::Render(hdc);

	//Utils::DrawCircle(hdc, _pos, _size);
}

void EnCurseObj::OnTriggerEnter(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetOwner())->TakeDamage(_info._dmg);
		_info._count++;

		if (_info._count >= 2)
			_isActivity = false;
	}
}

void EnCurseObj::OnTriggerExit(Collider* collider, Collider* other)
{
}

void EnCurseObj::Reset()
{
	_info._dmg = 0;
	_info._count = 0;
}

void EnCurseObj::SetState(DirState dir)
{
	if (_dir == dir)
		return;

	_dir = dir;
	UpdateAnimation();
}

void EnCurseObj::UpdateAnimation()
{
	switch (_dir)
	{
	case DirState::Left:
		_ani->SetAnimation(_dirAni[DIR_LEFT]);
		break;
	case DirState::Right:
		_ani->SetAnimation(_dirAni[DIR_RIGHT]);
		break;
	}
}
