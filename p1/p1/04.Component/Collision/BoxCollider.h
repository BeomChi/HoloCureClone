#pragma once
#include "Collider.h"
class BoxCollider :    public Collider
{
	using Super = Collider;
public:
	BoxCollider();
	virtual ~BoxCollider() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	virtual bool CheckCollision(Collider* other);

	Vector GetSize() { return _size; }
	void SetSize(Vector size) { _size = size; }

private:
	Vector _size = {};
};

