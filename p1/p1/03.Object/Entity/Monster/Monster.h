#pragma once
#include "../Entity.h"


class Monster	: public Entity
{
	using Super = Entity;
public:
	Monster();
	virtual ~Monster() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void InitCommon();
	virtual void InitStat();

	virtual void Reset() override;
	GameObject* SerachPlayer();

protected:
	GameObject* _target= nullptr;
	int32 _score = 0;
};

