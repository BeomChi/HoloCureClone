#include "../../pch.h"
#include "CameraComponent.h"
#include "../../03.Object/GameObject.h"
#include "../../01.Manager/SceneManager.h"

CameraComponent::CameraComponent()
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Init()
{
}

void CameraComponent::Update()
{
	if (_owner == nullptr)
		return;

	Vec2 pos = _owner->GetPos();

	pos.x = clamp(pos.x, 400.f, 2560.f - 400.f);
	pos.y = clamp(pos.y, 300.f , 2560.f - 300.f);

	GET_SINGLE(SceneManager)->SetCameraPos(pos);
}

void CameraComponent::Render(HDC hdc)
{
	
}
