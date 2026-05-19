#include "pch.h"
#include "Monster.h"
#include "../../../01.Manager/CollisionManager.h"
#include "../../../01.Manager/GameManager.h"
#include "../../../01.Manager/ResourceManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../01.Manager/SpawnManager.h"
#include "../../../01.Manager/StageManager.h"
#include "../../../02.Scene/Scene.h"
#include "../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../03.Object/Item/Experinence/ExperinenceObject.h"
#include "../../../03.Object/Item/Heal/Heal.h"
#include "../../../03.Object/Entity/Player/Player.h"
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
	_aniSpawn = GET_SINGLE(ResourceManager)->GetAnimator(L"FanSpawn");
	_aniDie = GET_SINGLE(ResourceManager)->GetAnimator(L"FanDie");

}

void Monster::Update()
{
	Super::Update();


	if (_info._isDead)
	{
		
		if (_ani->CheckCurrentAnimationEnd())
		{
			GET_SINGLE(SpawnManager)->SubCurrentSpawnCount();

			// 경험치 및 아이템 드랍
			ExperinenceObject* exp = GET_SINGLE(ObjectPool)->Get<ExperinenceObject>(L"Exp");
			exp->SetPlayer(GET_SINGLE(GameManager)->GetPlayer());
			exp->SetPos(_pos);
			GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(exp);

			Heal* heal = GET_SINGLE(ObjectPool)->Get<Heal>(L"Heal");
			heal->SetPlayer(GET_SINGLE(GameManager)->GetPlayer());
			heal->SetPos(_pos);
			GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(heal);
			GET_SINGLE(StageManager)->PlusMonsterDieCount();

			cout << "드랍됨" << endl;
			_isActivity = false;
		}
	}
	
}

void Monster::Render(HDC hdc)
{
	Super::Render(hdc);
	
	/*{
		Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(_pos);
		wstring str = std::format(L"MonsterHp :({0})", _info._currentHp);
		::TextOut(hdc, pos.x, pos.y - _size.y, str.c_str(), static_cast<int32>(str.size()));
	}*/
}

void Monster::InitCommon()
{
	InitStat();
	_entityType = EntityType::Monster;
	_state = State::Move;

	if(_ani != nullptr)
		AddComponent(_ani);

	BoxCollider* _boxCollider = new BoxCollider();
	_boxCollider->SetShowDebug(false);
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
	/*const vector<GameObject*>& objs = GET_SINGLE(SceneManager)->GetCurrentScene()->GetGameObjects(LAYER_OBJECT);

	for (auto& obj : objs)
	{
		if (obj->GetIsActivity() == false)
			continue;

		if (obj->GetEntityType() == EntityType::Player)
		{
			cout << "[DEBUG] Monster::SerachPlayer - 반환 주소: " << obj << endl;
			return obj;
		}
	}*/

	auto player = GET_SINGLE(GameManager)->GetPlayer();

	if (player && player->GetIsActivity())
	{
		cout << "[DEBUG] Monster::SerachPlayer - 반환 주소: " << player << endl;
		return player;
	}

	cout << "[DEBUG] Monster::SerachPlayer - 플레이어를 찾을 수 없음" << endl;
	return nullptr;
}
