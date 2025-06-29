#include "pch.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "SceneManager.h"


void GameManager::Update()
{
	// 전체 플레이 타임
	_playTime += GET_SINGLE(TimeManager)->GetDeltaTime();
}

