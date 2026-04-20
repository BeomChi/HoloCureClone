#include "pch.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "../../03.Object/GameObject.h"
#include "../../01.Manager/SceneManager.h"


BoxCollider::BoxCollider() : Collider(ColliderType::Box)
{
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Init()
{
    Super::Init();
}

void BoxCollider::Update()
{
    Super::Update();
}

void BoxCollider::Render(HDC hdc)
{
    Super::Render(hdc);

    if (_showDebug == false)
        return;

    Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(GetOwner()->GetPos() + _offset);

    HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
    HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
    Utils::DrawRect(hdc, pos, _size.x, _size.y);
    ::SelectObject(hdc, oldBrush);
    ::DeleteObject(myBrush);

}

bool BoxCollider::CheckCollision(Collider* other)
{
    switch (other->GetColliderType())
    {
    case ColliderType::Box:
        return CheckCollisionBoxToBox(this, static_cast<BoxCollider*>(other));
        break;
    case ColliderType::Sphere:
        return CheckCollisionBoxToSphere(this, static_cast<SphereCollider*>(other));
        break;
    }

    return false;
}
