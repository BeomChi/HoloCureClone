#pragma once
#include "../GameObject.h"

class Player;

enum class ItemType
{
	Exp,
	Heal,
	Equipment
};


class Item :    public GameObject
{
	using Super = GameObject;
public:
	Item();
	virtual ~Item() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	
	void SetPlayer(Player* player) { _player = player; }

	ItemType GetItemType() const { return _itemType; }

	void MoveTo(GameObject* obj);
	virtual void Reset() override;

	virtual void ApplyEffect() abstract;

protected:
	ItemType _itemType;
	Player* _player = nullptr;

	float _moveSpeed = 100.f;
	float _absorbDistance = 5.f;
};

