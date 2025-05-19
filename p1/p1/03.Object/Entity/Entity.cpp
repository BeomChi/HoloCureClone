#include "../../pch.h"
#include "Entity.h"
#include "../../04.Component/2D/AnimationComponent.h"

Entity::Entity() 
{
}

Entity::~Entity()
{
}

void Entity::Init()
{
	Super::Init();
}

void Entity::Update()
{
	Super::Update();

	if (_info._currentHp <= 0)
	{
		_info._isDead = true;
	}
}

void Entity::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Entity::SetState(State state)
{
	if (_state == state)
		return;

	_state = state;
	UpdateAnimation();
}

void Entity::SetDir(Dir dir)
{
	if (_dir == dir)
		return;

	_dir = dir;
	UpdateAnimation();
}

void Entity::SetenumAttack(enumAttack attack)
{
	if (_attack == attack)
		return;

	_attack = attack;
	UpdateAnimation();
}

void Entity::UpdateAnimation()
{
	switch (_state)
	{
	case State::Idle:
		_ani->SetAnimation(_aniIdle[_dir]);
		break;
	case State::Move:
		_ani->SetAnimation(_aniMove[_dir]);
		break;
	case State::Attack:
		_ani->SetAnimation(_aniAttack[_attack]);
	case State::Watch:
		break;
	}
}

void Entity::Reset()
{
	_info._currentHp = _info._maxHp;
}
