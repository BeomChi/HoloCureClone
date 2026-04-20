#include "pch.h"
#include "AOE.h"
#include "../../01.Manager/GameManager.h"
#include "03.Object/Entity/Entity.h"
#include "03.Object/Entity/Player/Player.h"

AOE::AOE()
{
}

AOE::~AOE()
{
}

void AOE::Init()
{
	SetLayer(LAYER_AREAATTACK);
	Super::Init();
}

void AOE::Update()
{
	Super::Update();
}

void AOE::Render(HDC hdc)
{
	Super::Render(hdc);
}

void AOE::SetScaleMultple(float scale)
{
	_info._baseScale += scale;
	SetScale({ _info._baseScale,_info._baseScale });
}

void AOE::Knockback(GameObject* obj, GameObject* other, float force)
{
	Vec2 dir = other->GetPos() - GET_SINGLE(GameManager)->GetPlayer()->GetPos();
	dir.Normalize();

	// 넉백 거리 만큼 dir을 곱해주고 거기에다가 객체의 위치를 더해서 위치를 설정하면 텔포가 되어버리는 데 음
	if (dir.Length() == 0)
		dir = { 1,0 };
	else
		dir.Normalize();

	float knockPower = force;
	static_cast<Entity*>(other)->SetState(State::Stagger);
	other->AddVelocity(dir * knockPower);
}

