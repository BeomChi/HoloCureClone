#pragma once
#include "../GameObject.h"

struct FanBeamObjInfo
{
	float _dmg = 0;
	float _attackDelay = 0.5f;

	float _baseScale = 1.f;
};



class Animator;
class AnimationComponent;
class Collider;

class FanBeamObj :   public GameObject
{
	using Super = GameObject;
public:
	FanBeamObj();
	virtual ~FanBeamObj() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetDir(DirState dir) { _dir = dir; }
	void SetDmg(float dmg) { _info._dmg = dmg; }
	void SetAttackDelay(float delay) { _info._attackDelay = delay; }
	

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	virtual void OnTriggerStay(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	virtual void Reset() override;

	void SetState(DirState dir);
	void UpdateAnimation();
private:
	FanBeamObjInfo _info;
	DirState _dir;
	float _sumTime = .8f;

	vector<Collider*> _collsion;

	Animator* _dirAni[2] = {};
	AnimationComponent* _ani = nullptr;
};

