#pragma once
#include "../../03.Object/GameObject.h"


struct BombObjInfo
{
	float _duration = 0;
	float _time = 0;
	float _dmg = 0;
	float _attackDelay = 0;
};

class BombObj : public GameObject
{
	using Super = GameObject;
public:
	BombObj();
	virtual ~BombObj();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetDemage(float dmg) { _info._dmg = dmg; }
	void SetAttackDelay(float delay) { _info._attackDelay = delay; }
	void SetDuration(float duration) { _info._duration = duration; }

	virtual void Reset() override;


	
	
private:
	BombObjInfo _info;
};

