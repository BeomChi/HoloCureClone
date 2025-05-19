#pragma once
#include "../GameObject.h"

struct BulletInfo
{
	Vector _dir = {};
	float _dmg = 0;
	float _time = 0;
	float _speed = 0;
};


class Bullet :   public GameObject
{
	using Super = GameObject;
public:
	Bullet();
	virtual ~Bullet() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetDir(Vector dir) { _info._dir = dir; }
	void SetDmg(float dmg) { _info._dmg = dmg; }

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	virtual void Reset() override;
private:
	BulletInfo _info;
};

