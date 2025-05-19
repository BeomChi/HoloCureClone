#include "../pch.h"
#include "Game.h"
#include "01.Manager/TimeManager.h"
#include "01.Manager/InputManager.h"
#include "01.Manager/SceneManager.h"
#include "01.Manager/ObjectManager.h"
#include "03.Object/ObjectPool/ObjectPool.h"


//TODO 
// 몬스터 만들기
// 일반 몹
// 특수 개체
// 보스
// 
// 스포너 만들기
// 스프라이트 렌더러 만들기
// UI 작업할떄 렌더 레이어 같이하기

Game::Game()
{

}

Game::~Game()
{
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ObjectManager)->Clear();
	GET_SINGLE(ObjectPool)->Clear();

	_CrtDumpMemoryLeaks();
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	hdcBack = ::CreateCompatibleDC(hdc); // hdc와 호환되는 DC를 생성
	_bmpBack = ::CreateCompatibleBitmap(hdc, _rect.right, _rect.bottom); // hdc와 호환되는 비트맵 생성
	HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack); // DC와 BMP를 연결
	::DeleteObject(prev);

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();




	GET_SINGLE(SceneManager)->ChangeScnee(SceneType::DevScene);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->Update();
}

void Game::Render()
{
	GET_SINGLE(SceneManager)->Render(hdcBack);
	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		::TextOut(hdc, GWinSizeX - 180, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	// Double Buffering
	::BitBlt(hdc, 0, 0, _rect.right, _rect.bottom, hdcBack, 0, 0, SRCCOPY); // 비트 블릿 : 고속 복사
	::PatBlt(hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
