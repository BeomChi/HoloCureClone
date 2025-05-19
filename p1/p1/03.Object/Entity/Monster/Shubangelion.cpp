#include "../../../pch.h"
#include "Shubangelion.h"
#include "../../../01.Manager/TimeManager.h"
#include "../../../01.Manager/ResourceManager.h"
#include "../../../01.Manager/ObjectManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../03.Object/Projectile/Laser.h"
#include "../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../04.Component/2D/AnimationComponent.h"
#include "../../../04.Component/Collision/BoxCollider.h"
#include "../../../05.Resource/2D/Animator.h"

Shubangelion::Shubangelion()
{
}

Shubangelion::~Shubangelion()
{
}

void Shubangelion::Init()
{
	_aniIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Shubangelion_MoveLeft");
	_aniIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Shubangelion_MoveRight");

	_aniMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Shubangelion_MoveLeft");
	_aniMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Shubangelion_MoveRight");

	_aniAttack[CHARGE] = GET_SINGLE(ResourceManager)->GetAnimator(L"Shubangelion_Charge");
	_aniAttack[ATTACK] = GET_SINGLE(ResourceManager)->GetAnimator(L"Shubagelion_Attack");

	_ani = new AnimationComponent();
	_ani->SetAnimation(_aniIdle[_dir]);
	SetState(State::Move);
	_attack = CHARGE;

	_score = 500;

	Super::Init();
}

void Shubangelion::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_target == nullptr)
		_target = SerachPlayer();

	if (_target == nullptr)
		return;


	switch (_state)
	{
	case State::Move:
		Move(deltaTime);
		break;
	case State::Attack:
		Attack(deltaTime);
		break;
	}
	
}

void Shubangelion::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Shubangelion::InitStat()
{
	_info._maxHp = 3000.f;
	_info._currentHp = _info._maxHp;
	_info._atk = 2.f;
	_info._speed = 100.f;

	_attackRange = 300;
}

void Shubangelion::Reset()
{
	SetState(State::Move);
	_attack = CHARGE;
	InitStat();
}

void Shubangelion::Move(float deltaTime)
{
	Vector dir = _target->GetPos() - GetPos();
	dir.Normalize();

	Vector distance = _target->GetPos() - GetPos();
	float dist = sqrt(distance.x * distance.x + distance.y * distance.y);

	if (distance.x > 0)
	{
		SetDir(DIR_RIGHT);
	}
	else
	{
		SetDir(DIR_LEFT);
	}


	if (dist <= 100)
	{
		_info._speed = 0;
		if (_sumTime >= 10.f)
		{
			SetState(State::Attack);
		}
	}
	else
		_info._speed = 100;

	Vector moveDir = dir * _info._speed * deltaTime;
	_pos += moveDir;
}

void Shubangelion::Attack(float deltaTime)
{
	_pattenrTime += deltaTime;

	//SetenumAttack(CHARGE);

	if (_pattenrTime == deltaTime)
	{
		ChangeAttack();
	}

	if (_pattenrTime >= _laserDurationTime)
	{
		_pattenrTime = 0;
		_sumTime = 0;
		SetState(State::Move);
	}
}

void Shubangelion::ChangeAttack()
{
	//SetenumAttack(ATTACK);
	Vector distance = _target->GetPos() - GetPos();
	float dist = sqrt(distance.x * distance.x + distance.y * distance.y);


	if (dist <= _attackRange )
	{
		static_cast<Entity*>(_target)->TakeDamage(_info._atk);
	}

}
