#pragma once
#include "Monster.h"


class Fubura :    public Monster
{
	using Super = Monster;
public:
	Fubura();
	virtual ~Fubura() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void InitStat() override;

	virtual void Reset() override;


	void Move(float deltaTime);
	void Attack(float deltaTime);
	void LaserPattern();

private:
	float _sumTime = 0;
	float _laserDurationTime = 5;
	float _pattenrTime = 0;
};

