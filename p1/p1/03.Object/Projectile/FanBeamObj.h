#pragma once
#include "AOE.h"




class Animator;
class AnimationComponent;
class Collider;

class FanBeamObj :   public AOE
{
	using Super = AOE;
public:
	FanBeamObj();
	virtual ~FanBeamObj() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetDir(DirState dir) { _dir = dir; }
	

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	virtual void OnTriggerStay(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	virtual void Reset() override;

	void SetState(DirState dir);
	void UpdateAnimation();
private:

	DirState _dir;

	vector<Collider*> _collsion;

	Animator* _dirAni[2] = {};
	AnimationComponent* _ani = nullptr;
};

