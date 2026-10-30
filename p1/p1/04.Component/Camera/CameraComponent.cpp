#include "pch.h"
#include "CameraComponent.h"
#include "../../03.Object/GameObject.h"
#include "../../01.Manager/SceneManager.h"
#include "97.Engin/Component/Transform/Transform.h"

CameraComponent::CameraComponent() : Super(ComponentType::Camera)
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
	if (_gameObject == nullptr)
	{
		cout << "[DEBUG] owner == nullptr!!" << endl;
		return;
	}

	Vec3 pos = _gameObject->GetTransform()->GetPosition();

	pos.x = clamp(pos.x, 400.f, 2560.f - 400.f);
	pos.y = clamp(pos.y, 300.f, 2560.f - 300.f);

	// TODO 카메라 오브젝트 삭제 후 여기다가 기능넣기
	//SCENE->SetCameraPos(pos);
	//cout << "[DEBUG] pos : " << pos.x <<" "<<pos.y << endl;
}

//void CameraComponent::Render(HDC hdc)
//{
//	
//}
