#pragma once  
#include "../Entity.h"  
#include "Signal.hpp" // Ensure Signal is included  

class Equipment;  
class HpBar;
class EquipmentSelectHud;

class Player : public Entity
{
	using Super = Entity;
public:
	Signal<float, float> OnHpChanged;
	Signal<float, float> OnExpChanged;
	Signal<int32> OnLevelChanged;

	Player();
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	virtual ~Player() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual void TakeDamage(const DamageInfo& dmg) override;

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	void AddExp(int32 exp) { _info._exp += exp; }
	void AddCrtMulty(float crtMulty) { _info._crtMultplier += crtMulty; }
	void RemoveCrtMulty(float crtMulty) { _info._crtMultplier -= crtMulty; }
	void SetMaxExp(int32 maxExp) { _info._maxExp = maxExp; }

	void CheckLevelUpExp();
	void LevelUp();

	void Heal(float heal);

	virtual void Reset() override;

	void SetEquipmentSelectHud(EquipmentSelectHud* hud) { _equipmentSelectUi = hud; }


	bool IsChoosingEquipment() const { return _isChoosingEquipment; }
	void SetChoosingEquipment(bool choosing) { _isChoosingEquipment = choosing; }

	int32 GetCurrentLevel() { return _info._level; }

	float GetItemAbsorbDistance() const { return _absorbDistance; }
	void SetItemAbsorbDistance(float distance) { _absorbDistance = distance; }
private:
	void InputMove(float deltaTime);
	void Idle(float deltaTime);

private:
	float _sumTime = 0;
	float _absorbDistance = 50.f;

	bool _isChoosingEquipment = false;

	EquipmentSelectHud* _equipmentSelectUi = nullptr;

};
