#include "../pch.h"
#include "SpawnManager.h"

void SpawnManager::SetSpawnStage(int32 maxCount, int32 spawnDelay)
{
	_maxSpawnCount = maxCount;
	_spawnDelay = spawnDelay;
}
