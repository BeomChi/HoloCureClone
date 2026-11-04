#pragma once
#include "AOE.h"


class SpriteRenderer;

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
	SpriteRenderer* renderer = nullptr;
	float _sumTime = .8f;
	unordered_map<Collider*, float> _hitCooldownMap;
};

