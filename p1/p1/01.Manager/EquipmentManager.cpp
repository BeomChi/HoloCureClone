#include "pch.h"
#include "EquipmentManager.h"
#include "GameManager.h"
#include "../03.Object/Item/Equipment/Equipment.h"


EquipmentManager::~EquipmentManager()
{
	Clear();
}

void EquipmentManager::UpdateAll()
{
	for (auto equip : _equipments)
	{
		if (equip)
			equip->Update(); // 무기 사용 로직 등
	}
	
}



void EquipmentManager::Clear()
{
	for (auto equip : _equipments)
	{
		if (equip)
			equip->OnUnequipEffect(*GET_SINGLE(GameManager)->GetPlayer());
	}
	_equipments.clear();
}

void EquipmentManager::RemoveObject(Equipment* equip)
{
	auto it = find(_equipments.begin(), _equipments.end(), equip);

	if (it == _equipments.end())
		return;

	(*it)->OnUnequipEffect(*GET_SINGLE(GameManager)->GetPlayer());
	_equipments.erase(it);
}

void EquipmentManager::AddEquiment(Equipment* equip)
{
	// 이미 가지고 있으면 장비 업글
	if (HasEquipment(equip->GetName()))
	{
		equip->UpgradeEquip(*GET_SINGLE(GameManager)->GetPlayer());
		return;
	}

	_equipments.push_back(equip);
	equip->OnEquipEffect(*GET_SINGLE(GameManager)->GetPlayer());
}

bool EquipmentManager::HasEquipment(wstring name)
{
	for (auto equip : _equipments)
	{
		if (equip->GetName() == name)
			return true;
	}

	return false;
}
