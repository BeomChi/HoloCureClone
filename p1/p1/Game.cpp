#include "pch.h"
#include "00.MainGame/Game.h"
#include "01.Manager/CollisionManager.h"
#include "01.Manager/EquipmentManager.h"
#include "01.Manager/GameManager.h"
#include "01.Manager/InputManager.h"
#include "01.Manager/TimeManager.h"
#include "01.Manager/SceneManager.h"
#include "01.Manager/ResourceManager.h"
#include "01.Manager/SpawnManager.h"
#include "01.Manager/StageManager.h"
#include "01.Manager/SoundManager.h"
#include "01.Manager/UiLayoutManager.h"
#include "03.Object/ObjectPool/ObjectPool.h"


//TODO 
//게임 매니저	
//역할 : 씬 전환, UI 갱신, 저장 / 로드 연동 포인트 등.
// 일단 플레이어는 저장할 필요가 없음
// 굳이 저장을 한다면 도감이나 캐릭터 해방 정도를 저장해야할듯
// 
// 
//보스 추가
//그 보스가 죽었는지 스테이지 매니저에서 판단해야 하기 때문.
// 현재 중간 보스 밖에 없기에 보스 만들기
// 
// 랜덤으로 나오는 상자 및 강화 모루 추가하기
// 
// UI 작업하기
// 플레이어 관련, 게임 시작화면 관련, 장비, 피격시 데미지 표시
// 
// UI 작업하기 전에 하자
// 
// 
//인벤토리가 어느 정도 작동한 뒤 연동해서 마무리.
// 장판기 같은 지속적으로 딜을 하는 설치기들 데미지 주기 건들여야함
// 일반 장비 끝나면 레벨업시 장비 강화하는 시스템 추가하기
// 강화 모루에 접근시 인벤토리 내에 있는 아이템 +1 강 하는 기능 넣기


Game::Game()
{

}

Game::~Game()
{
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ObjectPool)->Clear();
	GET_SINGLE(ResourceManager)->Clear();

	TimeManager::DestroyInstance();
	InputManager::DestroyInstance();
	GameManager::DestroyInstance();
	SceneManager::DestroyInstance();
	ObjectPool::DestroyInstance();
	ResourceManager::DestroyInstance();
	SpawnManager::DestroyInstance();
	StageManager::DestroyInstance();
	EquipmentManager::DestroyInstance();
	CollisionManager::DestroyInstance();
	SoundManager::DestroyInstance();
	UiLayoutManager::DestroyInstance();

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

	AllocConsole(); // 콘솔 생성
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);  // 표준 출력 연결
	freopen_s(&fp, "CONIN$", "r", stdin);    // 표준 입력 연결
	freopen_s(&fp, "CONOUT$", "w", stderr);  // 표준 에러 연결

	cout.clear();  // iostream 상태 초기화
	cin.clear();
	cerr.clear();

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SoundManager)->Init(hwnd);
	GET_SINGLE(ResourceManager)->Init(hwnd, fs::path(L"D:\\gitHub\\C++_WinApi\\HoloCureClone\\p1\\Resource"));
	GET_SINGLE(SceneManager)->Init();



	GET_SINGLE(GameManager)->SetState(GameState::Playing);
	GET_SINGLE(SceneManager)->ChangeScene(SceneType::StartScene);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(GameManager)->Update();
	GET_SINGLE(SceneManager)->Update();

}

void Game::Render()
{
	GET_SINGLE(SceneManager)->Render(hdcBack);


	uint32 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();


	//TODO define
	/*{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(hdcBack, 20, 480, str.c_str(), static_cast<int32>(str.size()));
	}*/
	
	{
		wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		::TextOut(hdc, GWinSizeX - 180, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	// Double Buffering
	::BitBlt(hdc, 0, 0, _rect.right, _rect.bottom, hdcBack, 0, 0, SRCCOPY); // 비트 블릿 : 고속 복사
	::PatBlt(hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
