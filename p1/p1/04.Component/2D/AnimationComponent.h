#pragma once
#include "../Component.h"

class Animator;

class AnimationComponent :    public Component
{
public:
	AnimationComponent();
	virtual ~AnimationComponent() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetAnimation(Animator* ani);
	void Reset();

	int32 CheckAnimation(int32 frame);
	bool CheckCurrentAnimationEnd();

	Animator* GetAnimator() { return _animator; }

private:
	Animator* _animator = nullptr;
	int32 _idx = 0;
	float _sumTime = 0.f;
};

