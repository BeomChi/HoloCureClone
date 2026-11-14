#include "pch.h"
#include "Animator.h"
//#include "00.MainGame/Game.h"
#include "01.Manager/TimeManager.h"

Animator::Animator() : Super(ComponentType::Animator)
{
}

Animator::~Animator()
{
}

void Animator::Init()
{
}

void Animator::Update()
{
	Animation* animation = GetCurrentAnimation();

	if (animation == nullptr)
		return;

	const Keyframe& keyframe = animation->GetKeyframe(_currentKeyframeIndex);
	
	float deltaTime = TIME->GetDeltaTime();
	_sumTime += deltaTime;

	if (_sumTime >= keyframe.time)
	{
		_currentKeyframeIndex++;

		int32 totalCount = animation->GetKeyframeCount();

		if (_currentKeyframeIndex >= totalCount)
		{
			if (animation->IsLoop())
			{
				_currentKeyframeIndex = 0;
			}
			else
			{
				_currentKeyframeIndex = totalCount - 1;
			}
			_isAnimationEnd = true;
		}

		_sumTime = 0;
	}
}

Animation* Animator::GetCurrentAnimation()
{
	return _currentAnimation;
}

const Keyframe& Animator::GetCurrentKeyframe()
{
	return _currentAnimation->GetKeyframe(_currentKeyframeIndex);
}

void Animator::Reset()
{
	_sumTime = 0;
	_currentKeyframeIndex = 0;
	_isAnimationEnd = false;
}