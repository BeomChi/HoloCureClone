#pragma once
#include "../Item.h"

class Player;
class Sprite;
class SpriteRenderer;

class ExperinenceObject : public Item
{
	using Super = GameObject;
public:
	ExperinenceObject();
	virtual ~ExperinenceObject() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void AddToExp(Player* obj);
	virtual void ApplyEffect() override;
	virtual void Reset() override;

private:
	int _expArr[6] = { 5,10,25,50,75,100 };
	int _exp = 0;
	Sprite* _sprites[6] = {};
	SpriteRenderer* _sprite;
};

