#pragma once
#include "Singleton.h"

class Spawner;

class SpawnManager : public Singleton<SpawnManager>
{
	friend class Singleton<SpawnManager>;
public:
	void Init();
	void Update();
	void Render(HDC hdc);

	void SpawnMidleBoss(int32 Stage);
	void SpawnBoss(int32 Stage);

	void SetSpawnStage(int32 maxCount,int32 spawnDelay);

	void SetMaxSpawnCount(int32 Count) { _maxSpawnCount = Count; }
	int32 GetMaxSpawnCount() const { return _maxSpawnCount; }

	void AddCurrentSpawnCount() { _currentSpawnCount++; }
	void SubCurrentSpawnCount() { _currentSpawnCount--; }

	bool CheckSpawn() { return _currentSpawnCount < _maxSpawnCount; }

	void SetSpawnDelay(float delay) { _spawnDelay = delay; }
	float GetSpawnDelay() const { return _spawnDelay; }

	void ResetCurrentSpawnCount() { _currentSpawnCount = 0; }

	void AddSpawner();

private:
	int32 _maxSpawnCount = 0;
	int32 _currentSpawnCount = 0;
	float _spawnDelay = 3;
	float _sumTime = 0;

	vector<Spawner*> _spawners;
};

