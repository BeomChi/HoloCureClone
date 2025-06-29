#include "pch.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "../../03.Object/GameObject.h"
#include "../../01.Manager/SceneManager.h"

SphereCollider::SphereCollider() : Collider(ColliderType::Sphere)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Init()
{
}

void SphereCollider::Update()
{
}

void SphereCollider::Render(HDC hdc)
{
    Super::Render(hdc);

    if (_showDebug == false)
        return;


    //Vec2 cameraPos = GET_SINGLE(SceneManager)->GetCameraPos();
    //Vec2 pos = GetOwner()->GetPos();
    
    //pos.x -= (cameraPos.x - GWinSizeX / 2);
    //pos.y -= (cameraPos.y - GWinSizeY / 2);
    Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(GetOwner()->GetPos());

    HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
    HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
    
    Utils::DrawCircle(hdc, pos, _radius);

    ::SelectObject(hdc, oldBrush);
    ::DeleteObject(myBrush);
}

bool SphereCollider::CheckCollision(Collider* other)
{
    switch (other->GetColliderType())
    {
    case ColliderType::Box:
        return CheckCollisionBoxToSphere(static_cast<BoxCollider*>(other), this);
        break;
    case ColliderType::Sphere:
        return CheckCollisionSphereToSphere(this, static_cast<SphereCollider*>(other));
        break;
    }

	return false;
}
