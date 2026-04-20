#pragma once
#include "Projectile.h"




class Animator;
class AnimationComponent;


class EnCurseObj :   public Projectile
{
	using Super = Projectile;
public:
	EnCurseObj();
	virtual ~EnCurseObj() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;


	void SetTransitionProbability(float probability) { _transition_Probability = probability; }
	void SetTransitionRange(int32 range) { _transition_Range = range; }
	void SetTransitionDamageIncreaseRate(float rate) { _transition_Damage_Increase_Rate = rate; }
	void SetIsAbility(bool isAbility) { _isAbility = isAbility; }

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;

	virtual void Reset() override;

	void SetState(DirState dir);
	void UpdateAnimation();
private:
	GameObject* _target = nullptr; // 타겟 오브젝트 (적)
	DirState _dir;

	Animator* _dirAni[2] = {};
	AnimationComponent* _ani = nullptr;

	bool _isAbility = false; // 능력 사용 여부
	bool _isTracking = false; // 타겟 추적 여부

	int32 _transition_Range = 100;	// 체인 거리
	float _transition_Probability = 20.f;			// 체인 확률
	float _transition_Damage_Increase_Rate = 0.f;
};

