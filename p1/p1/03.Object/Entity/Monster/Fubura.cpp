#include "pch.h"
#include "Fubura.h"
#include "../../../01.Manager/TimeManager.h"
#include "../../../01.Manager/ResourceManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../02.Scene/Scene.h"
#include "../../../03.Object/Projectile/Laser.h"
#include "../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../04.Component/2D/AnimationComponent.h"
#include "../../../04.Component/Collision/BoxCollider.h"
#include "../../../05.Resource/2D/Animator.h"

Fubura::Fubura()
{
}

Fubura::~Fubura()
{
}

void Fubura::Init()
{
	_aniIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Fubura_MoveLeft");
	_aniIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Fubura_MoveRight");

	_aniMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Fubura_MoveLeft");
	_aniMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Fubura_MoveRight");

	SetScale({ 1.5f, 1.5f });
	_ani = new AnimationComponent();
	_ani->SetAnimation(_aniIdle[_dir]);
	SetState(State::Move);

	_score = 500;

	Super::Init();
}

void Fubura::Update()
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

		if (_info._staggerTime >= 0.5f)
		{
			SetState(State::Move);
		}
		break;
	}
	
	_pos += _velocity * deltaTime;

	// 이동 후 속도 감소 (마찰 같은 느낌)
	_velocity *= 0.9f; // or 0.8f, 자연 감속
}

void Fubura::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Fubura::InitStat()
{
	_info._maxHp = 1000.f;
	_info._currentHp = _info._maxHp;
	_info._atk = 5.f;
	_info._speed = 100.f;
}

void Fubura::Reset()
{
	SetState(State::Move);
	InitStat();
}

void Fubura::Move(float deltaTime)
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

	if (dist <= 100.f)
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

void Fubura::Attack(float deltaTime)
{
	_pattenrTime += deltaTime;

	if (_pattenrTime == deltaTime)
		LaserPattern();

	if (_pattenrTime >= _laserDurationTime)
	{
		_pattenrTime = 0;
		_sumTime = 0;
		SetState(State::Move);
	}
}

void Fubura::LaserPattern()
{
	// 이게 왜 ㅈㄹ일까?
	// 해보고 안되면 rand() % 쓰자
	int safe = RandomRange(0, 3);

	for (int i = 0; i < 6; i++)
	{
		if (i == safe)
			continue;

		//Vec2 targetpos = GET_SINGLE(SceneManager)->ScreenToWorld(_target->GetPos());

		Laser* laser = GET_SINGLE(ObjectPool)->Get<Laser>(L"Laser");
		laser->Activate({ _target->GetPos().x - 5,(_target->GetPos().y - 400) + 100.f * (i + 1) }, 5);
		laser->SetScale({ 1.75,2 });
		laser->SetDamageInfo({ this,5,false });
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(laser);
	}
}
