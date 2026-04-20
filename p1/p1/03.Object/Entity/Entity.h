#pragma once
#include "../GameObject.h"

class Animator;
class AnimationComponent;

struct Info
{
	int32 _level = 1;
	int32 _currentHp = 0;
	int32 _maxHp = 0;
	int32 _atk = 0;
	int32 _exp = 0;
	int32 _maxExp = 0;

	float _speed = 0;
	float _dmgMultiplier = 1;
	float _staggerTime = 0;
	float _crtRate = 0;
	float _crtMultplier = 1.5f;

	bool _isDead = false;
};



enum class State
{
	Idle,
	Move,
	Attack,
	Spawn,
	Stagger,
	Die,
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
	virtual void TakeDamage(const DamageInfo& dmg);

	void SetState(State state);
	void SetDir(Dir dir);
	void SetenumAttack(enumAttack attack);

	Dir GetDir() { return _dir; }

	void UpdateAnimation();

	virtual void Reset() override;

protected:
	Info _info;
	State _state = State::Idle;
	Dir _dir = DIR_LEFT;
	enumAttack _attack = START;

	Animator* _aniIdle[2] = {};
	Animator* _aniMove[2] = {};
	Animator* _aniAttack[2] = {};
	Animator* _aniSpawn = {};
	Animator* _aniDie = {};

	AnimationComponent* _ani = nullptr;
};

