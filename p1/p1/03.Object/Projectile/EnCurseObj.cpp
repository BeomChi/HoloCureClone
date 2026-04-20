#include "pch.h"
#include "EnCurseObj.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../02.Scene/Scene.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../05.Resource/2D/Animator.h"

EnCurseObj::EnCurseObj()
{
}

EnCurseObj::~EnCurseObj()
{
}

void EnCurseObj::Init()
{
	_info._speed = 500;

	// component
	{
		{
			_dirAni[DIR_LEFT] = GET_SINGLE(ResourceManager)->GetAnimator(L"EnCurseLeft");
			_dirAni[DIR_RIGHT] = GET_SINGLE(ResourceManager)->GetAnimator(L"EnCurseRight");

			_ani = new AnimationComponent();
			_ani->SetAnimation(_dirAni[DIR_LEFT]);

			Vec2Int size = _ani->GetAnimator()->GetInfo().size;
			SetSize({ (float)size.x , (float)size.y });


			AddComponent(_ani);
		}
		// collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize(_renderSize);
			collider->SetShowDebug(false);
			AddComponent(collider);
			SetCollider(collider);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
		}
		
	}
	Super::Init();
}

void EnCurseObj::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	if (_target == nullptr)
	{


		if (_dir == DirState::Right)
		{
			_pos.x += _info._speed * deltaTime;
		}
		else
		{
			_pos.x -= _info._speed * deltaTime;
		}

	}
	else
	{
		Vec2 targetPos = _target->GetPos();
		Vec2 dir = targetPos - _pos;

		float distance = dir.Length();

		if (distance > 0)
		{
			dir.Normalize();
			_pos += dir * _info._speed * deltaTime;
		}
	}



	Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(_pos);
	if (pos.x <= 0 || pos.y <= 0 ||
		pos.x >= GWinSizeX || pos.y >= GWinSizeY)
	{
		_isActivity = false;
	}
}

void EnCurseObj::Render(HDC hdc)
{
	Super::Render(hdc);

	//Utils::DrawCircle(hdc, _pos, _size);
}

void EnCurseObj::OnTriggerEnter(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		if (_isAbility)
		{
			// 체인 데미지 증가
			_damageInfo._finalDamage += _damageInfo._finalDamage * _transition_Damage_Increase_Rate;
			cout << "체인 데미지 증가 : " << _damageInfo._finalDamage << endl;
		}

		// 추적중이고 타겟이 충돌체랑 같을 경우
		if (_isTracking && _target == other->GetOwner() && _target->GetIsActivity())
		{
			static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
			_target = nullptr; // 타겟 초기화
			_isTracking = false;
			cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
		}
		else if (!_isTracking) // 추적중이 아니면
		{
			static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
			cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
		}


		// 타겟이 업고 체인이 안되면 비활성화
		// 체인시 씬에서 오브젝트 레이어를 가져온 다음
		// 현재 충돌한 오브젝트를 제외하고
		// 체인 거리 내에 있는 몬스터를 타겟으로 설정
		if (_target == nullptr)
		{
			float random = rand() % 100;
			if (random < _transition_Probability)
			{
				for (GameObject* obj : GET_SINGLE(SceneManager)->GetCurrentScene()->GetGameObjects(LAYER_OBJECT))
				{
					if (obj == nullptr || !obj->GetIsActivity())
						continue;

					if (obj->GetEntityType() != EntityType::Monster)
						continue;

					if (obj == other->GetOwner())
						continue; // 현재 충돌한 오브젝트는 제외

					Vec2 targetPos = obj->GetPos();
					Vec2 dir = targetPos - _pos;

					float distance = dir.Length();
					if (distance <= _transition_Range)
					{
						//if (distance < (_target->GetPos() - _pos).Length())
						{
							_target = obj;
							_isTracking = true;
						}
					}
				}
			}
			else
				_isActivity = false;
		}
		
	}
}



void EnCurseObj::Reset()
{
	_damageInfo._finalDamage = 0;
	_target = nullptr;
}

void EnCurseObj::SetState(DirState dir)
{
	if (_dir == dir)
		return;

	_dir = dir;
	UpdateAnimation();
}

void EnCurseObj::UpdateAnimation()
{
	switch (_dir)
	{
	case DirState::Left:
		_ani->SetAnimation(_dirAni[DIR_LEFT]);
		break;
	case DirState::Right:
		_ani->SetAnimation(_dirAni[DIR_RIGHT]);
		break;
	}
}
