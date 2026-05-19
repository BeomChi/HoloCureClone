#include "pch.h"
#include "Collider.h"
#include "../../01.Manager/GameManager.h"
#include "../../03.Object/GameObject.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

Collider::Collider(ColliderType colliderType) :_colliderType(colliderType)
{
    Init();
}

Collider::~Collider()
{
    _debugShow.Disconnect();
}

void Collider::Init()
{
    _debugShow =GET_SINGLE(GameManager)->OnDebugShow += [this](bool isActivity)
        {
            _showDebug = isActivity;
        };
}

void Collider::Update()
{
    
}

void Collider::Render(HDC hdc)
{
}

bool Collider::CheckCollision(Collider* other)
{
    return false;
}

bool Collider::CheckCollisionBoxToBox(BoxCollider* b1, BoxCollider* b2)
{
    RECT intersect = {};

    return MyIntersectRect(&intersect,b1->GetOwner(),b2->GetOwner());
}

bool Collider::CheckCollisionSphereToSphere(SphereCollider* s1, SphereCollider* s2)
{
    Vec2 p1 = s1->GetOwner()->GetPos();
    float r1 = s1->GetRadius();


    Vec2 p2 = s2->GetOwner()->GetPos();
    float r2 = s2->GetRadius();

    Vec2 dir = p1 - p2;
    float dist = dir.Length();


    return dist <= r1 + r2;
}

bool Collider::CheckCollisionBoxToSphere(BoxCollider* b1, SphereCollider* s2)
{

    return false;
}

bool Collider::MyIntersectRect(LPRECT lrRect, GameObject* r1, GameObject* r2)
{
#pragma region 중략 : 크기랑 좌표 구하는 부분


    Vec2 size1 = r1->GetSize();
    Vec2 size2 = r2->GetSize();

    Vec2 pos1 = r1->GetCollider()->GetWorldPos();
    Vec2 pos2 = r2->GetCollider()->GetWorldPos();

    float dx = abs(pos1.x - pos2.x);
    float dy = abs(pos1.y - pos2.y);

    float half1X = size1.x / 2;
    float half1Y = size1.y / 2;
    float half2X = size2.x / 2;
    float half2Y = size2.y / 2;
#pragma endregion

    if (dx < half1X + half2X && dy < half1Y + half2Y)
    {
        if (lrRect)
        {
            lrRect->left = static_cast<int32>(max(r1->GetPos().x - half1X, r2->GetPos().x - half2X));
            lrRect->right = static_cast<int32>(min(r1->GetPos().x + half1X, r2->GetPos().x + half2X));
            lrRect->top = static_cast<int32>(max(r1->GetPos().y - half1Y, r2->GetPos().y - half2Y));
            lrRect->bottom = static_cast<int32>(min(r1->GetPos().y + half1Y, r2->GetPos().y + half2Y));
        }
        return true;
    }

    return false;
}

void Collider::ClearCollisionMap()
{
    _collsionMap.clear();
}

Vec2 Collider::GetWorldPos() const
{
    return _owner->GetPos() + _offset;
}
