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


private:
	StageState _state = StageState::Idle;
	float _time = 0.f;
};

