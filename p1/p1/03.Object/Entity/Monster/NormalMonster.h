#pragma once
#include "Monster.h"


class NormalMonster :    public Monster
{
	using Super = Monster;
public:
	NormalMonster();
	virtual ~NormalMonster() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void InitStat() override;

	virtual void Reset() override;


	void Move(float deltaTime);
	void Attack(float deltaTime);
	

private:
	vector<wstring> _monsterContainer = { L"Fubura",L"Shubangelion" };

	float _sumTime = 0;
	float _pattenrTime = 0;
	float _attackRange = 0;
};

