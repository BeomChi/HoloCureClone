#pragma once
#include "../../03.Object/GameObject.h"

class Animator;
class AnimationComponent;


struct BombExplodeInfo
{
	float _duration = 0;
	float _time = 0;
	float _dmg = 0;
	float _attackDelay = 0;
};

class BombExplode : public GameObject
{
	using Super = GameObject;
public:
	BombExplode();
	virtual ~BombExplode();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetDemage(float dmg) { _info._dmg = dmg; }
	void SetAttackDelay(float delay) { _info._attackDelay = delay; }
	void SetDuration(float duration) { _info._duration = duration; }

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	virtual void OnTriggerStay(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	virtual void Reset() override;

	
	
private:
	BombExplodeInfo _info;
	vector<Collider*> _collsion;
	Animator* _animation = nullptr;
	
	AnimationComponent* _ani = nullptr;
};

