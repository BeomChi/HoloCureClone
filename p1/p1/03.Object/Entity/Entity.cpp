#include "pch.h"
#include "Entity.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/GameManager.h"
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
}

void Entity::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Entity::TakeDamage(const DamageInfo& dmg)
{
	if (_info._currentHp <= 0)
		return;


	// 디버깅용 로그
	if (dmg._isCritical)
		cout << "★ 크리티컬 데미지! (" << dmg._finalDamage << ")" << endl;
	else
		cout << "일반 데미지 (" << dmg._finalDamage << ")" << endl;


	_info._currentHp -= dmg._finalDamage;

	if (_info._currentHp <= 0)
	{
		_info._isDead = true;
		SetState(State::Die);
	}
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
	cout << "[DEBUG] 방향 변경됨: " << (_dir == DIR_LEFT ? "LEFT" : "RIGHT") << endl;
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
	case State::Spawn:
		_ani->SetAnimation(_aniSpawn);
		break;
	case State::Die:
		_ani->SetAnimation(_aniDie);
		break;
	}
}

void Entity::Reset()
{
	_info._currentHp = _info._maxHp;
}
