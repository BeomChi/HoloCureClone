#include "pch.h"
#include "EquipmentManager.h"
#include "GameManager.h"
#include "../03.Object/Item/Equipment/Equipment.h"
#include "../03.Object/Item/Equipment/Weapon/BLBook.h"
#include "../03.Object/Item/Equipment/Weapon/Bomb.h"
#include "../03.Object/Item/Equipment/Weapon/EliteLavaBucket.h"
#include "../03.Object/Item/Equipment/Weapon/EnCurse.h"
#include "../03.Object/Item/Equipment/Weapon/FanBeam.h"
#include "../03.Object/Item/Equipment/Weapon/GlowStick.h"
#include "../03.Object/Item/Equipment/Weapon/PistolShoot.h"
#include "../03.Object/Item/Equipment/Weapon/PsychoAxe.h"
#include "../03.Object/Item/Equipment/Weapon/Sausage.h"
#include "../03.Object/Item/Equipment/Weapon/SpiderCooking.h"
#include "../03.Object/Item/Equipment/Weapon/Trident.h"
#include "../03.Object/Item/Equipment/Weapon/WamyWater.h"
#include "../06.Ui/Game/EquipmentHud.h"


EquipmentManager::~EquipmentManager()
{
	Clear();
}

void EquipmentManager::Init()
{
	// 무기 생성
	{
		{
			BLBook* testWeapon = new BLBook();
			testWeapon->Init();

			_allWeapons.push_back(testWeapon);
		}
		{
			Bomb* testWeapon = new Bomb();
			testWeapon->Init();

			_allWeapons.push_back(testWeapon);
		}
		{
			EliteLavaBucket* testWeapon = new EliteLavaBucket();
			testWeapon->Init();

			_allWeapons.push_back(testWeapon);
		}
		{
			EnCurse* testWeapon = new EnCurse();
			testWeapon->Init();

			_allWeapons.push_back(testWeapon);
		}
		{
			FanBeam* testWeapon = new FanBeam();
			testWeapon->Init();

			_allWeapons.push_back(testWeapon);
		}
		{
			GlowStick* testWeapon = new GlowStick();
			testWeapon->Init();

			_allWeapons.push_back(testWeapon);

		}
		{
			PistolShoot* testWeapon = new PistolShoot();
			testWeapon->Init();

			_allWeapons.push_back(testWeapon);

		}
		{
			PsychoAxe* testWeapon = new PsychoAxe();
			testWeapon->Init();

			_allWeapons.push_back(testWeapon);

		}
		{
			Sausage* testWeapon = new Sausage();
			testWeapon->Init();

			_allWeapons.push_back(testWeapon);

		}
		{
			SpiderCooking* testWeapon = new SpiderCooking();
			testWeapon->Init();

			_allWeapons.push_back(testWeapon);

		}
		{
			Trident* testWeapon = new Trident();
			testWeapon->Init();

			_allWeapons.push_back(testWeapon);
			_equipments[Weapon].push_back(testWeapon);
		}
		{
			WamyWater* testWeapon = new WamyWater();
			testWeapon->Init();

			_allWeapons.push_back(testWeapon);
		}
	}
}

void EquipmentManager::UpdateAll()
{
	for (const vector<Equipment*>& equipObj : _equipments)
		for (Equipment* equip : equipObj)
		{
			if (equip)
				equip->Update(); // 무기 사용 로직 등
		}

}


// 착용중이던 장비 해제 및 메모리 정리
void EquipmentManager::Clear()
{
	for (const vector<Equipment*>& equipObj : _equipments)
		for (Equipment* equip : equipObj)
		{
			if (equip)
			{
				equip->OnUnequipEffect(*GET_SINGLE(GameManager)->GetPlayer());
				//SAFE_DELETE(equip);
			}

		}

	for (int32 i = 0; i < _allWeapons.size(); i++)
		SAFE_DELETE(_allWeapons[i]);

	for (int32 i = 0; i < _allArmors.size(); i++)
		SAFE_DELETE(_allArmors[i]);

	for (int32 i = 0; i < Equip::None; i++)
		_equipments[i].clear();

	_allWeapons.clear();
}


vector<Equipment*> EquipmentManager::GetRandomEquipments()
{

	vector<Equipment*> candidates;

	if (_equipments[0].size() <= 5)
	{
		shuffle(_allWeapons.begin(), _allWeapons.end(), _rng);
		for (auto* eq : _allWeapons)
		{
			if (!eq->IsMaxLevel()) // 최대레벨 아닌 장비만
				candidates.push_back(eq);
		}

	}
	else
	{
		// 6개 선택이 끝났을 경우

		vector<Equipment*> tempList = _equipments[0];
		shuffle(tempList.begin(), tempList.end(), _rng);
		for (auto* eq : tempList)
		{
			if (!eq->IsMaxLevel()) // 최대레벨 아닌 장비만
				candidates.push_back(eq);
		}
	}
	int32 count = min(4, static_cast<int32>(candidates.size()));

	vector<Equipment*> temp;
	for (int32 i = 0; i < count; i++)
	{
		temp.push_back(candidates[i]);
	}

	return temp;
}

// 착용중인 장비 제거
void EquipmentManager::RemoveObject(Equipment* equip)
{
	auto it = find(_equipments[equip->GetType()].begin(), _equipments[equip->GetType()].end(), equip);

	if (it == _equipments[equip->GetType()].end())
		return;

	(*it)->OnUnequipEffect(*GET_SINGLE(GameManager)->GetPlayer());
	_equipments[equip->GetType()].erase(it);

	// 이건 생각을 해보자 근데 콜라보 장비 만들때 재료로 뺄때 어차피 렙업하면 안뜨게 해야하니 리스트에서도 
	// 빼버리는게 맞지 않을까? 겸사겸사 이젠 안쓰는거니 포인터도 정리해버리고
	auto it2 = find(_allWeapons.begin(), _allWeapons.end(), equip);
	if (it2 != _allWeapons.end())
		_allWeapons.erase(it2);

	SAFE_DELETE(equip); // 재료 장비는 더 이상 안 쓰이므로 삭제
}

// 장비 착용 및 이미 가지고 있는 장비일 경우 업그레이드
void EquipmentManager::AddEquiment(Equipment* equip)
{
	if (_equipments[equip->GetType()].size() >= 6) // 장비는 최대 12개까지만 착용 가능
	{
		cout << "무기 및 방어구는 각각 최대 6개까지만 착용할 수 있습니다." << endl;
		return;
	}

	// 이미 가지고 있으면 장비 업글
	if (HasEquipment(equip->GetName()))
	{
		for (const vector<Equipment*>& equipObj : _equipments)
			for (Equipment* eq : equipObj)
			{
				// 같은 이름의 장비가 이미 착용중인 경우 업그레이드
				if (eq->GetName() == equip->GetName())
				{
					eq->UpgradeEquip(*GET_SINGLE(GameManager)->GetPlayer()); // 장비 업그레이드

					// 새로만든 장비 제거
					SAFE_DELETE(equip);
					_equipmentHud->RefreshSlots(); // UI 갱신
					return; // 중복 착용 방지
				}
			}
	}

	cout << equip->GetType() << endl;
	_equipments[equip->GetType()].push_back(equip);
	equip->OnEquipEffect(*GET_SINGLE(GameManager)->GetPlayer());
	_equipmentHud->RefreshSlots(); // UI 갱신
}

void EquipmentManager::UpgreadEquipment(Equipment* equip)
{
	if(equip == nullptr)
		return;

	equip->UpgradeEquip(*GET_SINGLE(GameManager)->GetPlayer()); // 장비 업그레이드

	_equipmentHud->RefreshSlots(); // UI 갱신
}

// 해당 장비를 가지고 있는지 확인하는 용도
bool EquipmentManager::HasEquipment(wstring name)
{
	for (const vector<Equipment*>& equipObj : _equipments)
		for (Equipment* equip : equipObj)
		{
			if (!equip)
				continue;

			wcout << L"[DEBUG] 비교 중: 장비 이름 = " << equip->GetName()
				<< L", 찾는 이름 = " << name << endl;
			if (equip->GetName() == name)
				return true;
		}

	return false;
}