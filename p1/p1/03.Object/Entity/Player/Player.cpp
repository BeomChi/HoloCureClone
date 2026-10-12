#include "pch.h"
#include "Player.h"
#include "../../../01.Manager/InputManager.h"
#include "../../../01.Manager/TimeManager.h"
#include "../../../01.Manager/ResourceManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../01.Manager/CollisionManager.h"
#include "../../../01.Manager/GameManager.h"
#include "../../../02.Scene/Scene.h"
#include "../../Projectile/Bullet.h"
#include "../../ObjectPool/ObjectPool.h"
#include "../../Item/Equipment/Equipment.h"
#include "../../../04.Component/Collision/BoxCollider.h"
#include "../../../04.Component/Camera/CameraComponent.h"
#include "../../../04.Component/2D/AnimationComponent.h"
#include "../../../05.Resource/2D/Animator.h"
#include "../../../05.Resource/2D/Sprite.h"
#include "../../../06.Ui/Game/HpBar.h"
#include "../../../06.Ui/Game/EquipmentSelectHud.h"
#include "../../../06.Ui/Image.h"

Player::Player()
{
	_aniIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Gura_IdleLeft");
	_aniIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Gura_IdleRight");
	_aniMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"GuraMoveLeft");
	_aniMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"GuraMoveRight");
	_aniDie = GET_SINGLE(ResourceManager)->GetAnimator(L"PlayerDie");
	cout << "[DEBUG] 플레이어 생성. this: " << this << endl;
}

Player::~Player()
{
	//_equipmentSelectUi = nullptr;
	cout << "[DEBUG] 플레이어 소멸. this: " << this << endl;
}

void Player::Init()
{
	// 플레이어 초기화
	_info._currentHp = 65.f;
	_info._maxHp = _info._currentHp;
	_info._atk = 10.f;
	_info._speed = 200.f;
	_info._exp = 0;
	_info._maxExp = 10;
	_info._dmgMultiplier = 1.3f;


	_entityType = EntityType::Player;
	_dir = DIR_RIGHT;
	
	// 플레이어에 들어갈 컴포넌트
	{
		_ani = new AnimationComponent();
		_ani->SetAnimation(_aniIdle[_dir]);
		Vec2Int size = _ani->GetAnimator()->GetInfo().size;

		SetSize({ (float)size.x, (float)size.y });

		
		AddComponent(_ani);
	}
	{
		BoxCollider* boxCollider = new BoxCollider();
		boxCollider->SetSize({ _renderSize.x / 2,_renderSize.y });
		boxCollider->SetShowDebug(false);
		AddComponent(boxCollider);
		SetCollider(boxCollider);

		GET_SINGLE(CollisionManager)->AddCollider(boxCollider);
	}
	/*{
		CameraComponent* camera = new CameraComponent();
		AddComponent(camera);
	}*/

	// 컴포넌트 Init
	Super::Init();

	
}

void Player::Update()
{
	Super::Update();

	if (_state == State::Die)
	{
		//_isActivity = false;
		GET_SINGLE(GameManager)->GameOver();
		return;
	}

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;


	switch (_state)
	{
	case State::Idle:
		Idle(deltaTime);
		break;
	case State::Move:
		InputMove(deltaTime);
		break;
	}


	_pos += _velocity * deltaTime;

	// 이동 후 속도 감소 (마찰 같은 느낌)
	_velocity *= 0.9f; // or 0.8f, 자연 감속

	//UpdateEquipments();
	//Attack(deltaTime);

}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
	//cout << "Player Render: " << this << endl;
	//Utils::DrawCircle(hdc, GET_SINGLE(SceneManager)->WorldToScreen(_pos), 10);

	/*{
		Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(_pos);
		wstring str = std::format(L"Player :({0})", _info._currentHp);
		::TextOut(hdc, pos.x, pos.y - _size.y, str.c_str(), static_cast<int32>(str.size()));
	}*/
	
	//Utils::DrawRect(hdc, _pos, 50, 50);

	/*Utils::DrawLine(hdc, GET_SINGLE(SceneManager)->WorldToScreen(_pos), 
			GET_SINGLE(SceneManager)->WorldToScreen(GetFirePos()));*/
}

void Player::TakeDamage(const DamageInfo& dmg)
{
	Super::TakeDamage(dmg);

	//cout << this << endl;
	//cout << "[DEBUG] TakeDamage 호출됨. HP: " << _info._currentHp << " / " << _info._maxHp << endl;
	//cout << "[DEBUG] TakeDamage 호출. this: " << this << endl;
	//cout << "[DEBUG] OnHpChanged this 주소: " << &(OnHpChanged) << endl;
	OnHpChanged(_info._currentHp, _info._maxHp);
}



void Player::OnTriggerEnter(Collider* collider, Collider* other)
{
}

void Player::OnTriggerExit(Collider* collider, Collider* other)
{
}

void Player::CheckLevelUpExp()
{
	if (_info._exp >= _info._maxExp)
	{
		LevelUp();  // 하나만 처리
	}

	OnExpChanged(_info._exp, _info._maxExp);
}

void Player::LevelUp()
{
	if (_isChoosingEquipment)
		return;

	GET_SINGLE(GameManager)->SetState(GameState::Paused);

	_info._level++;
	_info._exp -= _info._maxExp;
	_info._maxExp = static_cast<int32>(_info._maxExp * 1.5f);
	_info._currentHp = _info._maxHp;

	_isChoosingEquipment = true;

	// UI 갱신
	OnLevelChanged(_info._level);

	// 시그널 방식과 비교를 위해 현재 착용 중인 장비는 
	// 시그널이 아닌 기존에 플레이어가 들고 사용하는 방식으로 구현
	// 구조 개편으로 인해 ui 풀에서 가져오지 않고 직접 활성화하는 방법으로
	//_equipmentSelectUi = GET_SINGLE(ObjectPool)->Get<EquipmentSelectHud>(L"EquipmentSelectHud");
	//GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(_equipmentSelectUi);
	//_equipmentSelectUi->SetIsActivity(true);
	//_equipmentSelectUi->Reset();
	OnEquipmentSelectHud(true);
	
}

void Player::Heal(float heal)
{
	_info._currentHp += heal;

	if (_info._currentHp > _info._maxHp)
		_info._currentHp = _info._maxHp;

	OnHpChanged(_info._currentHp, _info._maxHp);
}

void Player::Reset()
{
	SetState(State::Idle);
}


void Player::InputMove(float deltaTime)
{
	auto input = GET_SINGLE(InputManager);
	Vector dir = { 0,0 };
	Dir newDir = _dir;

	if (input->GetButton(KeyType::W)) { dir.y -= 1; }
	if (input->GetButton(KeyType::S)) { dir.y += 1; }
	if (input->GetButton(KeyType::A)) { dir.x -= 1;		newDir = DIR_LEFT; }
	if (input->GetButton(KeyType::D)) { dir.x += 1;		newDir = DIR_RIGHT; }

	if (dir.x == 0 && dir.y == 0) { SetState(State::Idle);		return; }

	SetDir(newDir);
	dir.Normalize();
	_velocity = dir * _info._speed;
}

void Player::Idle(float deltaTime)
{
	auto input = GET_SINGLE(InputManager);
	Vector dir = { 0,0 };

	if (input->GetButton(KeyType::W)) { dir.y -= 1; }
	if (input->GetButton(KeyType::S)) { dir.y += 1; }
	if (input->GetButton(KeyType::A)) { dir.x -= 1;	SetDir(DIR_LEFT); }
	if (input->GetButton(KeyType::D)) { dir.x += 1;	SetDir(DIR_RIGHT); }

	if (dir.x != 0 || dir.y != 0)
	{
		SetState(State::Move);
	}
}


// 2026 04 27
// 오늘 한 것 : 게임 오버 데이터 정리(ui 연결 해놓음), 업데이트 구조 개선(추가,업데이트,삭제 다 끝난 후 씬전환 체크)
// 문제 : 씬 전환 시 현재 씬이 업데이트가 돌고 있는 상태에서 씬전환이 이루어져 이미 죽은 포인터에 접근하는 문제
//		  그리고 플레이어 애니메이션이 2개가 동시에 출력되는 상태
// 해결 : 씬 전환을 즉시 전환이 아닌 예약을 걸어놓고 그 프레임 업데이트가 끝난 후 씬 전환이 되도록 변경
//		 그리고 플레이어 애니메이션이 2개가 동시 출력되는 문제는 플레이어 Init이 두번 호출되어 생긴 문제
//	  씬 오브젝트 풀에 등록이 되어 있는 객체들은 생성시 Init을 호출하게끔 되어 있었는데
//    플레이어도 풀에 등록이 되어있어서 생성될 때 Init이 호출이 되었는데, 씬이 플레이어 객체를 생성할 떄도
//    Init 호출하여 두번 호출이 되는 상황이 발생했던 것,그래서 플레이어를 풀에서 제거
//    하지만 지금 구조적으로 ui를 제외한 오브젝트들은 비활성화 시  씬에서 제거하고 풀에 들어가는 구조로 되어 있어
//    이 부분을 어떻게 할지 고민 중


// 2026 04 28
// 오늘 한 것 : 디버그 모드가 아닌 릴리즈 모드로 실행해서 지금까지 만든게 문제가 없는지 확인 및 어제 만든 게임오버 테스트
// 문제 : 현재 버튼 이미지랑 게임오버 ui 배경 이미지가 없어 임시로 대충 생길 위치에 배치
// 
// 해결 : 내일 이미지를 구하든 만들든 해서 교체하기
//

// 2026 04 29
// 오늘 한 것 : ui 이미지 구해서 교체하고 교체된 이미지 임시로 위치 잡아서 배치하기
// 문제 : 툴에서 bmp로 저장한 이미지가 로드가 되지 않는 문제가 발생
//			프로세스를 닫았는데도 계속해서 프로세스가 실행중이라서 디버깅이 안되는 문제 발생
// 해결 : 그림판으로 이미지를 저장하니 해결이 되었는 그 이유가 툴에서 저장한 이미지 파일 포멧이랑
// 			그림판에서 저장한 이미지 파일 포멧이 달라서 그런 것 같음, 
//		그리고 프로세스 문제는 작업관리자에서 프로세스 종료를 해줄려고 했으니 보이지가 않아 컴퓨터를 껐다가 키는 방향으로
//		해결할려고 했는데 하기가 싫어져서 끄고 자버림
//

// 2026 04 30
// 오늘 한 것 : 하루 종일 놀았다
// 문제 : 뭔가 정신이 나갈거 같아서
// 
// 해결 : 아무것도 생각안하고 놀았다
//

// 2026 05 01
// 오늘 한 것 : 에디터 씬을 만들고 그 안에서 오브젝트 선택 기능과 이동 기능을 만들었다.
// 문제 : ui 배치하는 작업이 너무 노가다에다가 위치를 임시로 집어넣고 실행시킨 다음에 마우스 위치랑 현재 위치를 보고
// 대략적으로 조정하는 방식으로 매번 실행시키고 수정하는 방식이 너무 비효율적이어서 툴?을 제작하기로 결심
// 
// 해결 : 씬을 만들고 그 안에서 오브젝트 선택 기능과 패널에 있는 것만 간섭이 가능하게끔 만들었다
//

// 2026 05 03
// 오늘 한 것 : 일단 임시로 uiLayoutManager를 만들고 저장과 로드 기능을 만들었다. 이걸로 ui 배치가 좀더 수월해질것이며 이걸 좀더 확장해서 파일 입출력 시스템을 구축하자
// 문제 : pch에 있는 메모리 누수를 찾기 위한 defin new 가 json 내에 있는 걸 싹다 바꿔버려서 오류가 다량으로 터지는 상황 발생
// 
// 
// 해결 : 일단 임시로 pch에 있는 new를 주석처리해서	json 내에 있는 new가 사용되도록 해서 일단 컴파일이 되게끔 했는데, 이 부분은 좀더 고민해봐야할듯
// 
//

// 2026 05 04
// 오늘 한 것 : ui 레이아웃 매니저에서 save와 load 기능이 문제없이 작동하는 것을 확인했고 이제 이걸 좀 더 확장해서 ui 뿐만 아니라 맵 오브젝트 배치도 가능하게 되었다. 이론적으로
// 문제 : json의 파일 포맷이 wstring을 지원하지 않아 파일에는 name에 []로 저장되는 상황 발생 
//			그리고 obj->GetKey()가 해서 string으로 변환이 안되고 it에 문제가 발생하는 일이 생김
// 
// 
// 해결 : string음 임시로 선언해서 거기에 저장하는 방식으로 해결
//		  wstring으로 일단 GetKey()를 받고 이 받은걸 토대로 string으로 변환해서 json에 저장하는 방식으로 해결
// 
//

// 2026 05 05
// 오늘 한 것 : 패널의 render에서 출력하던 문자들을 Text라는 클래스로 빼서 출력하도록 변경
// 문제 : 크기가 감이 안와 크게 잡았더니 실제 보이는 문자 크기보다 선택되는 범위가 넓은 문제가 발생
//			
// 
// 
// 해결 : 기본 크기를 줄이고 입려 받은 폰트 크기에 맞게끔 크기를 조정하는 방식으로 해결
//

// 2026 05 07
// 오늘 한 것 : GameOverHud에 타이틀로 돌아가는 버튼이 보이지 않는 문제가 발생
// 문제 : GameOverHud에 타이틀로 돌아가는 버튼이 보이지 않는 문제가 발생, 
// json 파일에는 키랑 좌표 값이 들어가 있지만 화면에는 보이지 않는 문제가 발생하여 디버깅 시작
// 해결 : 버튼은 다른 ui들이랑 달리 크기가 자동으로 설정되지 않는 문제를 발견 이를 임시로 수동으로 설정하였고
//        이왕 확인하는 김에 다른 것들고 확인
// 하지만 스프라이트가 생성될때 크기랑 다 설정을 하는데 버튼만 이상하게 크기가 0,0 으로 설정이 되어 있음
// 이유를 알았다.스프라이트 내에는 잘 들어가 있지만 오브젝트에는 스프라이트의 크기가 전달되지않아
// 이떄까지 다른 오브젝트들고 다 SetSize로 스프라이트 크기를 받아와 설정을 하는 것이었다.
// 예전에 만들었던 부분이라 까먹고 있었네

// 2026 05 08
// 오늘 한 것 : 아직 아무것도 안함 자고 일어나서 할 예정 일거리(영상을 찍었을떄 데미지 출력이 안되어 밋밋해서 이거까지만 추가)
//  나머지 장비의 입출력 시스템은 영상촬영 후 문서 정리하면서 시작
// 어차피 장비 내부 입출력은 게임 영상에 안보이는 부분이고 어차피 지금 클래스에 깡으로 박혀있던거에서
// 파일을 읽어와서 저장하는 방식으로 바뀌는 거니 영상 촬영에는 영향이 없을 것 같아서 일단 데미지 출력 시스템만 추가할 예정
// 문제 : 
//			
// 
// 
// 해결 : 
//

// 2026 05 9 ~ 11
// 한 것 : 데미지를 화면에 출력, ui 누락 현상 및 글자 깨짐 현상, 데미지가 자유분방하게 날라 댕김
// 문제 : 월드 좌표와 화면 좌표가 상이하고 제대로 구분하지 않아 문제가 발생, ui는 불러오는데는 문제가 없었지만 왠지 모르겠지만 하나가 자꾸 사라짐
// 
// 해결 : ui는 사라진 애를 좌표를 임의 화면에 보이는 곳에 설정한 다음에 에딧모드에서 다시 저장을 해주니 해결이 됨
// 텍스트의 월드좌표와 화면 좌표 분리를 좀 더 고민을 해봐야 할거 같음 지금 당장은 DamageText만 따로 Super::Render(hdc)를 호출하는게 아닌
// 스스로 렌더하는 방식으로 변경
//

// 2026 05 12 ~ 14
// 한 것 : 영상 촬영을 위해 릴리즈 모드로 디버깅 시작
// 문제 : 디버그 모드일때 없던 각종 버그 발생장비가 업그레이드가 안되는 문제가 발생 
// 해결 : ui 데이터가 갱신이 안된다거나 플레이어랑 연결하는 부분이 에딧모드에서 작업한다고 주석친 걸 해제하는 걸로 해결
//  AddObject 쪽에서 if 조건이 잘못되어 있어서 수정
// 
// 내일 할거 : 영상 찍고 자막 달고 문서 작업 시작하기 재미없는 작업이 시작되는 구먼
//