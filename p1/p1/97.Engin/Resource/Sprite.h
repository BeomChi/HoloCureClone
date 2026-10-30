#pragma once
#include "97.Engin/Resource/ResourceBase.h"

class Texture;

class Sprite :    public ResourceBase
{
	using Super = ResourceBase;
public:
	Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy);
	virtual ~Sprite() override;


	Texture* GetTexture() { return _texture; }

	Vec2 GetPos() const { return _offset; }
	Vec2 GetSize() const { return _size; }
	

	Vec2 GetPivot() { return _pivot; }
	void SetPivot(Vec2 pivot) { _pivot = pivot; }

private:
	Texture* _texture = nullptr;

	Vec2 _pivot = { 0.5f,0.5f };

	Vec2 _offset = { 0.f,0.f };
	Vec2 _size = { 0.f,0.f };
};

