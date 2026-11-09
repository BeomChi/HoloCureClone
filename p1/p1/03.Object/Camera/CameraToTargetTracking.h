#pragma once
#include "../../97.Engin/Component/MonoBehaviour/MonoBehaviour.h"

class GameObject;

class CameraToTargetTracking : public MonoBehaviour
{
	using Super = MonoBehaviour;
public:
	CameraToTargetTracking();
	virtual ~CameraToTargetTracking() override;

	virtual void Init() override;
	virtual void Update() override;

	void MoveCamera(float deltaTime);
	void Input();

	void SetTarget(GameObject* target);;

private:
	GameObject* _target = nullptr;
};

