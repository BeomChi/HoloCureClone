#pragma once
#include "../GameObject.h"

struct BLBookSt
{
	float _dmg = 0;
};


class BLBookObj :   public GameObject
{
	using Super = GameObject;
public:
	BLBookObj();
	virtual ~BLBookObj() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	//void Activate()

	void SetDmg(float dmg) { _info._dmg = dmg; }

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	virtual void Reset() override;
private:
	BLBookSt _info;
};

