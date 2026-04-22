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
	_equipmentSelectUi = nullptr;
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
		_ani->SetAnimation(_aniIdle[DIR_RIGHT]);
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
	{
		//CameraComponent* camera = new CameraComponent();
		//AddComponent(camera);
	}

	// 컴포넌트 Init
	Super::Init();

	
}

void Player::Update()
{
	Super::Update();

	if (_state == State::Die)
	{
		_info._isDead = true;
		GET_SINGLE(GameManager)->GameOver();
	}

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_info._isDead)
	{
		if (_ani->CheckCurrentAnimationEnd())
		{
			_isActivity = false;
		}
		return;
	}

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

	cout << this << endl;
	cout << "[DEBUG] TakeDamage 호출됨. HP: " << _info._currentHp << " / " << _info._maxHp << endl;
	cout << "[DEBUG] TakeDamage 호출. this: " << this << endl;
	cout << "[DEBUG] OnHpChanged this 주소: " << &(OnHpChanged) << endl;
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
	_equipmentSelectUi = GET_SINGLE(ObjectPool)->Get<EquipmentSelectHud>(L"EquipmentSelectHud");
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(_equipmentSelectUi);
	
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
	if (input->GetButton(KeyType::D)) { dir.x += 1;	newDir = DIR_RIGHT; }

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


