#include "pch.h"
#include "Lava.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../05.Resource/2D/Animator.h"

Lava::Lava()
{
}

Lava::~Lava()
{
}

void Lava::Init()
{
	_lava[START] = GET_SINGLE(ResourceManager)->GetAnimator(L"LavaStart");
	_lava[ATTACK] = GET_SINGLE(ResourceManager)->GetAnimator(L"LavaLoop");
	_lava[END] = GET_SINGLE(ResourceManager)->GetAnimator(L"LavaEnd");

	_ani = new AnimationComponent();
	_ani->SetAnimation(_lava[START]);

	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->SetShowDebug(false);
	SetCollider(boxCollider);

	GET_SINGLE(CollisionManager)->AddCollider(boxCollider);

	Vec2Int size = _ani->GetAnimator()->GetInfo().size;
	SetSize({ (float)size.x , (float)size.y });

	AddComponent(_ani);
	AddComponent(boxCollider);

	Super::Init();
}

void Lava::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	deltaTime = clamp(deltaTime, 0.0f, 0.1f);
	_sumTime += deltaTime;

	if (_state == LavaState::Start)
	{
		if (_ani->CheckCurrentAnimationEnd())
		{
			SetState(LavaState::Fire);
		}
	}

	if (_state == LavaState::Fire)
	{
		_info._time += deltaTime;

		if (_info._time >= _info._duration && _info._duration > 0)
		{
			SetState(LavaState::LaserStatEnd);
		}
	}

	if (_state == LavaState::LaserStatEnd && _ani->CheckCurrentAnimationEnd())
	{
		SetIsActivity(false);
	}


}

void Lava::Render(HDC hdc)
{
	Super::Render(hdc);
	//Utils::DrawRect(hdc, _pos, _size.x, _size.y);
}

void Lava::Activate(Vec2 pos, float duration)
{
	SetPos(pos);

	_info._duration = duration;
	_info._time = 0;
	_sumTime = 0;

	SetState(LavaState::Start);
	SetIsActivity(true);
}



void Lava::OnTriggerStay(Collider* collider, Collider* other)
{
	if (_state == LavaState::Start || _state == LavaState::LaserStatEnd)
		return;

	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		if (_sumTime >= _info._attackDelay)
		{
			static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
			cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
			_sumTime = 0;
		}
	}
}



void Lava::Reset()
{
	_info._time = 0;
	//_info._duration = 0;
	//_info._attackDelay = 0;
	_sumTime = 0;

	SetState(LavaState::Start);
}

void Lava::SetState(LavaState state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void Lava::UpdateAnimation()
{
	switch (_state)
	{
	case LavaState::Start:
		_ani->SetAnimation(_lava[START]);
		break;
	case LavaState::Fire:
		_ani->SetAnimation(_lava[ATTACK]);
		break;
	case LavaState::LaserStatEnd:
		_ani->SetAnimation(_lava[END]);
		break;
	}
}
