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


// 착용중이던 장비 해제 및 메모리 정리
void EquipmentManager::Clear()
{
	for (auto equip : _equipments)
	{
		if (equip)
		{
			equip->OnUnequipEffect(*GET_SINGLE(GameManager)->GetPlayer());
			SAFE_DELETE(equip);
		}

	}
	_equipments.clear();
}

// 착용중인 장비 제거
void EquipmentManager::RemoveObject(Equipment* equip)
{
	auto it = find(_equipments.begin(), _equipments.end(), equip);

	if (it == _equipments.end())
		return;

	(*it)->OnUnequipEffect(*GET_SINGLE(GameManager)->GetPlayer());
	SAFE_DELETE(equip);
	_equipments.erase(it);
}

// 장비 착용 및 이미 가지고 있는 장비일 경우 업그레이드
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

// 해당 장비를 가지고 있는지 확인하는 용도
bool EquipmentManager::HasEquipment(wstring name)
{
	for (auto equip : _equipments)
	{
		if (equip->GetName() == name)
			return true;
	}

	return false;
}
