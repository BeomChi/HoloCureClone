#include "pch.h"
#include "00.MainGame/Game.h"
#include "01.Manager/TimeManager.h"
#include "01.Manager/InputManager.h"
#include "01.Manager/SceneManager.h"
#include "01.Manager/ObjectManager.h"
#include "01.Manager/ResourceManager.h"
#include "01.Manager/GameManager.h"
#include "03.Object/ObjectPool/ObjectPool.h"


//TODO 
//스테이지 매니저 
//역할 : 스폰 조건 체크, 클리어 조건 체크, 보스 소환 타이밍 관리 등.
// 스테이지 흐름 확정하고 중간 보스 소환 시간과 보스 소환시간 정하기
// 게임 매니저 추가시 추가로 해야될 작업하기
// 
//스폰 매니저 완?
// 
// 수정 됨
//역할 : 여러 스포너 관리, 몬스터 수 제한, 스폰 주기 제어.
// 현재는 스포너에서 조건 검사를 하고 있지만 매니저에서 조건 검사하고 스포너는 소환만
// 하게 하기
// 
//게임 매니저
//역할 : 씬 전환, UI 갱신, 저장 / 로드 연동 포인트 등.
// 플레이어 추가해서 어디서든 플레이어 접근이 가능하게하기
// 
//보스 추가
//그 보스가 죽었는지 스테이지 매니저에서 판단해야 하기 때문.
// 현재 중간 보스 밖에 없기에 보스 만들기
// 
//경험치, 체력 회복 등의 필드 드랍템 추가
//드랍 조건은 몬스터가 죽을 때 연동 가능함.
// 랜덤으로 나오는 상자 및 강화 모루 추가하기
// 
//인벤토리 시스템 추가
//역할 : 장비, 소비 아이템, 드랍 아이템 처리 준비.
// 
//장비 시스템 추가
//인벤토리가 어느 정도 작동한 뒤 연동해서 마무리.
// 강화 모루에 접근시 인벤토리 내에 있는 아이템 +1 강 하는 기능 넣기


Game::Game()
{

}

Game::~Game()
{
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ObjectManager)->Clear();
	GET_SINGLE(ObjectPool)->Clear();
	GET_SINGLE(ResourceManager)->Clear();

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
	GET_SINGLE(ResourceManager)->Init(hwnd, fs::path(L"D:\\gitHub\\C++_WinApi\\HoloCureClone\\p1\\Resource"));
	GET_SINGLE(SceneManager)->Init();




	GET_SINGLE(SceneManager)->ChangeScnee(SceneType::StartScene);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->Update();
	GET_SINGLE(GameManager)->Update();

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
