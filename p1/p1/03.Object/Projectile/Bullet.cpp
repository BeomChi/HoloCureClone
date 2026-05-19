#include "pch.h"
#include "Bullet.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/SpriteRenderer.h"
#include "../../05.Resource/2D/Sprite.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	//_size = { 50, 50 };
	_info._speed = 500;

	// component
	{
		{
			Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Bullet06");
			SpriteRenderer* renderer = new SpriteRenderer();
			renderer->SetSprite(sprite);
			SetSize({ (float)sprite->GetSize().x, (float)sprite->GetSize().y });


			AddComponent(renderer);
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
	Super::OnTriggerEnter(collider, other);
	if (other->GetOwner()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetOwner())->TakeDamage(_damageInfo);
		//cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
		_isActivity = false;
	}
	
}



void Bullet::Reset()
{
	_info._dir = {0,0};

}
