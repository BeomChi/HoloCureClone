#include "pch.h"
#include "Camera.h"
#include "../../01.Manager/InputManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../03.Object/Entity/Player/Player.h"
#include "../../04.Component/Camera/CameraComponent.h"

Camera::Camera()
{
}

Camera::~Camera()
{
	_target = nullptr;
}

void Camera::Init()
{
	{
		CameraComponent* camera = new CameraComponent();
		AddComponent(camera);
	}

	Super::Init();
}

void Camera::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	Input();

	if (_target == nullptr)
	{
		MoveCamera(deltaTime);
		return;
	}

	Vec2 pos = _target->GetPos();

	pos.x = clamp(pos.x, 400.f, 2560.f - 400.f);
	pos.y = clamp(pos.y, 300.f, 2560.f - 300.f);

	_pos = pos;
}

void Camera::MoveCamera(float deltaTime)
{
	auto input = GET_SINGLE(InputManager);
	Vector dir = { 0,0 };

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
	

	dir.Normalize();
	_pos += dir * 200 * deltaTime;

	GET_SINGLE(SceneManager)->SetCameraPos(_pos);
}

void Camera::Input()
{
	auto input = GET_SINGLE(InputManager);
	if (input->GetButtonDown(KeyType::KEY_0))
	{
		if (_target == nullptr)
		{
			Player* player = GET_SINGLE(GameManager)->GetPlayer();
			GameObject* obj = static_cast<GameObject*>(player);
			_target = obj;
		}
		else if (_target != nullptr)
		{
			_target = nullptr;
		}
	}
}

void Camera::SetTarget(GameObject* target)
{
	_target = target;
}
