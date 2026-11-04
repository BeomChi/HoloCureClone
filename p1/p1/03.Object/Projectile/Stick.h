#pragma once
#include "Projectile.h"


class Animator;
class Animation;


class Stick :   public Projectile
{
	using Super = Projectile;
public:
	Stick();
	virtual ~Stick() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetDir(Vec3 dir) { _info._dir = dir; }
	void SetDamageInfo(const DamageInfo& info) { _damageInfo = info; }
	void SetStickPierceCount(int32 count) { _info._pierceCount = count; }

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	virtual void Reset() override;

private:
	DirState _dir;

	Animation* _animation = nullptr;
	Animator* _ani = nullptr;

	int32 _currentPierceCount = 0;
};

