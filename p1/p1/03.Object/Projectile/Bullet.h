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
private:

};

