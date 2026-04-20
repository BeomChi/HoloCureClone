#pragma once
#include "AOE.h"




class BombObj : public AOE
{
	using Super = AOE;
public:
	BombObj();
	virtual ~BombObj();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;



	virtual void Reset() override;
private:
};

