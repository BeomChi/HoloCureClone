#include "pch.h"
#include "GameManager.h"
#include "TimeManager.h"
#include "SceneManager.h"


void GameManager::Update()
{
	// 전체 플레이 타임
	_playTime += GET_SINGLE(TimeManager)->GetDeltaTime();
}

void GameManager::GameOver()
{
	SetState(GameState::GameOver);

	// 게임 오버 시 필요한 추가 로직을 여기에 작성
	// 일단 추가 할거 게임 오버 ui
	// ui 에다가 현재 스테이지 킬수, 레벨, 생존 시간
	// 그리고 밑에 버튼을 누르면 메인 메뉴로 나가게 하기

	// 일단 메인 화면으로 빼면서 메모리가 세거나 하는 문제가 있는지 확인해보자

	// 음 플레이 상태 중일때 말고 이제 타이틀 상태일때도 좀 제외를 시키는게 좋겠지?

	OnGameOverHudActivity(true);
}

