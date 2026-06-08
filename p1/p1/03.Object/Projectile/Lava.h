#pragma once
#include "AOE.h"

class Animator;
class AnimationComponent;
class Collider;

enum class LavaState
{
	Start,
	Fire,

	LaserStatEnd
};



class Lava : public AOE
{
	using Super = AOE;
public:
	Lava();
	virtual ~Lava();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Activate(Vec2 pos, float duration);



	virtual void OnTriggerStay(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	virtual void Reset() override;

	void SetState(LavaState state);
	void UpdateAnimation();

	
	
private:

	float _sumTime = .8f;
	LavaState _state = LavaState::Start;
	Animator* _lava[3] = {};
	AnimationComponent* _ani = nullptr;

	unordered_map<Collider*, float> _hitCooldownMap;
};

