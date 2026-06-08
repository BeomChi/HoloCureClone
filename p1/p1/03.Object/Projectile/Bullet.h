#pragma once
#include "Projectile.h"



class Bullet :   public Projectile
{
	using Super = Projectile;
public:
	Bullet();
	virtual ~Bullet() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;


	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;

	virtual void Reset() override;

	void SetPierceCount(int32 count) { _info._pierceCount = count; }
private:

	int32 _currentPierceCount = 0;
};

