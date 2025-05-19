#pragma once
#include "Singleton.h"

class Collider;

class CollisionManager : public Singleton<CollisionManager>
{
	friend class Singleton<CollisionManager>;
public:
	~CollisionManager();

	void Init();
	void Update();

	void AddCollider(Collider* collider);
	void RemoveCollider(Collider* collider);

	void Clear();

private:
	vector<Collider*> _colliders;
};

