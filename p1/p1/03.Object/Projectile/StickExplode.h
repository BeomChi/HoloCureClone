#pragma once
#include "AOE.h"



class Animator;
class AnimationComponent;


class StickExplode :   public AOE
{
	using Super = AOE;
public:
	StickExplode();
	virtual ~StickExplode() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	//void Activate()

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;


	virtual void Reset() override;
private:
	vector<Collider*> _collsion;

	Animator* _animation = nullptr;
	AnimationComponent* _ani = nullptr;

};

