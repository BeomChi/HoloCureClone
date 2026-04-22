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
}

