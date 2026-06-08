#include "pch.h"
#include "NormalMonster.h"
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

NormalMonster::NormalMonster()
{
}

NormalMonster::~NormalMonster()
{
}

void NormalMonster::Init()
{
	int32 stage = 0;
	int32 randMonster = RandomRange(0, 4);

	wstring monster = _monsterContainer[randMonster];

	wstring idleLeft = monster + L"_IdleLeft";
	wstring idleRight = monster + L"_IdleRight";;
	wstring moveLeft = monster + L"_MoveLeft";;
	wstring moveRight = monster + L"_MoveRight";;

	_aniIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(idleLeft);
	_aniIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(idleRight);

	_aniMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(moveLeft);
	_aniMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(moveRight);

	_aniAttack[START] = GET_SINGLE(ResourceManager)->GetAnimator(L"FanSpawn");
	_aniAttack[ATTACK] = GET_SINGLE(ResourceManager)->GetAnimator(L"FanSpawn");

	
	_ani = new AnimationComponent();
	_ani->SetAnimation(_aniIdle[_dir]);
	SetState(State::Move);

	_score = 100;
	_attackRange = 50;

	Super::Init();
}

void NormalMonster::Update()
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
		break;
	case State::Stagger:
		// 일단 임시로 이렇게 하고 나중에 고치는 걸로
		_info._staggerTime += deltaTime;

		if (_info._staggerTime >= 1.f)
		{
			_info._staggerTime = 0.f;
			SetState(State::Move);
		}
		break;
	case State::Stun:
		// 일단 임시로 이렇게 하고 나중에 고치는 걸로
		_info._staggerTime += deltaTime;

		if (_info._staggerTime >= 1.f)
		{
			_info._staggerTime = 0.f;
			SetState(State::Move);
		}
		break;
	}

	_pos += _velocity * deltaTime;

	// 이동 후 속도 감소 (마찰 같은 느낌)
	_velocity *= 0.9f; // or 0.8f, 자연 감속
	
}

void NormalMonster::Render(HDC hdc)
{
	Super::Render(hdc);
}

void NormalMonster::InitStat()
{
	_info._maxHp = 10.f;
	_info._currentHp = _info._maxHp * min(max(1, GET_SINGLE(StageManager)->GetTime() * 0.25f),100);
	_info._atk = 10.f;
	_info._speed = 100.f;
	_info._staggerTime = 0;
	_info._isDead = false;
}

void NormalMonster::Reset()
{
	SetState(State::Move);
	InitStat();
	_target = SerachPlayer();
}

void NormalMonster::Move(float deltaTime)
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

	if (dist <= 25.f)
    {
        _velocity = { 0,0 };
        _sumTime += deltaTime;

        if (_sumTime >= 0.5f)
            SetState(State::Attack);
    }
    else
    {
        _velocity = dir * _info._speed;
    }

	//Vector moveDir = dir * _info._speed * deltaTime;
	//_pos += moveDir;
}

void NormalMonster::Attack(float deltaTime)
{
	_pattenrTime += deltaTime;

	if (_pattenrTime == deltaTime && _target != nullptr)
	{
		Vector distance = _target->GetPos() - GetPos();
		float dist = sqrt(distance.x * distance.x + distance.y * distance.y);


		static_cast<Entity*>(_target)->TakeDamage({ this,_info._atk,false });
	}

	if (_pattenrTime >= 1)
	{
		_pattenrTime = 0;
		_sumTime = 0;
		SetState(State::Move);
	}
}

