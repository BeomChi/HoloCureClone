#include "pch.h"
#include "Transform.h"

Transform::Transform() :Super(ComponentType::Transform)
{
}

Transform::~Transform()
{
	if (_parent)
		_parent = nullptr;

	for (const Transform* child : _children)
	{
		child = nullptr;
	}
}

void Transform::Init()
{
}

void Transform::Update()
{
}

Vec3 ToEulerAngles(Quaternion q)
{
	Vec3 angles;

	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angles.x = std::atan2(sinr_cosp, cosr_cosp);

	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angles.y = 2 * std::atan2(sinp, cosp) * 3.14159f / 2.f;

	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angles.z = std::atan2(siny_cosp, cosy_cosp);

	return angles;
}

void Transform::UpdateTransform()
{
	Matrix matScale = Matrix::CreateScale(_localScale);
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	Matrix matLocal = matScale * matRotation * matTranslation;
	_matLocal = matLocal;

	if (HasParent())
	{
		_matWorld = _matLocal * _parent->GetWorldMatrix();
	}
	else
	{
		_matWorld = matLocal;
	}

	Quaternion quat;

	_matWorld.Decompose(_scale, quat, _position);
	_rotation = ToEulerAngles(quat);

	/*_right = Vec3::TransformNormal(Vec3::Right, _matWorld);
	_up = Vec3::TransformNormal(Vec3::Up, _matWorld);
	_look = Vec3::TransformNormal(Vec3::Backward, _matWorld);*/

	for (Transform* child : _children)
	{
		child->UpdateTransform();
	}
}

void Transform::SetScale(const Vec3& worldScale)
{
	if (HasParent())
	{
		Vec3 parentScale = _parent->GetScale();
		Vec3 scale = worldScale;

		scale.x /= parentScale.x;
		scale.y /= parentScale.y;
		scale.z /= parentScale.z;
	}
	else
	{
		SetLocalScale(worldScale);
	}
}

void Transform::SetRotation(const Vec3& worldRotation)
{
	if (HasParent())
	{
		Matrix worldToParentLocalMatrix = _parent->GetWorldMatrix().Invert();

		Vec3 rotation;
		rotation.TransformNormal(worldRotation, worldToParentLocalMatrix);

		SetLocalRotation(rotation);
	}
	else
	{
		SetLocalRotation(worldRotation);
	}
}

void Transform::SetPosition(const Vec3& worldPosition)
{
	if (HasParent())
	{
		Matrix worldToParentLocalMatrix = _parent->GetWorldMatrix().Invert();

		Vec3 position;
		position.Transform(worldPosition, worldToParentLocalMatrix);

		SetLocalPosition(position);
	}
	else
	{
		SetLocalPosition(worldPosition);
	}

}
