#pragma once
#include "AOE.h"




class BLBookObj :   public AOE
{
	using Super = AOE;
public:
	BLBookObj();
	virtual ~BLBookObj() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	//void Activate()


	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	virtual void Reset() override;
private:


};

