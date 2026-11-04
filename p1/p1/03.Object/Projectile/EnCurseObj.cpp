#include "pch.h"
#include "EnCurseObj.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../02.Scene/Scene.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "97.Engin/Component/Animation/Animator.h"
#include "97.Engin/Resource/Animation.h"

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
			_dirAni[DIR_LEFT] = RESOURCE->Get<Animation>(L"EnCurseLeft");
			_dirAni[DIR_RIGHT] = RESOURCE->Get<Animation>(L"EnCurseRight");

			_ani = new Animator();
			_ani->SetAnimation(_dirAni[DIR_LEFT]);

			//Vec2Int size = _ani->GetAnimator()->GetInfo().size;
			//SetSize({ (float)size.x , (float)size.y });


			AddComponent(_ani);
		}
		// collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize(_ani->GetCurrentAnimation()->GetKeyframe(0).size);;
			collider->SetShowDebug(false);
			AddComponent(collider);
			//SetCollider(collider);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
		}
		
	}
	Super::Init();
}

void EnCurseObj::Update()
{
	Super::Update();

	float deltaTime = TIME->GetDeltaTime();
	Vec3 pos = GetTransform()->GetPosition();
	if (_target == nullptr)
	{
		if (_dir == DirState::Right)
		{
			pos.x += _info._speed * deltaTime;
		}
		else
		{
			pos.x -= _info._speed * deltaTime;
		}
		// 왜 자꾸 제자리에서 안사라지고 있는거지
		// 추적중인 놈이 죽어서 사라지니 이놈 제자리 걸음하네
		_trackingTime += deltaTime;
	}
	else
	{
		Vec3 targetPos = _target->GetTransform()->GetPosition();
		Vec3 dir = targetPos - pos;

		float distance = dir.Length();

		if (distance > 0)
		{
			dir.Normalize();
			pos += dir * _info._speed * deltaTime;
		}
	}

	GetTransform()->SetPosition(pos);
	/*if (!_target->GetIsActivity())
	{
		_target = nullptr;
	}*/
	

	pos = SCENE->WorldToScreen(Vec2(pos.x,pos.y));
	if (pos.x <= 0 || pos.y <= 0 ||
		pos.x >= GWinSizeX || pos.y >= GWinSizeY ||
		_trackingTime >= 10.f)
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
	if (other->GetGameObject()->GetEntityType() == EntityType::Monster)
	{
		if (_isAbility)
		{
			// 체인 데미지 증가
			_damageInfo._finalDamage += _damageInfo._finalDamage * _transition_Damage_Increase_Rate;
			//cout << "체인 데미지 증가 : " << _damageInfo._finalDamage << endl;
		}

		// 추적중이고 타겟이 충돌체랑 같을 경우
		if (_isTracking && _target == other->GetGameObject() && _target->GetIsActivity())
		{
			static_cast<Entity*>(other->GetGameObject())->TakeDamage(_damageInfo);
			_target = nullptr; // 타겟 초기화
			_isTracking = false;
			//cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
		}
		else if (!_isTracking) // 추적중이 아니면
		{
			static_cast<Entity*>(other->GetGameObject())->TakeDamage(_damageInfo);
			//cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
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
				for (GameObject* obj : SCENE->GetCurrentScene()->GetGameObjects(LAYER_OBJECT))
				{
					if (obj == nullptr || !obj->GetIsActivity())
						continue;

					if (obj->GetEntityType() != EntityType::Monster)
						continue;

					if (obj == other->GetGameObject())
						continue; // 현재 충돌한 오브젝트는 제외

					Vec3 targetPos = obj->GetTransform()->GetPosition();
					Vec3 dir = targetPos - GetTransform()->GetPosition();

					float distance = dir.Length();
					if (distance <= _transition_Range)
					{

						_target = obj;
						_isTracking = true;

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
	_trackingTime = 0.f;
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
