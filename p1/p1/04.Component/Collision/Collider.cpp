#include "pch.h"
#include "Collider.h"
#include "../../01.Manager/GameManager.h"
#include "../../03.Object/GameObject.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "97.Engin/Component/Transform/Transform.h"

Collider::Collider(ColliderType colliderType)    :  Super(ComponentType::Collider), _colliderType(colliderType)
{
    Init();
}

Collider::~Collider()
{
    _debugShow.Disconnect();
}

void Collider::Init()
{
    _debugShow =
        GAMEMANAGER->OnDebugShow += [this](bool isActivity)
        {
            _showDebug = isActivity;
        };

    _showDebug = GAMEMANAGER->GetDebugShow();
}

void Collider::Update()
{
    
}

//void Collider::Render(HDC hdc)
//{
//}

bool Collider::CheckCollision(Collider* other)
{
    return false;
}

bool Collider::CheckCollisionBoxToBox(BoxCollider* b1, BoxCollider* b2)
{
    RECT intersect = {};

    return MyIntersectRect(&intersect,b1->GetGameObject(), b2->GetGameObject());
}

bool Collider::CheckCollisionSphereToSphere(SphereCollider* s1, SphereCollider* s2)
{
    Vec3 p1 = s1->GetGameObject()->GetTransform()->GetPosition();
    float r1 = s1->GetRadius();

    
    Vec3 p2 = s2->GetGameObject()->GetTransform()->GetPosition();
    float r2 = s2->GetRadius();

    Vec3 dir = p1 - p2;
    float dist = dir.LengthSquared();


    return dist <= r1 + r2;
}

bool Collider::CheckCollisionBoxToSphere(BoxCollider* b1, SphereCollider* s2)
{

    return false;
}

// 회전을 넣고 싶으면 OBB 충돌 체크로 구현해야함
bool Collider::MyIntersectRect(LPRECT lrRect, GameObject* r1, GameObject* r2)
{
#pragma region 중략 : 크기랑 좌표 구하는 부분


    Vec3 size1 = r1->GetTransform()->GetScale();
    Vec3 size2 = r2->GetTransform()->GetScale();

    Vec3 pos1 = r1->GetTransform()->GetPosition();
    Vec3 pos2 = r2->GetTransform()->GetPosition();

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
            lrRect->left = static_cast<int32>(max(r1->GetTransform()->GetPosition().x - half1X, 
                r2->GetTransform()->GetPosition().x - half2X));
            lrRect->right = static_cast<int32>(min(r1->GetTransform()->GetPosition().x + half1X,
                r2->GetTransform()->GetPosition().x + half2X));
            lrRect->top = static_cast<int32>(max(r1->GetTransform()->GetPosition().y - half1Y,
                r2->GetTransform()->GetPosition().y - half2Y));
            lrRect->bottom = static_cast<int32>(min(r1->GetTransform()->GetPosition().y + half1Y,
                r2->GetTransform()->GetPosition().y + half2Y));
        }
        return true;
    }

    return false;
}

void Collider::ClearCollisionMap()
{
    _collsionMap.clear();
}

Vec3 Collider::GetWorldPos() const
{
    return _gameObject->GetTransform()->GetPosition() + _offset;
}
