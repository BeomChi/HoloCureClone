#pragma once
#include "../GameObject.h"

struct AOEInfo
{
	float _duration = 0;		// 지속 시간
	float _attackDelay = 1;		// 공격 딜레이

	float _baseScale = 1.f;		// 기본 스케일
	float _scaleMultiple = 1.f; // 스케일 배율
	float _sumTime = 0.f;
	float _time = 0;
};

class Animator;
class AnimationComponent;


class AOE :   public GameObject
{
	using Super = GameObject;
public:
	AOE();
	virtual ~AOE() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	

	void SetScaleMultple(float scale);
	void SetDamageInfo(const DamageInfo& info) { _damageInfo = info; }
	void SetDuration(float duration) { _info._duration = duration; }
	void SetAttackDelay(float delay) { _info._attackDelay = delay; }

	void Knockback(GameObject* obj,GameObject* other, float force);



protected:
	AOEInfo _info;
	DamageInfo _damageInfo;

	vector<Collider*> _collsion;
};

