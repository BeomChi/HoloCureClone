#pragma once
#include "97.Engin/Component/Component.h"
#include "97.Engin/Resource/Animation.h"

class Animation;

class Animator :  public Component
{
	using Super = Component;
public:
	Animator();
	virtual ~Animator();

	void Init();
	void Update();

	Animation* GetCurrentAnimation();
	const Keyframe& GetCurrentKeyframe();

	void SetAnimation(Animation* animation) { _currentAnimation = animation; }

private:
	float _sumTime = 0.f;

	int32 _currentKeyframeIndex = 0;
	Animation* _currentAnimation;
};

