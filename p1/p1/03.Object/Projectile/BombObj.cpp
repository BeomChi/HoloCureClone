#include "pch.h"
#include "BombObj.h"
#include "../../01.Manager/ResourceManager.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../02.Scene/Scene.h"
#include "../../03.Object/ObjectPool/ObjectPool.h"
#include "../../03.Object/Projectile/BombExplode.h"
#include "../../04.Component/2D/SpriteRenderer.h"
#include "97.Engin/Resource/Sprite.h"

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
			Sprite* sprite = RESOURCE->Get<Sprite>(L"BombObj");
			SpriteRenderer* renderer = new SpriteRenderer();
			renderer->SetSprite(sprite);
			//SetSize({ (float)sprite->GetSize().x, (float)sprite->GetSize().y });


			AddComponent(renderer);
		}

	}

	Super::Init();
}

void BombObj::Update()
{
	Super::Update();

	float deltaTime = TIME->GetDeltaTime();
	deltaTime = clamp(deltaTime, 0.0f, 0.1f);

	_info._time += deltaTime;

	if (_info._time >= _info._attackDelay)
	{
		BombExplode* bombExplode = GET_SINGLE(ObjectPool)->Get<BombExplode>(L"BombExplode");
		bombExplode->GetTransform()->SetPosition(GetTransform()->GetPosition());
		bombExplode->SetDamageInfo(_damageInfo);

		SCENE->GetCurrentScene()->AddObject(bombExplode);

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


