#pragma once
#include "AOE.h"




class Miasma :   public AOE
{
	using Super = AOE;
public:
	Miasma();
	virtual ~Miasma() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	//void Activate()


	virtual void OnTriggerStay(Collider* collider, Collider* other) override;


	virtual void Reset() override;
private:

	float _sumTime = .8f;
};

