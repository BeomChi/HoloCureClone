#include "pch.h"
#include "BombObj.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/ObjectManager.h"
#include "../../03.Object/ObjectPool/ObjectPool.h"
#include "../../03.Object/Projectile/BombExplode.h"
#include "../../04.Component/2D/SpriteRenderer.h"
#include "../../05.Resource/2D/Sprite.h"

BombObj::BombObj()
{
}

BombObj::~BombObj()
{
}

void BombObj::Init()
{// component
	{
		{
			Sprite* sprite = GET_SINGLE(ResourceManager)->GetSprite(L"Bomb");
			SpriteRenderer* renderer = new SpriteRenderer();
			renderer->SetSprite(sprite);
			SetSize({ (float)sprite->GetSize().x, (float)sprite->GetSize().y });


			AddComponent(renderer);
		}

	}

	Super::Init();
}

void BombObj::Update()
{
	Super::Update();

	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
	deltaTime = clamp(deltaTime, 0.0f, 0.1f);

	_info._time += deltaTime;

	if (_info._time >= _info._attackDelay)
	{
		BombExplode* bombExplode = GET_SINGLE(ObjectPool)->Get<BombExplode>(L"BombExplode");
		bombExplode->SetPos(GetPos());
		bombExplode->SetDemage(_info._dmg);

		GET_SINGLE(ObjectManager)->AddObject(bombExplode);

		SetIsActivity(false);
	}


}

void BombObj::Render(HDC hdc)
{
	Super::Render(hdc);
	//Utils::DrawRect(hdc, _pos, _size.x, _size.y);
}



void BombObj::Reset()
{
	_info._time = 0;

}


