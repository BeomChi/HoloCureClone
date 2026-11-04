#pragma once
#include "AOE.h"




class Animator;
class Animation;
class Collider;

class TridentObj :   public AOE
{
	using Super = AOE;
public:
	TridentObj();
	virtual ~TridentObj() override;

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

	vector<Collider*> _collsion;

	Animation* _dirAni[2] = {};
	Animator* _ani = nullptr;
};

