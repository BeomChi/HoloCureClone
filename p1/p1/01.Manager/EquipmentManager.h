#pragma once
#include "Singleton.h"


class Equipment;
class EquipmentHud;

class EquipmentManager : public Singleton<EquipmentManager>
{
	friend class Singleton<EquipmentManager>;
public:
	virtual ~EquipmentManager() override;

	void Init();
	void UpdateAll();
	void Clear();

	// 랜덤으로 4개 장비를 뽑아옴
	vector<Equipment*> GetRandomEquipments();

	void RemoveObject(Equipment* equip);
	void AddEquiment(Equipment* equip);
	void SetEquipmentHud(EquipmentHud* equipmentHud) { _equipmentHud = equipmentHud; }
	void UpgreadEquipment(Equipment* equip);

	bool HasEquipment(wstring name);
	
	const vector<Equipment*>& GetGameObjects(int type) const { return _equipments[type]; }
	

private:
	vector<Equipment*> _equipments[2];	// 착용중인 장비 (여기에 있는건 삭제 x) : 착용해제시 remove 호출
	vector<Equipment*> _allWeapons;		// 모든 무기 소유 (여기서 삭제)
	vector<Equipment*> _allArmors;		// 모든 방어구 소유 (여기서 삭제)

	EquipmentHud* _equipmentHud = nullptr; // 장비 UI 핸들러


	mt19937 _rng
	{ 
		random_device{}() 
	};
};
