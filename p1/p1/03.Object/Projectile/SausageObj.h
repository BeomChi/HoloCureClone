#pragma once
#include "AOE.h"




class Animator;
class AnimationComponent;
class Collider;

class SausageObj :   public AOE
{
	using Super = AOE;
public:
	SausageObj();
	virtual ~SausageObj() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetDir(DirState dir) { _dir = dir; }

	

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;


	virtual void Reset() override;

	void SetState(DirState dir);
	void UpdateAnimation();
private:

	DirState _dir;
	float _sumTime = .8f;

	vector<Collider*> _collsion;

	Animator* _dirAni[2] = {};
	AnimationComponent* _ani = nullptr;
};

