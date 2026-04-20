#pragma once
#include "AOE.h"

class Animator;
class AnimationComponent;

enum class LaserState
{
	Start,
	Fire,

	LaserStatEnd
};


class Laser : public AOE
{
	using Super = AOE;
public:
	Laser();
	virtual ~Laser();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Activate(Vec2 pos, float duration);


	virtual void OnTriggerStay(Collider* collider, Collider* other) override;

	virtual void Reset() override;

	void SetState(LaserState state);
	void UpdateAnimation();
private:

	LaserState _state = LaserState::Start;
	Animator* _laser[2] = {};
	AnimationComponent* _ani = nullptr;
};

