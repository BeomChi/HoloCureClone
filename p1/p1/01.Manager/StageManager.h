#pragma once
#include "Singleton.h"
#include "Signal.hpp"

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
	Signal<int32> OnKillCountChanged;
	Signal<int32> OnCoinCountChanged;
	Signal<int32> OnTimeChanged;
	void Init();
	void Update();

	void StartStage();
	void SetStage(int32 stage) { _currentStage = stage; }
	void SetStageState(StageState state);
	void SetClear(bool clear) { _isClear = clear; }

	void BossOnDead();
	void PlusMonsterDieCount() 
	{
		_countMontersDie++; 
		OnKillCountChanged(_countMontersDie);
	}
	void PlusCoin(int32 coin)
	{ 
		_cureentCoin += coin; 
		OnCoinCountChanged(_cureentCoin);
	}

	float GetTime() const { return _time; }
private:
	StageState _state = StageState::Idle;
	float _time = 0.f;
	float _normalMonsterDelayToBossSpawnTime = 0.f;
	float _lastMidleBossSpawnTime = 0.f;

	bool _isSpawnBoss = false;
	bool _isClear = false;

	int32 _cureentCoin = 0;
	int32 _countMontersDie = 0;
	int32 _currentStage = 0;
	int32 _spawnMidleBossCount = 0;
};

