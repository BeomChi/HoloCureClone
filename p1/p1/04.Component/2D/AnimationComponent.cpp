#include "pch.h"
#include "AnimationComponent.h"
#include "../../05.Resource/2D/Animator.h"
#include "../../05.Resource/2D/Texture.h"
#include "../../05.Resource/2D/Sprite.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../03.Object/GameObject.h"

AnimationComponent::AnimationComponent()
{
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::Init()
{
}

void AnimationComponent::Update()
{
	if (_animator == nullptr)
		return;

	const AnimationInfo& info = _animator->GetInfo();

	if (info.loop == false && _idx == info.end)
		return;

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_sumTime += deltaTime;

	int32 frameCount = (info.end - info.start + 1);

	float delta = info.duration / frameCount;

	if (_sumTime >= delta)
	{
		_sumTime = 0.f;
		_idx = (_idx + 1) % frameCount;
	}
}

void AnimationComponent::Render(HDC hdc)
{
	if (_animator == nullptr)
	{
		OutputDebugString(L"animator is nullptr!\n");
		return;
	}

	

	const AnimationInfo& info = _animator->GetInfo();
	Vec2 pos = _owner->GetPos();
	Vec2 size = _owner->GetSize();
	Vec2 renderSize = _owner->GetRenderSize();

	// 화면 좌표 구하기
	Vec2 screenPos = GET_SINGLE(SceneManager)->WorldToScreen(pos);

	screenPos.x -= _animator->GetPivot().x * renderSize.x;
	screenPos.y -= _animator->GetPivot().y * renderSize.y;

	//screenPos.x -= size.x / 2;
	//screenPos.y -= size.y / 2;

	int frameIdx = _idx - info.start;
	int srcX = frameIdx * info.size.x;
	int srcY = info.line * info.size.y;

	::TransparentBlt(
		hdc,
		(int32)screenPos.x,
		(int32)screenPos.y,
		renderSize.x,
		renderSize.y,
		info.texture->GetDC(),
		srcX,
		srcY,
		info.size.x,
		info.size.y,
		info.texture->GetTransparent()
	);
	
}

void AnimationComponent::SetAnimation(Animator* ani)
{
	if (_animator && _animator == ani)
		return;
	
	_animator = ani;
	Reset();
}

void AnimationComponent::Reset()
{
	_sumTime = 0.f;
	_idx = 0;
}

int32 AnimationComponent::CheckAnimation(int32 frame)
{
	return _idx == frame;
}

bool AnimationComponent::CheckCurrentAnimationEnd()
{
	return _idx == _animator->GetInfo().end;
}
