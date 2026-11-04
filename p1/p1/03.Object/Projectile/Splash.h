#pragma once
#include "AOE.h"





class Animation;
class Animator;
class Collider;

class Splash :   public AOE
{
	using Super = AOE;
public:
	Splash();
	virtual ~Splash() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetDir(DirState dir) { _dir = dir; }

	void SetKnockbackForce(float force) { _knockbackForce = force; }

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;

	virtual void Reset() override;

	void SetState(DirState dir);
	void UpdateAnimation();
private:
	DirState _dir;

	vector<Collider*> _collsion;

	float _knockbackForce = 0.f;

	Animation* _dirAni[2] = {};
	Animator* _ani = nullptr;
};

