#pragma once
#include "97.Engin/Component/Component.h"

class Transform : public Component
{
	using Super = Component;
public:
	Transform();
	virtual ~Transform() override;

	virtual void Init() override;
	virtual void Update() override;

	void UpdateTransform();

	// Local
	Vec3 GetLoaclScale() { return _localScale; }
	void SetLocalScale(const Vec3& scale) { _localScale = scale; UpdateTransform(); }

	Vec3 GetLoaclRotation() { return _localRotation; }
	void SetLocalRotation(const Vec3& rotation) { _localRotation = rotation; UpdateTransform(); }

	Vec3 GetLocalPosition() { return _localScale; }
	void SetLocalPosition(const Vec3& position) { _localPosition = position; UpdateTransform(); }

	// World
	Vec3 GetScale() { return _localScale; }
	void SetScale(const Vec3& worldScale);

	Vec3 GetRotation() { return _localRotation; }
	void SetRotation(const Vec3& worldRotation);

	Vec3 GetPosition() { return _localPosition; }
	void SetPosition(const Vec3& worldPosition);

	Vec3 GetRighjt() { return _matWorld.Right(); }
	Vec3 GetUp() { return _matWorld.Up(); }
	Vec3 GetLook() { return _matWorld.Backward(); }

	Matrix GetWorldMatrix() { return _matWorld; }

	// 계층 관계일경우
	bool HasParent() { return _parent != nullptr; }
	Transform* GetParent() { return _parent; }
	void SetParent(Transform* parent) { _parent = parent; }

	const vector<Transform*>& GetChildren() { return _children; }
	void AddChild(Transform* child) { _children.push_back(child); }

private:
	Vec3 _localPosition = { 0.f,0.f,0.f };
	Vec3 _localRotation = { 0.f,0.f,0.f };
	Vec3 _localScale = { 1.f,1.f,1.f };

	// Cache
	Matrix _matLocal = Matrix::Identity;
	Matrix _matWorld = Matrix::Identity;

	Vec3 _scale;
	Vec3 _rotation;
	Vec3 _position;

	Vec3 _right;
	Vec3 _up;
	Vec3 _look;

private:
	Transform* _parent;
	vector<Transform*> _children;

};

