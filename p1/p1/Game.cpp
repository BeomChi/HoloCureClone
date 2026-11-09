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
#include "01.Manager/RenderManager.h"
#include "03.Object/ObjectPool/ObjectPool.h"


// TODO 인강보고 DirectX11 내 구조에 맞춰서 넣어보기 시작하기

// TODO 매니저 중들 싱글톤 해제 및 game에 모으기
// 일부 매니저들은 각 씬이 들고 있게하기
// 그 목록
// SpawnManager, StageManager, UiLayoutManager, CollisionManager
// 이 4개는 각 씬에서 관리하는 방향으로
// ObjectPool은 좀 더 고민이 필요
// 이건 다렉으로 업글후 마저 작업하는 걸로

Game* GGame = nullptr;

Game::Game()
{

}

Game::~Game()
{
	// scene에 남아있는 짜바리 선 정리
	_equipmentManager->Clear();


	_sceneManager->Clear();
	GET_SINGLE(ObjectPool)->Clear();
	_resourceManager->Clear();

	SAFE_DELETE(_equipmentManager);
	SAFE_DELETE(_sceneManager);

	SAFE_DELETE(_soundManager);
	SAFE_DELETE(_resourceManager);
	SAFE_DELETE(_renderManager);

	SAFE_DELETE(_gameManager);
	SAFE_DELETE(_timeManager);
	SAFE_DELETE(_inputManager);

	SAFE_DELETE(_graphics);

	ObjectPool::DestroyInstance();
	SpawnManager::DestroyInstance();
	StageManager::DestroyInstance();
	CollisionManager::DestroyInstance();

	_CrtDumpMemoryLeaks();
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	hdc = ::GetDC(hwnd);

	_graphics = new Graphics(hwnd);

	//::GetClientRect(hwnd, &_rect);

	//hdcBack = ::CreateCompatibleDC(hdc); // hdc와 호환되는 DC를 생성
	//_bmpBack = ::CreateCompatibleBitmap(hdc, _rect.right, _rect.bottom); // hdc와 호환되는 비트맵 생성
	//HBITMAP prev = (HBITMAP)::SelectObject(hdcBack, _bmpBack); // DC와 BMP를 연결
	//::DeleteObject(prev);

#ifdef _DEBUG
	AllocConsole(); // 콘솔 생성
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);  // 표준 출력 연결
	freopen_s(&fp, "CONIN$", "r", stdin);    // 표준 입력 연결
	freopen_s(&fp, "CONOUT$", "w", stderr);  // 표준 에러 연결

	cout.clear();  // iostream 상태 초기화
	cin.clear();
	cerr.clear();
#endif

#ifdef _DEBUG
	fs::path resourcePath = L"../Resource";
#else
	fs::path resourcePath = L"./Resource";
#endif

	_timeManager = new TimeManager();
	_timeManager->Init();

	_inputManager = new InputManager();
	_inputManager->Init(hwnd);

	_resourceManager = new ResourceManager(_graphics->GetDevice());
	_resourceManager->Init(hwnd, resourcePath);

	_renderManager = new RenderManager(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_renderManager->Init();

	_soundManager = new SoundManager();
	_soundManager->Init(hwnd);

	_sceneManager = new SceneManager(_graphics);
	_sceneManager->Init();

	_gameManager = new GameManager();
	_gameManager->SetState(GameState::Playing);

	_equipmentManager = new EquipmentManager();
	//_equipmentManager->Init();

	SCENE->ChangeScene(SceneType::StartScene);
}

void Game::Update()
{
	TIME->Update();
	INPUT->Update();
	GAMEMANAGER->Update();
	SCENE->Update();

}

void Game::Render()
{
	//SCENE->Render(hdcBack);

	RENDER->Update(_graphics);


#ifdef _DEBUG

	/*uint32 fps = TIME->GetFps();
	float deltaTime = TIME->GetDeltaTime();*/


	//
	/*{
		POINT mousePos = INPUT->GetMousePos();
		wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(hdcBack, 20, 480, str.c_str(), static_cast<int32>(str.size()));
	}*/
	
	{
		/*wstring str = std::format(L"FPS({0}), DT({1})", fps, deltaTime);
		Utils::DrawText(hdcBack, Vector{ GWinSizeX - 180, 10 }, str);*/
		//::TextOut(hdc, GWinSizeX - 180, 10, str.c_str(), static_cast<int32>(str.size()));
	}
#endif
	// Double Buffering
	//::BitBlt(hdc, 0, 0, _rect.right, _rect.bottom, hdcBack, 0, 0, SRCCOPY); // 비트 블릿 : 고속 복사
	//::PatBlt(hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS);
}
