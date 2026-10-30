#pragma once
#include "97.Engin/Component/Component.h"

class CameraComponent :   public Component
{
	using Super = Component;
public:
	CameraComponent();
	virtual ~CameraComponent() override;

	virtual void Init() override;
	virtual void Update() override;
	//virtual void Render(HDC hdc) override;
};

