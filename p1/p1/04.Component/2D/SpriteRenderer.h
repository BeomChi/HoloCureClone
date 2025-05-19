#pragma once
#include "../Component.h"

class Sprite;

class SpriteRenderer :    public Component
{
public:
	SpriteRenderer();
	virtual ~SpriteRenderer() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetSprtie(Sprite* sprite) { _sprite = sprite; }

private:
	Sprite* _sprite = nullptr;
};

