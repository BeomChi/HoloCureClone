#include "../../pch.h"
#include "SpriteRenderer.h"
#include "../../05.Resource/2D/Sprite.h"
#include "../../01.Manager/SceneManager.h"
#include "../../03.Object/GameObject.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Init()
{
}

void SpriteRenderer::Update()
{
}

void SpriteRenderer::Render(HDC hdc)
{
	if (_sprite == nullptr)
		return;

	Vec2Int size = _sprite->GetSize();
	Vec2 pos = _owner->GetPos();
	Vec2 scale = _owner->GetScale();

	float renderSizeX = (float)size.x * scale.x;
	float renderSizeY = (float)size.y * scale.y;

	Vec2 screenPos = GET_SINGLE(SceneManager)->WorldToScreen(pos);

	screenPos.x -= _sprite->GetPivot().x * renderSizeX;
	screenPos.y -= _sprite->GetPivot().y * renderSizeY;

	::TransparentBlt(hdc,
		(int32)screenPos.x,
		(int32)screenPos.y,
		renderSizeY,
		renderSizeY,
		_sprite->GetDC(),
		_sprite->GetPos().x,
		_sprite->GetPos().y,
		_sprite->GetSize().x,
		_sprite->GetSize().y,
		_sprite->GetTransparent());
}
