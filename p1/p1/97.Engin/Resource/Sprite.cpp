#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy)	
	: Super(ResourceType::Sprite)
{
	_texture = texture;
	_offset.x = x;
	_offset.y = y;
	_size.x = cx;
	_size.y = cy;
}

Sprite::~Sprite()
{
}




