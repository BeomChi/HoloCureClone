#pragma once
#include "../GameObject.h"

struct ProjectileInfo
{
	Vector _dir = {0,0};
	float _speed = 0;

	int32 _pierceCount = 0; // °üÅë ¼ö
};


class Projectile :   public GameObject
{
	using Super = GameObject;
public:
	Projectile();
	virtual ~Projectile() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetDir(Vector dir) { _info._dir = dir; }
	void SetDamageInfo(const DamageInfo& info) { _damageInfo = info; }


protected:
	ProjectileInfo _info;
	DamageInfo _damageInfo;
};

