#pragma once
#include "../Bar.h"

class Sprite;




class HpBar : public Bar
{
	using Super = Bar;
public:
	HpBar();
	virtual ~HpBar() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetHP(float current, float max);


protected:
	float _hp = 100.f;
	float _maxHp = 100.f;

	float _barLength = 100.f;       // 전체 길이
};

