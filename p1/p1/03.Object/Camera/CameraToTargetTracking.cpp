#include "pch.h"
#include "CameraToTargetTracking.h"
#include "../../01.Manager/InputManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../04.Component/Camera/CameraComponent.h"

CameraToTargetTracking::CameraToTargetTracking()
{
}

CameraToTargetTracking::~CameraToTargetTracking()
{
	_target = nullptr;
}

void CameraToTargetTracking::Init()
{
	Super::Init();
}

void CameraToTargetTracking::Update()
{
	Super::Update();

	float deltaTime = TIME->GetDeltaTime();

	Input();

	if (_target == nullptr)
	{
		MoveCamera(deltaTime);
		return;
	}

	Vec3 pos = _target->GetTransform()->GetPosition();

	pos.x = clamp(pos.x, 400.f, 2560.f - 400.f);
	pos.y = clamp(pos.y, 300.f, 2560.f - 300.f);

	GetTransform()->SetPosition(pos);
}

void CameraToTargetTracking::MoveCamera(float deltaTime)
{
	auto input = INPUT;
	Vec3 dir = { 0,0,0 };

	if (input->GetButton(KeyType::Up))
	{
		dir.y -= 1;
	}
	if (input->GetButton(KeyType::Down))
	{
		dir.y += 1;
	}
	if (input->GetButton(KeyType::Left))
	{
		dir.x -= 1;
	}
	if (input->GetButton(KeyType::Right))
	{
		dir.x += 1;
	}

	if (dir.x == 0 && dir.y == 0)
		return;
	

	Vec3 pos = GetTransform()->GetPosition();
	dir.Normalize();
	pos += dir * 200 * deltaTime;
	GetTransform()->SetPosition(pos);
	//SCENE->SetCameraPos(_pos);
}

void CameraToTargetTracking::Input()
{
	auto input = INPUT;
	if (input->GetButtonDown(KeyType::KEY_0))
	{
		if (_target == nullptr)
		{
			Player* player = GAMEMANAGER->GetPlayer();
			GameObject* obj = static_cast<GameObject*>(player);
			_target = obj;
		}
		else if (_target != nullptr)
		{
			_target = nullptr;
		}
	}
}

void CameraToTargetTracking::SetTarget(GameObject* target)
{
	_target = target;
}
