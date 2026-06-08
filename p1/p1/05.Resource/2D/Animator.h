#pragma once
#include "../ResourceBase.h"

class Texture;

struct AnimationInfo
{
	Texture* texture = nullptr;
	wstring name;

	Vec2Int size = {};

	int32 start = 0;
	int32 end = 0;
	int32 line = 0;

	// 기초 동안 재생
	float duration = 1.f;
	
	bool loop = true;
};

class Animator :   public ResourceBase
{
public:
	Animator();
	virtual ~Animator() override;

	void SetInfo(const AnimationInfo& info) { _info = info; }
	const AnimationInfo& GetInfo() const { return _info; }

	Vec2 GetPivot() { return _pivot; }
	void SetPivot(Vec2 pivot) { _pivot = pivot; }

private:
	AnimationInfo _info;
	Vec2 _pivot = { 0.5f,0.5f };
};

