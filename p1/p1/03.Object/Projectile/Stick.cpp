#include "pch.h"
#include "Stick.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../02.Scene/Scene.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../03.Object/Projectile/StickExplode.h"
#include "../../03.Object/ObjectPool/ObjectPool.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/AnimationComponent.h"
#include "../../05.Resource/2D/Animator.h"

Stick::Stick()
{
}

Stick::~Stick()
{
}

void Stick::Init()
{
	_info._speed = 500;

	// component
	{
		{
			_animation = GET_SINGLE(ResourceManager)->GetAnimator(L"Stick");
			_ani = new AnimationComponent();
			_ani->SetAnimation(_animation);

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

void Stick::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	_pos += _info._dir * _info._speed * deltaTime;
	
	Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(_pos);

	if (pos.x <= 0 || pos.y <= 0 ||
		pos.x >= GWinSizeX || pos.y >= GWinSizeY)
	{
		_isActivity = false;
	}
}

void Stick::Render(HDC hdc)
{
	Super::Render(hdc);

	//Utils::DrawCircle(hdc, _pos, _size);
}

void Stick::OnTriggerEnter(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
		//cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
		_info._pierceCount++;


		if (_info._pierceCount >= 2)
		{
			// stickExplode 소환
			StickExplode* stickExplode = GET_SINGLE(ObjectPool)->Get<StickExplode>(L"StickExplode");
			stickExplode->SetPos(_pos);
			stickExplode->SetDamageInfo(_damageInfo);

			GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(stickExplode);
			_isActivity = false;
		}
	}
}

void Stick::OnTriggerExit(Collider* collider, Collider* other)
{
}

void Stick::Reset()
{
	_info._pierceCount = 0;
}




