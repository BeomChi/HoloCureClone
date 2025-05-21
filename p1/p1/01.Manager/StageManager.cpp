#include "../pch.h"
#include "StageManager.h"
#include "TimeManager.h"
#include "SpawnManager.h"
#include "ObjectManager.h"



void StageManager::Init()
{
	
}

void StageManager::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	// 스테이니 내에 플레이 타임
	_time += deltaTime;

	switch(_state)
	{
	case StageState::StageStart:
		// 일정 시간 후 일반 몬스터 소환 상태로 전환
		// 스테이지 시작후 5초 스폰 시작
		if (_time >= 5.f)
			SetStageState(StageState::Spawning);
		break;
	case StageState::Spawning:
		// 일정 시간 후 중간 보스 하나 소환 카운트 +1 다시 일반 몬스터 소환
		GET_SINGLE(SpawnManager)->Update();

		if (_time - _lastMidleBossSpawnTime >= 30 && _spawnMidleBossCount < 4)
		{
			//중간 보스 소환
			// 게임 매니저를 통해서 현재 스테이지 값 넘겨주기
			GET_SINGLE(SpawnManager)->SpawnMidleBoss(_currentStage);
			_spawnMidleBossCount++;
			_lastMidleBossSpawnTime = _time;
		}

		if (_spawnMidleBossCount == 4)
		{
			SetStageState(StageState::BossInComing);
		}
		break;
	case StageState::BossInComing:
		// 일정 시간 후 보스 소환 대기 시간이 지난 후 소환 카운트가 충분하면 보스 소환
		// 보스 출현 UI띄우기
		// 일정 시간 후 보스 소환
		if (_isSpawnBoss == false)
		{
			GET_SINGLE(SpawnManager)->SpawnBoss(_currentStage);
			_isSpawnBoss = true;
			SetStageState(StageState::Boss);
		}
		break;
	case StageState::Boss:
		// 소환후 시간이 지난 후 다시 일반 몬스터 소환 시작
		// 보스 사망 판정이 뜨면 clear로 전환

		_normalMonsterDelayToBossSpawnTime += deltaTime;

		if(_normalMonsterDelayToBossSpawnTime >= 30)
			SetStageState(StageState::Spawning);

		break;
	case StageState::Clear:
		// 다음 씬으로 넘어갈 수 있게 하기

		break;
	default:
		break;
	}
}

void StageManager::StartStage()
{
	_state = StageState::StageStart;
	_time = 0;
	_spawnMidleBossCount = 0;
}

void StageManager::SetStageState(StageState state)
{
	if (_state == state)
		return;

	_state = state;
}

void StageManager::BossOnDead()
{
	_state = StageState::Clear;
}
