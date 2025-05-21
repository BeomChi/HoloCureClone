#pragma once
#include "Singleton.h"

enum class StageState
{
	Idle,
	StageStart,
	Spawning,
	BossInComing,
	Boss,
	Clear,


	StargeStateEnd
};


class StageManager : public Singleton<StageManager>
{
	friend class Singleton<StageManager>;
public:
	void Init();
	void Update();

	void StartStage();
	void SetStage(int32 stage) { _currentStage = stage; }
	void SetStageState(StageState state);

	void BossOnDead();

private:
	StageState _state = StageState::Idle;
	float _time = 0.f;
	float _normalMonsterDelayToBossSpawnTime = 0.f;
	float _lastMidleBossSpawnTime = 0.f;

	bool _isSpawnBoss = false;


	int32 _currentStage = 0;
	int32 _spawnMidleBossCount = 0;
};

