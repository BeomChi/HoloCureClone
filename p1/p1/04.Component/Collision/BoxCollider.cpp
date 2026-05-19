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

    // 내부 투명
    HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
    HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);

    // 초록색 테두리 펜 생성
    HPEN greenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    HPEN oldPen = (HPEN)::SelectObject(hdc, greenPen);

    // 사각형 그리기
    Utils::DrawRect(hdc, pos, _size.x, _size.y);

    // 원래 오브젝트 복구
    ::SelectObject(hdc, oldBrush);
    ::SelectObject(hdc, oldPen);

    // 생성한 GDI 오브젝트 해제
    ::DeleteObject(greenPen);

    /*if (_showDebug == false)
        return;

    Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(GetOwner()->GetPos() + _offset);

    HBRUSH myBrush = (HBRUSH)::GetStockObject(NULL_BRUSH);
    HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, myBrush);
    Utils::DrawRect(hdc, pos, _size.x, _size.y);
    ::SelectObject(hdc, oldBrush);
    ::DeleteObject(myBrush);*/

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
