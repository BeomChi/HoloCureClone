#pragma once
#include "AOE.h"




class Animator;
class AnimationComponent;


class Axe :   public AOE
{
	using Super = AOE;
public:
	Axe();
	virtual ~Axe() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetStartPos(Vec2 pos) { _startPos = pos; }
	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	void SetDir(Vec2 dir) { _dir = dir; }
	virtual void Reset() override;

private:
	Vec2 _dir;

	float _angle = PI;			// 180도 (9시 방향)
	float _angularSpeed = PI;	// 라디안/초
	float _radiusGrowth = 100.f;// 초당 거리 증가
	float _baseRadius = 25.f;   // 시작 반지름

	Vec2 _startPos = {};

	Animator* _animation = nullptr;
	AnimationComponent* _ani = nullptr;
};

