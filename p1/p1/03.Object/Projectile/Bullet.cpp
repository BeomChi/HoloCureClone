#include "pch.h"
#include "Bullet.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/CollisionManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../03.Object/Entity/Entity.h"
#include "../../04.Component/Collision/BoxCollider.h"
#include "../../04.Component/2D/SpriteRenderer.h"
#include "97.Engin/Resource/Sprite.h"
#include "97.Engin/Resource/Texture.h"

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
			Sprite* sprite = RESOURCE->Get<Sprite>(L"Bullet06");
			_spriteRenderer = new SpriteRenderer();
			_spriteRenderer->SetSprite(sprite);
			//SetSize({ (float)sprite->GetSize().x, (float)sprite->GetSize().y });


			AddComponent(_spriteRenderer);
		}
		// collider
		{
			BoxCollider* collider = new BoxCollider();
			collider->SetSize(_spriteRenderer->GetSprite()->GetSize());
			collider->SetShowDebug(false);
			AddComponent(collider);
			//SetCollider(collider);

			GET_SINGLE(CollisionManager)->AddCollider(collider);
		}
		
	}
	Super::Init();
}

void Bullet::Update()
{
	Super::Update();

	float deltaTime = TIME->GetDeltaTime();

	//_info._time += deltaTime;

	Vec3 pos = GetTransform()->GetPosition();
	pos += _info._dir * _info._speed * deltaTime;
	
	GetTransform()->SetPosition(pos);

	pos = SCENE->WorldToScreen(Vec2(pos.x, pos.y));
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
	if (other->GetGameObject()->GetEntityType() == EntityType::Monster)
	{
		static_cast<Entity*>(other->GetGameObject())->TakeDamage(_damageInfo);
		//cout << "데미지 들어감 : " << _damageInfo._finalDamage << endl;
		_currentPierceCount++;

		if(_info._pierceCount <= _currentPierceCount)
			_isActivity = false;
	}
	
}



void Bullet::Reset()
{
	_info._dir = {0,0};
	_currentPierceCount = 0;
}
