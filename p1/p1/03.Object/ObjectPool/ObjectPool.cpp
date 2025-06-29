#include "pch.h"
#include "ObjectPool.h"
#include "../GameObject.h"
#include "../ObjectFactory.h"
#include "../Entity/Player/Player.h"
#include "../Projectile/Bullet.h"
#include "../Entity/Monster/Fubura.h"
#include "../Entity/Monster/Shubangelion.h"
#include "../Entity/Monster/NormalMonster.h"
#include "../Projectile/Laser.h"
#include "../Projectile/Lava.h"
#include "../Projectile/BLBookObj.h"
#include "../Projectile/EnCurseObj.h"
#include "../Item/Experinence/ExperinenceObject.h"
#include "../Item/Heal/Heal.h"


void ObjectPool::Init()
{
	ReigsterCreator<Player>(L"Player");
	CreateNewObject(L"Player");

	ReigsterCreator<Bullet>(L"Bullet");


	ReigsterCreator<Fubura>(L"Fubura");
	ReigsterCreator<Shubangelion>(L"Shubangelion");
	ReigsterCreator<NormalMonster>(L"NormalMonster");

	ReigsterCreator<Laser>(L"Laser");
	ReigsterCreator<Lava>(L"Lava");

	ReigsterCreator<BLBookObj>(L"BLBook");
	ReigsterCreator<EnCurseObj>(L"EnCurseObj");

	ReigsterCreator<ExperinenceObject>(L"Exp");
	ReigsterCreator<Heal>(L"Heal");

	

}

void ObjectPool::CreateNewObject(wstring key)
{
	auto it = _creators.find(key);

	if (it == _creators.end())
		return;

	GameObject* obj = it->second();
	obj->SetKey(key);

	_objectPool[key].push_back(obj);
}

void ObjectPool::Clear()
{
	for (auto& [key, vec] : _objectPool)
	{
		for (GameObject* obj : vec)
		{
			SAFE_DELETE(obj);
		}
		vec.clear();
	}

	_objectPool.clear();
	_creators.clear();
}
