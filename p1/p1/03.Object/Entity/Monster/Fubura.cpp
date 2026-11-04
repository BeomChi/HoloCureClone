#include "pch.h"
#include "Fubura.h"
#include "../../../01.Manager/TimeManager.h"
#include "../../../01.Manager/ResourceManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../02.Scene/Scene.h"
#include "../../../03.Object/Projectile/Laser.h"
#include "../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../04.Component/Collision/BoxCollider.h"
#include "97.Engin/Component/Animation/Animator.h"
#include "97.Engin/Resource/Animation.h"

Fubura::Fubura()
{
}

Fubura::~Fubura()
{
}

void Fubura::Init()
{
	_aniIdle[DIR_LEFT] = RESOURCE->Get<Animation>(L"Fubura_MoveLeft");
	_aniIdle[DIR_RIGHT] = RESOURCE->Get<Animation>(L"Fubura_MoveRight");

	_aniMove[DIR_LEFT] = RESOURCE->Get<Animation>(L"Fubura_MoveLeft");
	_aniMove[DIR_RIGHT] = RESOURCE->Get<Animation>(L"Fubura_MoveRight");

	_aniAttack[START] = RESOURCE->Get<Animation>(L"FanSpawn");
	_aniAttack[ATTACK] = RESOURCE->Get<Animation>(L"FanSpawn");

	//SetScale({ 1.5f, 1.5f });
	_ani = new Animator();
	_ani->SetAnimation(_aniIdle[_dir]);
	SetState(State::Move);

	_score = 500;

	Super::Init();
}

void Fubura::Update()
{
	Super::Update();

	float deltaTime = TIME->GetDeltaTime();
	

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
		if (_ani->GetCurrentAinmationEndIndex())
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
	
	Vec3 pos = GetTransform()->GetPosition();
	pos += _velocity * deltaTime;
	GetTransform()->SetPosition(pos);

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
	Vec3 dir = _target->GetTransform()->GetPosition() - GetTransform()->GetPosition();
	dir.Normalize();

	Vec3 distance = _target->GetTransform()->GetPosition() - GetTransform()->GetPosition();
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

		Vec3 pos;
		pos.x = _target->GetTransform()->GetPosition().x - 5;
		pos.y = (_target->GetTransform()->GetPosition().y - 400) + 100.f * (i + 1);

		laser->Activate(pos, 5);
		laser->GetTransform()->SetScale({ 1.75,2,1 });
		laser->SetDamageInfo({ this,25,false });

		SCENE->GetCurrentScene()->AddObject(laser);
	}
}
