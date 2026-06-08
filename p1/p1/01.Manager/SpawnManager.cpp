#include "pch.h"
#include "SpawnManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "../02.Scene/Scene.h"
#include "../03.Object/Spawner/Spawner.h"

void SpawnManager::Init()
{
	for (int32 i = 0; i < 20; i++)
		AddSpawner();

	_maxSpawnCount = 500;
}

void SpawnManager::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_sumTime += deltaTime;
	if (_spawnDelay <= _sumTime)
	{
		for (int i = 0; i < _spawners.size(); i++)
		{
			if (_currentSpawnCount < _maxSpawnCount && _spawners.size() >= 1)
			{
				_spawners[i]->NormalMonsterSpawn();

			}
		}
		_sumTime = 0;
	}
}

void SpawnManager::Render(HDC hdc)
{
	/*{
		wstring str = std::format(L"현재 스폰된 몬스터({0})", _currentSpawnCount);
		::TextOut(hdc, GWinSizeX / 2, 30, str.c_str(), static_cast<int32>(str.size()));
	}*/
}

void SpawnManager::SpawnMidleBoss(int32 Stage)
{
	if (_spawners.size() == 0)
		return;

	_spawners[0]->SpawnMidleBoss(Stage);
}

void SpawnManager::SpawnBoss(int32 Stage)
{
	if (_spawners.size() == 0)
		return;

	_spawners[0]->SpawnBoss(Stage);
}

void SpawnManager::SetSpawnStage(int32 maxCount, int32 spawnDelay)
{
	_maxSpawnCount = maxCount;
	_spawnDelay = spawnDelay;
}

void SpawnManager::AddSpawner()
{
	Spawner* spawner = new Spawner();
	_spawners.push_back(spawner);

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(spawner);
}
