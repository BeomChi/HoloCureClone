#pragma once
#include "../Component.h"

class BoxCollider;
class SphereCollider;

class Collider : public Component
{
public:
	Collider(ColliderType colliderType);
	virtual ~Collider() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other);

	ColliderType GetColliderType() { return _colliderType; }

	bool CheckCollisionBoxToBox(BoxCollider* b1, BoxCollider* b2);
	bool CheckCollisionSphereToSphere(SphereCollider* s1, SphereCollider* s2);
	bool CheckCollisionBoxToSphere(BoxCollider* b1, SphereCollider* s2);

	bool MyIntersectRect(LPRECT lrRect,  GameObject* r1,  GameObject* r2);

	void SetShowDebug(bool value) { _showDebug = value; }
	void ClearCollisionMap();

	unordered_set<Collider*>& GetCollisionMap() { return _collsionMap; }
	void SetOffset(Vec2 offset) { _offset = offset; }

	Vec2 GetWorldPos() const;

protected:
	bool _showDebug = false;
	
	ColliderType _colliderType;
	Vec2 _offset = { 0,0 };
	

private:
	unordered_set<Collider*> _collsionMap;
};

