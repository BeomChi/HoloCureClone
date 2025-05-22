#pragma once
#include "../Entity.h"





class Player : public Entity
{
	using Super = Entity;
public:
	Player();
	virtual ~Player() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;



	void SetFirePosLength(float length) { _firePosLength = length; }
	Vec2 GetFirePos();
	Vec2 GetMousePosToPlayerDir();

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	void AddExp(float exp) { _info._exp += exp; }
	void SetMaxExp(float maxExp) { _info._maxExp = maxExp; }

	void CheckLevelUpExp();
	void LevelUp();

	virtual void Reset() override;
	
private:
	void InputMove(float deltaTime);
	void Idle(float deltaTime);
	void Attack(float deltaTime);


private:
	float _firePosLength = 0;
	float _attackDelayTime = 2;
	float _lastAttackTime = 0;
	float _sumTime = 0;
};

