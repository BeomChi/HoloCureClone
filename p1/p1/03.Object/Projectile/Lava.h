#pragma once
#include "../../03.Object/GameObject.h"

class Animator;
class AnimationComponent;

enum class LavaState
{
	Start,
	Fire,

	LaserStatEnd
};

struct LavaInfo
{
	float _duration = 0;
	float _time = 0;
	float _dmg = 0;
	float _attackDelay = 0;
};

class Lava : public GameObject
{
	using Super = GameObject;
public:
	Lava();
	virtual ~Lava();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void Activate(Vec2 pos, float duration);
	void SetDemage(float dmg) { _info._dmg = dmg; }
	void SetAttackDelay(float delay) { _info._attackDelay = delay; }
	void SetDuration(float duration) { _info._duration = duration; }

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	virtual void OnTriggerStay(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	virtual void Reset() override;

	void SetState(LavaState state);
	void UpdateAnimation();

	
	
private:
	LavaInfo _info;
	float _sumTime = .8f;
	LavaState _state = LavaState::Start;
	Animator* _lava[3] = {};
	AnimationComponent* _ani = nullptr;
};

