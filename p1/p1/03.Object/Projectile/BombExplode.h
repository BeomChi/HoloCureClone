#pragma once
#include "AOE.h"

class Animator;
class AnimationComponent;


class BombExplode : public AOE
{
	using Super = AOE;
public:
	BombExplode();
	virtual ~BombExplode();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;


	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;


	virtual void Reset() override;

	
	
private:
	vector<Collider*> _collsion;
	
	Animator* _animation = nullptr;
	AnimationComponent* _ani = nullptr;
};

