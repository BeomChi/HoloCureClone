#include "pch.h"
#include "ObjectPool.h"
#include "../GameObject.h"
#include "../ObjectFactory.h"
#include "../Entity/Player/Player.h"
#include "../Entity/Monster/Fubura.h"
#include "../Entity/Monster/Shubangelion.h"
#include "../Entity/Monster/NormalMonster.h"
#include "../Projectile/Bullet.h"
#include "../Projectile/Laser.h"
#include "../Projectile/Lava.h"
#include "../Projectile/BLBookObj.h"
#include "../Projectile/EnCurseObj.h"
#include "../Projectile/FanBeamObj.h"
#include "../Projectile/BombExplode.h"
#include "../Projectile/BombObj.h"
#include "../Projectile/Axe.h"
#include "../Projectile/SausageObj.h"
#include "../Projectile/Splash.h"
#include "../Projectile/Stick.h"
#include "../Projectile/StickExplode.h"
#include "../Projectile/TridentObj.h"
#include "../Item/Experinence/ExperinenceObject.h"
#include "../Item/Heal/Heal.h"
#include "../../06.Ui/Game/EquipmentSelectHud.h"
#include "../../06.Ui/Game/DamageText.h"


void ObjectPool::Init()
{

	ReigsterCreator<Bullet>(L"Bullet");


	ReigsterCreator<Fubura>(L"Fubura");
	ReigsterCreator<Shubangelion>(L"Shubangelion");
	ReigsterCreator<NormalMonster>(L"NormalMonster");

	ReigsterCreator<Laser>(L"Laser");
	ReigsterCreator<Lava>(L"Lava");

	ReigsterCreator<BLBookObj>(L"BLBook");
	ReigsterCreator<EnCurseObj>(L"EnCurseObj");
	ReigsterCreator<FanBeamObj>(L"FanBeamObj");
	ReigsterCreator<BombExplode>(L"BombExplode");
	ReigsterCreator<BombObj>(L"BombObj");
	ReigsterCreator<Axe>(L"Axe");
	ReigsterCreator<SausageObj>(L"SausageObj");
	ReigsterCreator<Splash>(L"Splash");
	ReigsterCreator<Stick>(L"Stick");
	ReigsterCreator<StickExplode>(L"StickExplode");
	ReigsterCreator<TridentObj>(L"TridentObj");


	ReigsterCreator<ExperinenceObject>(L"Exp");
	ReigsterCreator<Heal>(L"Heal");
	ReigsterCreator<DamageText>(L"DamageText");

	for (wstring key : {L"Bullet", L"Laser", L"Lava", L"BLBook", L"EnCurseObj", L"FanBeamObj",
		L"BombExplode", L"BombObj", L"Axe", L"SausageObj", L"Splash", L"Stick", L"StickExplode", L"TridentObj"})
	{
		for (int i = 0; i < 3; i++)
		{
			CreateNewObject(key);
		}
	}
	
	for (wstring key : {L"NormalMonster", L"DamageText", L"Heal", L"Exp"})
	{
		for (int i = 0; i < 100; i++)
		{
			CreateNewObject(key);
		}
	}

}

bool ObjectPool::CreateNewObject(wstring key)
{
	auto it = _creators.find(key);

	if (it == _creators.end())
		return false;

	GameObject* obj = it->second();

	if (obj == nullptr)
		return false;

	obj->SetKey(key);
	_objectPool[key].push_back(obj);

	return true;
}

void ObjectPool::Clear()
{
	for (auto& [key, vec] : _objectPool)
	{
		for (GameObject* obj : vec)
		{
			if(obj != nullptr)
				SAFE_DELETE(obj);
		}
		vec.clear();
	}

	_objectPool.clear();
	_creators.clear();
}

void ObjectPool::Debug()
{
	cout << "---------------------------" << endl;
	for (const auto& [key, vec] : _objectPool)
	{
		wcout << L"Key: " << key << L", Count: " << vec.size() << endl;
	}
}
