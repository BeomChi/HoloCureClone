#pragma once
#include "97.Engin/Component/Component.h"

class Sprite;

class SpriteRenderer : public Component
{
	using Super = Component;
public:
	SpriteRenderer();
	virtual ~SpriteRenderer() override;

	virtual void Init() override;
	virtual void Update() override;
	//virtual void Render(HDC hdc) override;

	void SetSprite(Sprite* sprite) { _sprite = sprite; }
	Sprite* GetSprite() { return _sprite; }

private:
	Sprite* _sprite = nullptr;
};

