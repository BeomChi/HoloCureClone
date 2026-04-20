#include "pch.h"
#include "Laser.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../05.Resource/2D/Animator.h"

Laser::Laser()
{

}

Laser::~Laser()
{

}

void Laser::Init()
{
	_laser[START] = GET_SINGLE(ResourceManager)->GetAnimator(L"FuburaLaserStart");
	_laser[ATTACK] = GET_SINGLE(ResourceManager)->GetAnimator(L"FuburaLaser");

	_ani = new AnimationComponent();
	_ani->SetAnimation(_laser[START]);

	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->SetShowDebug(false);
	SetCollider(boxCollider);

	GET_SINGLE(CollisionManager)->AddCollider(boxCollider);

	Vec2Int size = _ani->GetAnimator()->GetInfo().size;
	SetSize({ (float)size.x , (float)size.y});
	
	AddComponent(_ani);
	AddComponent(boxCollider);

	Super::Init();
}

void Laser::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_info._sumTime += deltaTime;
	_info._time += deltaTime;

	if (_info._time >= _info._duration)
		SetIsActivity(false);

	if (_ani->CheckCurrentAnimationEnd())
	{
		SetState(LaserState::Fire);
	}
}

void Laser::Render(HDC hdc)
{
	Super::Render(hdc);
	
}

void Laser::Activate(Vec2 pos, float duration)
{
	SetPos(pos);
	_info._duration = duration;
	_info._time = 0;
	SetState(LaserState::Start);

	SetIsActivity(true);
}


void Laser::OnTriggerStay(Collider* collider, Collider* other)
{
	if (_state == LaserState::Start)
		return;

	if (other->GetOwner()->GetEntityType() == EntityType::Player)
	{
		//_sumTime += GET_SINGLE(TimeManager)->GetDeltaTime();

		if (_info._sumTime >= 1.f)
		{
			static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
			cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
			_info._sumTime = 0;
		}
	}
}



void Laser::Reset()
{
}

void Laser::SetState(LaserState state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void Laser::UpdateAnimation()
{
	switch(_state)
	{
	case LaserState::Start:
		_ani->SetAnimation(_laser[START]);
		break;
	case LaserState::Fire:
		_ani->SetAnimation(_laser[ATTACK]);
		break;
	}
}
