#pragma once
#include "../GameObject.h"

class Animator;
class AnimationComponent;

struct Info
{
	int32 _currentHp = 0;
	int32 _maxHp = 0;
	int32 _atk = 0;
	float _speed = 0;
	int32 _exp = 0;
	int32 _maxExp = 0;
	int32 _level = 1;
	float _dmgMultiplier = 1;

	bool _isDead = false;
};

enum class State
{
	Idle,
	Move,
	Attack,
	Watch,
};

class Entity : public GameObject
{
	using Super = GameObject;
public:
	Entity();
	virtual ~Entity() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	Info GetInfo() const { return _info; }
	void TakeDamage(float dmg) { _info._currentHp -= dmg; }

	void SetState(State state);
	void SetDir(Dir dir);
	void SetenumAttack(enumAttack attack);

	void UpdateAnimation();

	virtual void Reset() override;

protected:
	Info _info;
	State _state = State::Idle;
	Dir _dir = DIR_LEFT;
	enumAttack _attack = CHARGE;

	Animator* _aniIdle[2] = {};
	Animator* _aniMove[2] = {};
	Animator* _aniAttack[2] = {};

	AnimationComponent* _ani = nullptr;
};

