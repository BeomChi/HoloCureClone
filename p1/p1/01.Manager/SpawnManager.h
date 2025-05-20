#pragma once
#include "Singleton.h"

class SpawnManager : public Singleton<SpawnManager>
{
	friend class Singleton<SpawnManager>;
public:
	void SetSpawnStage(int32 maxCount,int32 spawnDelay);

	void SetMaxSpawnCount(int32 Count) { _maxSpawnCount = Count; }
	int32 GetMaxSpawnCount() const { return _maxSpawnCount; }

	void AddCurrentSpawnCount() { _currentSpawnCount++; }
	void SubCurrentSpawnCount() { _currentSpawnCount--; }

	bool CheckSpawn() { return _currentSpawnCount < _maxSpawnCount; }

	void SetSpawnDelay(int32 delay) { _spawnDelay = delay; }
	int32 GetSpawnDelay() const { return _spawnDelay; }

	void ResetCurrentSpawnCount() { _currentSpawnCount = 0; }

private:
	int32 _maxSpawnCount = 0;
	int32 _currentSpawnCount = 0;
	int32 _spawnDelay = 0;
};

