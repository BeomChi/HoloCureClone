#include "../pch.h"
#include "StageManager.h"
#include "TimeManager.h"



void StageManager::Init()
{
}

void StageManager::Update()
{
	_time += GET_SINGLE(TimeManager)->GetDeltaTime();

	switch(_state)
	{
	case StageState::StageStart:
		// 일정 시간 후 일반 몬스터 소환 상태로 전환
		break;
	case StageState::Spawning:
		// 일정 시간 후 중간 보스 하나 소환 카운트 +1 다시 일반 몬스터 소환
		break;
	case StageState::BossInComing:
		// 일정 시간 후 보스 소환 대기 시간이 지난 후 소환 카운트가 충분하면 보스 소환
		break;
	case StageState::Boss:
		// 보스 사망 판정이 뜨면 clear로 전환
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
}
