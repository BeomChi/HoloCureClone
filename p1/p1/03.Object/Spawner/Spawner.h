#pragma once
#include "../GameObject.h"

class Spawner :    public GameObject
{
	using Super = GameObject;
public:
	Spawner();
	virtual ~Spawner() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	float GetTime() { return _time; }

	void SetSpawnMaxCount(int32 count) { _spawnMaxCount = count; }
	int32 GetSpawnCount() { return _spawnCount; }
	void SubSpawnCount() { _spawnCount--; }

private:
	float _time = 0;
	float _spawnDelay = 3;
	float _sumTime = 0;

	int32 _spawnCount = 0;
	int32 _spawnMaxCount = 0;
};

