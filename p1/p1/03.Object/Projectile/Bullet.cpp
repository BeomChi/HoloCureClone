#include "../../pch.h"
#include "Bullet.h"
#include "../../01.Manager/TimeManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../01.Manager/ObjectManager.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/SpriteRenderer.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../05.Resource/2D/Sprite.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	_size = { 50, 50 };
	_info._speed = 500;

	// component
	{
		// collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize(_size);
			collider->SetShowDebug(true);
			AddComponent(collider);
			SetCollider(collider);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
		}
		{
			Sprite* sprtie = GET_SINGLE(ResourceManager)->GetSprite(L"GuraImage");
			SpriteRenderer* renderer = new SpriteRenderer();
			renderer->SetSprtie(sprtie);

			AddComponent(renderer);
		}
	}
	Super::Init();
}

void Bullet::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	//_info._time += deltaTime;

	_pos += _info._dir * _info._speed * deltaTime;
	Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(_pos);

	if (pos.x <= 0 || pos.y <= 0 ||
		pos.x >= GWinSizeX || pos.y >= GWinSizeY)
	{
		_isActivity = false;
	}
}

void Bullet::Render(HDC hdc)
{
	Super::Render(hdc);

	//Utils::DrawCircle(hdc, _pos, _size);
}

void Bullet::OnTriggerEnter(Collider* collider, Collider* other)
{
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetOwner())->TakeDamage(_info._dmg);
		_isActivity = false;
	}
	else if (other->GetOwner()->GetEntityType() == EntityType::Player)
	{

	}
}

void Bullet::OnTriggerExit(Collider* collider, Collider* other)
{
}

void Bullet::Reset()
{
	_info._dir = {};
	_info._dmg = 0;
	_info._time = 0;
}
