#include "pch.h"
#include "Shubangelion.h"
#include "../../../01.Manager/TimeManager.h"
#include "../../../01.Manager/ResourceManager.h"
#include "../../../01.Manager/ObjectManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../01.Manager/StageManager.h"
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

	_aniIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Shubangelion_Charge");
	_aniIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Shubangelion_Charge");

	_aniMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Shubangelion_MoveLeft");
	_aniMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Shubangelion_MoveRight");

	_aniAttack[START] = GET_SINGLE(ResourceManager)->GetAnimator(L"Shubangelion_Charge");
	_aniAttack[ATTACK] = GET_SINGLE(ResourceManager)->GetAnimator(L"Shubagelion_Attack");

	_ani = new AnimationComponent();
	_ani->SetAnimation(_aniIdle[_dir]);
	SetState(State::Move);
	_attack = START;

	_score = 500;
	Super::Init();

}

void Shubangelion::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

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
	case State::Spawn:
		if (_ani->CheckCurrentAnimationEnd())
		{
			SetState(State::Move);
		}
	case State::Stagger:
		SetState(State::Move);
		break;
	}
	
	_pos += _velocity * deltaTime;

	// 이동 후 속도 감소 (마찰 같은 느낌)
	_velocity *= 0.9f; // or 0.8f, 자연 감속
}

void Shubangelion::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Shubangelion::InitStat()
{
	_info._maxHp = 3000.f;
	_info._currentHp = _info._maxHp;
	_info._atk = 40.f;
	_info._speed = 110.f;

	_attackRange = 300;
}

void Shubangelion::Reset()
{
	SetState(State::Move);
	_attack = START;
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

	if (dist <= _attackRange / 2)
	{
		_velocity = { 0,0 };
		_sumTime += deltaTime;

		if (_sumTime >= 2.f)
			SetState(State::Attack);
	}
	else
	{
		_velocity = dir * _info._speed;
	}
}

void Shubangelion::Attack(float deltaTime)
{
	if (_paattenNumber == 0)
	{
		SetenumAttack(START);

		if (!_ani->CheckCurrentAnimationEnd())
			return;

		_paattenNumber = 1;
	}

	if (_paattenNumber == 1)
	{
		ChangeAttack();
	}
}

void Shubangelion::ChangeAttack()
{
	SetenumAttack(ATTACK);

	if (!_ani->CheckCurrentAnimationEnd())
		return;

	Vector distance = _target->GetPos() - GetPos();
	float dist = sqrt(distance.x * distance.x + distance.y * distance.y);


	if (dist <= _attackRange )
	{
		static_cast<Entity*>(_target)->TakeDamage({ this,_info._atk,false });
	}

	_paattenNumber = 0;
	_sumTime = 0;
	SetState(State::Move);
}
