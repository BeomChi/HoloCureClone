#pragma once
#include "../ResourceBase.h"

class Texture;

class Sprite :    public ResourceBase
{
public:
	Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy);
	virtual ~Sprite() override;

	HDC GetDC();
	int32 GetTransparent();

	Vec2Int GetPos() const { return Vec2Int{ _x,_y }; }
	Vec2Int GetSize() const { return Vec2Int{ _cx,_cy }; }
	

	Vec2 GetPivot() { return _pivot; }
	void SetPivot(Vec2 pivot) { _pivot = pivot; }

private:
	Texture* _texture = nullptr;

	Vec2 _pivot = { 0.5f,0.5f };

	int32 _x = 0;
	int32 _y = 0;
	int32 _cx = 0;
	int32 _cy = 0;
};

