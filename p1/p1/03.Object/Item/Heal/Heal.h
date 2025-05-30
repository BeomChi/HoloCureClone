#pragma once
#include "../Item.h"

class Player;
class Sprite;

class Heal : public Item
{
	using Super = GameObject;
public:
	Heal();
	virtual ~Heal() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void AddToHeal(Player* obj);
	virtual void ApplyEffect() override;
private:
	int _expArr[6] = { 5,10,25,50,75,100 };
	int _exp = 0;
	Sprite* _sprites[6] = {};
};

