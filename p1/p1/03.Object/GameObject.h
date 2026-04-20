#pragma once

class Component;
class Collider;
class BoxCollider;


class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Reset();

	// Component
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	// Position
	void SetPos(Vec2 pos) { _pos = pos; }
	Vec2 GetPos() { return _pos; }

	// Size
	void SetSize(Vec2 size);
	Vec2 GetSize() { return _size; }

	// Scale
	void SetScale(Vec2 scale);
	Vec2 GetScale() { return _scale; }

	Vec2 GetRenderSize() { return _renderSize; }

	// IsActivity
	bool GetIsActivity() { return _isActivity; }
	void SetIsActivity(bool isActivity) { _isActivity = isActivity; }

	virtual void OnEnable();

	// Key
	wstring GetKey() { return _key; }
	void SetKey(wstring key) { _key = key; }

	// Type
	EntityType GetEntityType() const { return _entityType; }

	// Collider
	virtual void OnTriggerEnter(Collider* collider, Collider* other);
	virtual void OnTriggerStay(Collider* collider, Collider* other);
	virtual void OnTriggerExit(Collider* collider, Collider* other);

	void SetCollider(Collider* collider) { _collider = collider; }
	Collider* GetCollider() { return _collider; }

	void SetLayer(LAYER_TYPE layer) { _layer = layer; }
	LAYER_TYPE GetLayer() { return _layer; }

	void  AddVelocity(const Vector& v) { _velocity += v; }


	int RandomRange(int min, int max)
	{
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int32_t> dist(min, max);

		return dist(mt);
	}


private:
	void Clear();

protected:
	// VALUE
	Vec2 _pos = {};
	Vec2 _size = { 0, 0};
	Vec2 _scale = { 1,1 };
	Vec2 _renderSize = { 0,0 };
	Vec2 _velocity = { 0,0 };
	bool _isActivity = true;

	vector<Component*> _components;

	wstring _key;

	// TYPE
	LAYER_TYPE _layer = LAYER_OBJECT;
	EntityType _entityType;				// »ç½Ç»ó tag ¤·¤µ¤·


	Collider* _collider = nullptr;
};

