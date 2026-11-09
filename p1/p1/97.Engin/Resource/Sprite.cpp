#include "pch.h"
#include "Sprite.h"
#include "Texture.h"

Sprite::Sprite(Texture* texture, int32 x, int32 y, int32 cx, int32 cy)	
	: Super(ResourceType::Sprite)
{
	_texture = texture;
	_info.offset.x = x;
	_info.offset.y = y;
	_info.size.x = cx;
	_info.size.y = cy;
}

Sprite::~Sprite()
{
}




