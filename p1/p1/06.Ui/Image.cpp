#include "pch.h"
#include "Image.h"
#include "../05.Resource/2D/Sprite.h"

Image::Image()
{
	SetLayer(LAYER_UI);
}

Image::~Image()
{
}

void Image::Init()
{
	Super::Init();
}

void Image::Update()
{
	Super::Update();
	
}

void Image::Render(HDC hdc)
{
	
	if (_sprites)
	{
		Vec2Int size = _sprites->GetSize();
		Vec2 scale = GetScale();

		float renderSizeX = (float)size.x * scale.x;
		float renderSizeY = (float)size.y * scale.y;

		::TransparentBlt(hdc,
			(int32)_pos.x - _size.x / 2,
			(int32)_pos.y - _size.y / 2,
			renderSizeX,
			renderSizeY,
			_sprites->GetDC(),
			_sprites->GetPos().x,
			_sprites->GetPos().y,
			_sprites->GetSize().x,
			_sprites->GetSize().y,
			_sprites->GetTransparent());
	}
	else
	{
		Utils::DrawRect(hdc, _pos, _size.x, _size.y);
	}
}

