#pragma once
#include "../GameObject.h"



class Camera : public GameObject
{
	using Super = GameObject;
public:
	Camera();
	virtual ~Camera() override;

	virtual void Init() override;
	virtual void Update() override;

	void MoveCamera(float deltaTime);
	void Input();

	void SetTarget(GameObject* target);;

private:
	GameObject* _target = nullptr;
};

