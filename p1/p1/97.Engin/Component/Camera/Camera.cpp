#include "pch.h"
#include "Camera.h"
#include "97.Engin/Component/Transform/Transform.h"

Matrix Camera::s_matView = Matrix::Identity;
Matrix Camera::s_matProjection = Matrix::Identity;

Camera::Camera() : Super(ComponentType::Camera)
{
}

Camera::~Camera()
{
}	

void Camera::Update()
{
	UpdateMatrix();
}

void Camera::UpdateMatrix()
{
	// 카메라 현재 위치
	Vec3 eyePosition = GetTransform()->GetPosition();
	// 카메라가 바라보는 지점
	Vec3 focusPosition = eyePosition + GetTransform()->GetLook();
	// 카메라에서 위쪽이 어느 방향인지
	Vec3 upDirection = GetTransform()->GetUp();

	// 위에 있는 걸 기준으로 행렬을 만들어 달라
	s_matView = XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);

	// 위랑 같은 계산 값이 나옴
	// 역행렬이 한줄로 퉁칠 수 있어서 편할지도?
	//s_matView = GetTransform()->GetWorldMatrix().Invert();

	if (_type == ProjectionType::Perspective)
	{
		s_matProjection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PI / 4.f, 800.f / 600.f, 1.f, 100.f);
	}
	else
	{
		s_matProjection = DirectX::XMMatrixOrthographicLH(800, 600, 0.f, 1.f);
	}
}
