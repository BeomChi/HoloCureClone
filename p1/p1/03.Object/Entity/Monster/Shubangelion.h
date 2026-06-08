#pragma once
#include "Monster.h"


class Shubangelion :    public Monster
{
	using Super = Monster;
public:
	Shubangelion();
	virtual ~Shubangelion() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void InitStat() override;

	virtual void Reset() override;

	void Move(float deltaTime);
	void Attack(float deltaTime);
	void ChangeAttack();

private:
	int8 _paattenNumber = 0;
	float _sumTime = 0;
	float _attackRange = 0;
};

