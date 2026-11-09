#pragma once
#include "97.Engin/Resource/ResourceBase.h"

class Texture;

struct SpriteInfo
{
	Vec2 offset = { 0.f,0.f };
	Vec2 size = { 0.f,0.f };
	Vec2 pivot = { 0.5f,0.5f };
};

class Sprite :    public ResourceBase
{
	using Super = ResourceBase;
public:
	Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy);
	virtual ~Sprite() override;


	Texture* GetTexture() { return _texture; }

	Vec2 GetOffset() const { return _info.offset; }
	Vec2 GetSize() const { return _info.size; }

	SpriteInfo& GetInfo() { return _info; }
	

	Vec2 GetPivot() { return _info.pivot; }
	void SetPivot(Vec2 pivot) { _info.pivot = pivot; }

private:
	Texture* _texture = nullptr;

	SpriteInfo _info;
};

