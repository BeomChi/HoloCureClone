#pragma once
#include "../GameObject.h"

struct MiasmaInfo
{
	float _duration = 0;
	float _time = 0;
	float _dmg = 0;
	float _attackDelay = 1;

	float _baseScale = 1.f;
};


class Miasma :   public GameObject
{
	using Super = GameObject;
public:
	Miasma();
	virtual ~Miasma() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	//void Activate()

	void SetDmg(float dmg) { _info._dmg = dmg; }
	void SetScaleMultple(float scale);

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	virtual void OnTriggerStay(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	virtual void Reset() override;
private:
	MiasmaInfo _info;
	float _sumTime = .8f;
};

