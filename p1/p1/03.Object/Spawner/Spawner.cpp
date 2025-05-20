#include "../../pch.h"
#include "Spawner.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/ObjectManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/SpawnManager.h"
#include "../../03.Object/ObjectPool/ObjectPool.h"
#include "../../03.Object/Entity/Monster/NormalMonster.h"


Spawner::Spawner()
{
}

Spawner::~Spawner()
{
}

void Spawner::Init()
{
	_spawnMaxCount = GET_SINGLE(SpawnManager)->GetMaxSpawnCount();
	_spawnDelay = GET_SINGLE(SpawnManager)->GetSpawnDelay();
}

void Spawner::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// UI 용 나중에 게임 매니저 만들면 거기로 옮길 것
	_time += deltaTime;

	_sumTime += deltaTime;
	if (_spawnDelay <= _sumTime && GET_SINGLE(SpawnManager)->CheckSpawn())
	{
		int32 x = RandomRange(0, GWinSizeX);
		int32 y = RandomRange(0, GWinSizeY);

		Vec2 pos = GET_SINGLE(SceneManager)->ScreenToWorld({ (float)x,(float)y });

		NormalMonster* monster = GET_SINGLE(ObjectPool)->Get<NormalMonster>(L"NormalMonster");
		monster->SetPos({ pos.x,pos.y });
		GET_SINGLE(ObjectManager)->AddObject(monster);

		_sumTime = 0;
		GET_SINGLE(SpawnManager)->AddCurrentSpawnCount();
	}
}

void Spawner::Render(HDC hdc)
{
	{
		wstring str = std::format(L"현재 스폰된 몬스터({0})", _spawnCount);
		::TextOut(hdc, GWinSizeX / 2, 30, str.c_str(), static_cast<int32>(str.size()));
	}
}
