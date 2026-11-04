#include "pch.h"
#include "Shubangelion.h"
#include "../../../01.Manager/TimeManager.h"
#include "../../../01.Manager/ResourceManager.h"
#include "../../../01.Manager/ObjectManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../01.Manager/StageManager.h"
#include "../../../03.Object/Projectile/Laser.h"
#include "../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../04.Component/Collision/BoxCollider.h"
#include "97.Engin/Component/Animation/Animator.h"
#include "97.Engin/Resource/Animation.h"

Shubangelion::Shubangelion()
{
}

Shubangelion::~Shubangelion()
{
}

void Shubangelion::Init()
{

	_aniIdle[DIR_LEFT] = RESOURCE->Get<Animation>(L"Shubangelion_Charge");
	_aniIdle[DIR_RIGHT] = RESOURCE->Get<Animation>(L"Shubangelion_Charge");

	_aniMove[DIR_LEFT] = RESOURCE->Get<Animation>(L"Shubangelion_MoveLeft");
	_aniMove[DIR_RIGHT] = RESOURCE->Get<Animation>(L"Shubangelion_MoveRight");

	_aniAttack[START] = RESOURCE->Get<Animation>(L"Shubangelion_Charge");
	_aniAttack[ATTACK] = RESOURCE->Get<Animation>(L"Shubagelion_Attack");

	_ani = new Animator();
	_ani->SetAnimation(_aniIdle[_dir]);
	SetState(State::Move);
	_attack = START;

	_score = 500;
	Super::Init();

}

void Shubangelion::Update()
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
	case State::Stagger:
		SetState(State::Move);
		break;
	}
	
	Vec3 pos = GetTransform()->GetPosition();
	pos += _velocity * deltaTime;

	GetTransform()->SetPosition(pos);
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

		if (!_ani->GetCurrentAinmationEndIndex())
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

	if (!_ani->GetCurrentAinmationEndIndex())
		return;

	Vec3 distance = _target->GetTransform()->GetPosition() - GetTransform()->GetPosition();
	float dist = sqrt(distance.x * distance.x + distance.y * distance.y);


	if (dist <= _attackRange )
	{
		static_cast<Entity*>(_target)->TakeDamage({ this,_info._atk,false });
	}

	_paattenNumber = 0;
	_sumTime = 0;
	SetState(State::Move);
}
