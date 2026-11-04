#pragma once

class Component;
class Collider;
class BoxCollider;

class MonoBehaviour;
class Transform;
class Camera;
class MeshRenderer;
class Animator;


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
	//void SetPos(Vector pos) { _pos = pos; }
	//Vector GetPos() { return _pos; }

	// Size
	 //고유 사이즈
	//void SetSize(Vector size);
	//Vector GetSize() { return _size; }

	 //Scale
	 //렌더 사이즈
	//void SetScale(Vector scale);
	//Vector GetScale() { return _scale; }

	//Vector GetRenderSize() { return _renderSize; }

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


	void SetLayer(LAYER_TYPE layer) { _layer = layer; }
	LAYER_TYPE GetLayer() { return _layer; }

	void  AddVelocity(const Vec3& v) { _velocity += v; }


	int RandomRange(int min, int max)
	{
		random_device rd;
		mt19937 mt(rd());
		uniform_int_distribution<int32_t> dist(min, max);

		return dist(mt);
	}


	Collider* GetCollider();
	//void SetCollider(Collider* collider) { _collider = collider; }

	Component* GetFixedComponent(ComponentType type);
	Transform* GetTransform();
	Camera* GetCamera();
	MeshRenderer* GetMeshRenderer();
	Animator* GetAnimator();

	Transform* GetOrAddTransform();


private:
	void Clear();

protected:
	// VALUE
	// 트랜스폼으로 옮겼으니 이제 이것들은 안씀
	//Vector _pos = {};
	//Vector _size = { 0, 0};
	//Vector _scale = { 1,1 };
	//Vector _renderSize = { 0,0 };
	Vec3 _velocity = { 0,0 ,0};

	bool _isActivity = true;

	array<Component*, FIXED_COMPONENT_COUNT> _components;
	vector<MonoBehaviour*> _scripts;
	

	wstring _key;			// 오브젝트 이름

	// TYPE
	LAYER_TYPE _layer = LAYER_OBJECT;
	EntityType _entityType;				// 사실상 tag ㅇㅅㅇ

	//Collider* _collider = nullptr;
};

