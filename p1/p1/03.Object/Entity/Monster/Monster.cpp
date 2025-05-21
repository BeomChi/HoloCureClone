#include "../../../pch.h"
#include "Monster.h"
#include "../../../01.Manager/CollisionManager.h"
#include "../../../01.Manager/ObjectManager.h"
#include "../../../01.Manager/ResourceManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../01.Manager/SpawnManager.h"
#include "../../../04.Component/2D/AnimationComponent.h"
#include "../../../04.Component/Collision/BoxCollider.h"
#include "../../../05.Resource/2D/Animator.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Init()
{
	InitCommon();
}

void Monster::Update()
{
	Super::Update();


	if (_info._isDead)
	{
		_isActivity = false;
		GET_SINGLE(SpawnManager)->SubCurrentSpawnCount();
		// 게임 매니저에다가 점수 +
	}
	
}

void Monster::Render(HDC hdc)
{
	Super::Render(hdc);
	
	{
		Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(_pos);
		wstring str = std::format(L"MonsterHp :({0})", _info._currentHp);
		::TextOut(hdc, pos.x, pos.y - _size.y, str.c_str(), static_cast<int32>(str.size()));
	}
}

void Monster::InitCommon()
{
	InitStat();
	_entityType = EntityType::Monster;
	_state = State::Move;

	if(_ani != nullptr)
		AddComponent(_ani);

	BoxCollider* _boxCollider = new BoxCollider();
	_boxCollider->SetShowDebug(true);
	SetCollider(_boxCollider);

	Vec2Int size = _ani->GetAnimator()->GetInfo().size;
	SetSize({ (float)size.x, (float)size.y });

	AddComponent(_boxCollider);

	GET_SINGLE(CollisionManager)->AddCollider(_boxCollider);
	


	Super::Init();
}

void Monster::InitStat()
{

}

void Monster::Reset()
{
}

GameObject* Monster::SerachPlayer()
{
	const vector<GameObject*>& objs = GET_SINGLE(ObjectManager)->GetGameObjects(LAYER_OBJECT);

	for (auto& obj : objs)
	{
		if (obj->GetIsActivity() == false)
			continue;

		if (obj->GetEntityType() == EntityType::Player)
			return obj;
	}

	return nullptr;
}
