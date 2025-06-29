#include "pch.h"
#include "Player.h"
#include "../../../01.Manager/InputManager.h"
#include "../../../01.Manager/TimeManager.h"
#include "../../../01.Manager/ObjectManager.h"
#include "../../../01.Manager/ResourceManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../01.Manager/CollisionManager.h"
#include "../../Projectile/Bullet.h"
#include "../../ObjectPool/ObjectPool.h"
#include "../../Item/Equipment/Equipment.h"
#include "../../../04.Component/Collision/BoxCollider.h"
#include "../../../04.Component/Camera/CameraComponent.h"
#include "../../../04.Component/2D/AnimationComponent.h"
#include "../../../05.Resource/2D/Animator.h"

Player::Player()
{
	_aniIdle[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Gura_IdleLeft");
	_aniIdle[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"Gura_IdleRight");
	_aniMove[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"GuraMoveLeft");
	_aniMove[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"GuraMoveRight");
	_aniDie = GET_SINGLE(ResourceManager)->GetAnimator(L"PlayerDie");
}

Player::~Player()
{
}

void Player::Init()
{
	// 플레이어 초기화
	_info._currentHp = 65.f;
	_info._maxHp = _info._currentHp;
	_info._atk = 5.f;
	_info._speed = 200.f;
	_info._maxExp = 10;


	_entityType = EntityType::Player;
	_firePosLength = 50.f;
	
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
		boxCollider->SetShowDebug(true);
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

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	_sumTime += deltaTime;

	if (_info._isDead)
	{
		SetState(State::Die);
		if (_ani->CheckCurrentAnimationEnd())
		{
			_isActivity = false;
		}
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

	//UpdateEquipments();
	//Attack(deltaTime);

}

void Player::Render(HDC hdc)
{
	Super::Render(hdc);
	{
		Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(_pos);
		wstring str = std::format(L"Player :({0})", _info._currentHp);
		::TextOut(hdc, pos.x, pos.y - _size.y, str.c_str(), static_cast<int32>(str.size()));
	}
	
	//Utils::DrawRect(hdc, _pos, 50, 50);

	Utils::DrawLine(hdc, GET_SINGLE(SceneManager)->WorldToScreen(_pos), 
			GET_SINGLE(SceneManager)->WorldToScreen(GetFirePos()));
}

Vec2 Player::GetFirePos()
{
	Vector firePos = _pos;
	Vector dir = GetMousePosToPlayerDir();


	firePos += dir * _firePosLength;

	return firePos;
}

Vec2 Player::GetMousePosToPlayerDir()
{
	POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vec2 Pos = GET_SINGLE(SceneManager)->ScreenToWorld(mousePos);
	Vector firePos = _pos;

	float dirX = Pos.x - _pos.x;
	float dirY = Pos.y - _pos.y;

	Vector dir = { dirX,dirY };
	dir.Normalize();

	return dir;
}

void Player::OnTriggerEnter(Collider* collider, Collider* other)
{
}

void Player::OnTriggerExit(Collider* collider, Collider* other)
{
}

void Player::CheckLevelUpExp()
{
	while (_info._exp >= _info._maxExp)
	{
		LevelUp();
	}
}

void Player::LevelUp()
{
	_info._level++;
	_info._exp -= _info._maxExp;
	_info._maxExp = static_cast<int32>(_info._maxExp * 1.2f);
	_info._maxHp = static_cast<int32>(_info._maxHp * 1.2f);
	_info._atk = static_cast<int32>(_info._atk * 1.2f);
	_info._currentHp = _info._maxHp;

	cout << "현재 최대 경험치 : " << _info._maxExp << endl;
	cout << "현재 최대 체력 : " << _info._maxHp << endl;
	cout << "현재 공격력 : " << _info._atk << endl;

	// UI 갱신

	// 무기나 방어구 강화창
}

void Player::Heal(float heal)
{
	_info._currentHp += heal;

	if (_info._currentHp > _info._maxHp)
		_info._currentHp = _info._maxHp;
}

void Player::Reset()
{
}

//void Player::AddEquiment(Equipment* equip)
//{
//	_equipments.push_back(equip);
//	equip->OnEquipEffect(*this);
//}
//
//void Player::UpdateEquipments()
//{
//	for (auto equip : _equipments)
//	{
//		if (equip)
//			equip->Update(); // 무기 사용 로직 등
//	}
//}



void Player::InputMove(float deltaTime)
{
	auto input = GET_SINGLE(InputManager);
	Vector dir = { 0,0 };

	if (input->GetButton(KeyType::W))
	{
		dir.y -= 1;
	}
	if (input->GetButton(KeyType::S))
	{
		dir.y += 1;
	}
	if (input->GetButton(KeyType::A))
	{
		dir.x -= 1;
		SetDir(DIR_LEFT);
	}
	if (input->GetButton(KeyType::D))
	{
		dir.x += 1;
		SetDir(DIR_RIGHT);
	}

	if (dir.x == 0 && dir.y == 0)
	{
		SetState(State::Idle);
		return;
	}

	dir.Normalize();
	_pos += dir * _info._speed * deltaTime;
}

void Player::Idle(float deltaTime)
{
	auto input = GET_SINGLE(InputManager);
	Vector dir = { 0,0 };

	if (input->GetButton(KeyType::W))
	{
		dir.y -= 1;
	}
	if (input->GetButton(KeyType::S))
	{
		dir.y += 1;
	}
	if (input->GetButton(KeyType::A))
	{
		dir.x -= 1;
		SetDir(DIR_LEFT);
	}
	if (input->GetButton(KeyType::D))
	{
		dir.x += 1;
		SetDir(DIR_RIGHT);
	}

	if (dir.x != 0 || dir.y != 0)
	{
		SetState(State::Move);
	}
}

void Player::Attack(float deltaTime)
{
	if (_sumTime - _lastAttackTime >=_attackDelayTime )
	{
		Bullet* bullet = GET_SINGLE(ObjectPool)->Get<Bullet>(L"Bullet");
		if (bullet == nullptr)
		{
			OutputDebugString(L"Bullet is nullptr!\n");
		}
		else
		{
			bullet->SetPos(GetFirePos());
			bullet->SetDir(GetMousePosToPlayerDir());
			bullet->SetDmg(_info._atk);
			GET_SINGLE(ObjectManager)->AddObject(bullet);
		}

		_lastAttackTime = _sumTime;
	}
}
