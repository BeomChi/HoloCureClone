#pragma once
#include "Ui.h"

class Sprite;

class Image : public Ui
{
	using Super = Ui;
public:
	Image();
	virtual ~Image() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	
	Sprite* GetSprite() { return _sprites; }

	void SetSprite(Sprite* sprite) { _sprites = sprite; }


protected:
	Sprite* _sprites = nullptr;


	float _sumTime = 0;
};

