#include "../pch.h"
#include "GameManager.h"
#include "TimeManager.h"


void GameManager::Update()
{
	_playTime += GET_SINGLE(TimeManager)->GetDeltaTime();
}
