#include "pch.h"
#include "Lava.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "97.Engin/Component/Animation/Animator.h"
#include "97.Engin/Resource/Animation.h"

Lava::Lava()
{
}

Lava::~Lava()
{
}

void Lava::Init()
{
	_lava[START] = RESOURCE->Get<Animation>(L"LavaStart");
	_lava[ATTACK] = RESOURCE->Get<Animation>(L"LavaLoop");
	_lava[END] = RESOURCE->Get<Animation>(L"LavaEnd");

	_ani = new Animator();
	_ani->SetAnimation(_lava[START]);

	BoxCollider* boxCollider = new BoxCollider();
	boxCollider->SetShowDebug(false);

	boxCollider->SetSize(_ani->GetCurrentAnimation()->GetKeyframe(0).size);
	//SetCollider(boxCollider);

	GET_SINGLE(CollisionManager)->AddCollider(boxCollider);

	//Vec2Int size = _ani->GetAnimator()->GetInfo().size;
	//SetSize({ (float)size.x , (float)size.y });

	AddComponent(_ani);
	AddComponent(boxCollider);

	Super::Init();
}

void Lava::Update()
{
	Super::Update();

	float deltaTime = TIME->GetDeltaTime();
	deltaTime = clamp(deltaTime, 0.0f, 0.1f);
	_sumTime += deltaTime;

	if (_state == LavaState::Start)
	{
		if (_ani->GetCurrentAinmationEndIndex())
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

	if (_state == LavaState::LaserStatEnd && _ani->GetCurrentAinmationEndIndex())
	{
		SetIsActivity(false);
	}


}

void Lava::Render(HDC hdc)
{
	Super::Render(hdc);
	//Utils::DrawRect(hdc, _pos, _size.x, _size.y);
}

void Lava::Activate(Vec3 pos, float duration)
{
	GetTransform()->SetPosition(pos);

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

	if (other->GetGameObject()->GetEntityType() == EntityType::Monster)
	{
		auto it = _hitCooldownMap.find(other);

		if (it == _hitCooldownMap.end())
		{
			static_cast<Entity*>(other->GetGameObject())->TakeDamage(_damageInfo);
			_hitCooldownMap[other] = _sumTime;
		}
		else
		{
			if (_sumTime - it->second >= _info._attackDelay)
			{
				static_cast<Entity*>(other->GetGameObject())->TakeDamage(_damageInfo);
				it->second = _sumTime;
			}
		}

	}
}

void Lava::OnTriggerExit(Collider* collider, Collider* other)
{
	_hitCooldownMap.erase(other);
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
