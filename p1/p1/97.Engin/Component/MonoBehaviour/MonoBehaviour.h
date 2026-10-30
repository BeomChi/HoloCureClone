#pragma once
#include "97.Engin/Component/Component.h"

class MonoBehaviour : public Component
{
	using Super = Component;
public:
	MonoBehaviour();
	~MonoBehaviour();

	virtual void Init() override;
	virtual void Update() override;
};

