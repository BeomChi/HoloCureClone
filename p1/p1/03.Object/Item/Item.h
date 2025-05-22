#pragma once
#include "../GameObject.h"



class Item :    public GameObject
{
	using Super = GameObject;
public:
	Item();
	virtual ~Item() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
};

