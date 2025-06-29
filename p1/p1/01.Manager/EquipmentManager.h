#pragma once
#include "Singleton.h"


class Equipment;


class EquipmentManager : public Singleton<EquipmentManager>
{
	friend class Singleton<EquipmentManager>;
public:
	virtual ~EquipmentManager() override;

	void UpdateAll();
	void Clear();

	void RemoveObject(Equipment* equip);
	void AddEquiment(Equipment* equip);

	bool HasEquipment(wstring name);


	const vector<Equipment*>& GetGameObjects(int layer) const { return _equipments; }
	
private:
	vector<Equipment*> _equipments;

};
