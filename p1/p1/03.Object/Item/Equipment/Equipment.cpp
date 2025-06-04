#include "../../../pch.h"
#include "Equipment.h"

Equipment::Equipment()
{
	_itemType = ItemType::Equipment;
}

Equipment::~Equipment()
{
}

void Equipment::Init()
{
	Super::Init();
}

void Equipment::Update()
{
	Super::Update();
}

void Equipment::Render(HDC hdc)
{
	Super::Render(hdc);
}


void Equipment::SetEquipInfo(const EquipInfo& info)
{
	_info._count = info._count;
	_info._level = 1;
	_info._maxLevel = info._maxLevel;
	_info._dmg = info._dmg;
}

void Equipment::ResetEquipInfo()
{
	_info._level = 1;
	_info._maxLevel = 0;
	_info._count = 1;
	_info._dmg = 0;

	_info._range = 1;
	_info._dmg = 0;
	_info._delay = 0;
	_info._coolTime = 0;
}

void Equipment::UpgradeEquip(Player& player)
{
	_info._level++;

	OnEquipEffect(player);
}
