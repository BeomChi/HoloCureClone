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
#include "97.Engin/Component/Animation/Animator.h"
#include "97.Engin/Resource/Animation.h"

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
			_animation = RESOURCE->Get<Animation>(L"Stick");
			_ani = new Animator();
			_ani->SetAnimation(_animation);

			//Vec2Int size = _ani->GetAnimator()->GetInfo().size;
			//SetSize({ (float)size.x , (float)size.y });


			AddComponent(_ani);
		}
		// collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize(_ani->GetCurrentAnimation()->GetKeyframe(0).size);
			collider->SetShowDebug(false);
			AddComponent(collider);
			//SetCollider(collider);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
		}
		
	}
	Super::Init();
}

void Stick::Update()
{
	Super::Update();

	float deltaTime = TIME->GetDeltaTime();

	Vec3 pos = GetTransform()->GetPosition();
	pos += _info._dir * _info._speed * deltaTime;
	
	GetTransform()->SetPosition(pos);

	// 그럼 순서가 중요하겠네
	// 일단 위치설정하고 그 다음에 이게 화면 밖으로 나갔는지 체크하는게 맞겠지?
	pos = SCENE->WorldToScreen(Vec2(pos.x,pos.y));


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
	if (other->GetGameObject()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetGameObject())->TakeDamage(_damageInfo);
		//cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
		_currentPierceCount++;

		// stickExplode 소환
		StickExplode* stickExplode = GET_SINGLE(ObjectPool)->Get<StickExplode>(L"StickExplode");
		stickExplode->GetTransform()->SetPosition(GetTransform()->GetPosition());
		stickExplode->SetDamageInfo(_damageInfo);

		SCENE->GetCurrentScene()->AddObject(stickExplode);

		if (_info._pierceCount <= _currentPierceCount)
		{
			_isActivity = false;
		}
	}
}

void Stick::OnTriggerExit(Collider* collider, Collider* other)
{
}

void Stick::Reset()
{
	_currentPierceCount = 0;
}




