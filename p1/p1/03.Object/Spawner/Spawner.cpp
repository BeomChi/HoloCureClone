#include "pch.h"
#include "Spawner.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/SpawnManager.h"
#include "../../02.Scene/Scene.h"
#include "../../03.Object/ObjectPool/ObjectPool.h"
#include "../../03.Object/Entity/Monster/Monster.h"
#include "../../03.Object/Entity/Monster/NormalMonster.h"
#include "../../03.Object/Entity/Monster/Fubura.h"
#include "../../03.Object/Entity/Monster/Shubangelion.h"


Spawner::Spawner()
{
}

Spawner::~Spawner()
{
}

void Spawner::Init()
{
	
}

void Spawner::Update()
{
	
}

void Spawner::Render(HDC hdc)
{
	
}

void Spawner::NormalMonsterSpawn()
{
	int32 x = RandomRange(0, GWinSizeX);
	int32 y = RandomRange(0, GWinSizeY);

	Vec2 pos = GET_SINGLE(SceneManager)->ScreenToWorld({ (float)x,(float)y });

	Monster* monster = GET_SINGLE(ObjectPool)->Get<NormalMonster>(L"NormalMonster");
	monster->SetPos({ pos.x,pos.y });
	monster->SetState(State::Spawn);
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(monster);

	GET_SINGLE(SpawnManager)->AddCurrentSpawnCount();
}

void Spawner::SpawnMidleBoss(int32 Stage)
{
	// 지금은 이렇게 해놓지만 나중에 스테이지에 맞게 소환하도록 해야함
	// 이차원 배열로 해서 [stage - 1][현재 소환된 중간보스 수]
	int32 x = RandomRange(0, GWinSizeX);
	int32 y = RandomRange(0, GWinSizeY);

	Vec2 pos = GET_SINGLE(SceneManager)->ScreenToWorld({ (float)x,(float)y });

	Monster* monster = GET_SINGLE(ObjectPool)->Get<Fubura>(L"Fubura");
	monster->SetPos({ pos.x,pos.y });
	monster->SetState(State::Spawn);
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(monster);

	GET_SINGLE(SpawnManager)->AddCurrentSpawnCount();
}

void Spawner::SpawnBoss(int32 Stage)
{
	// 보스 소환 코드
	int32 x = RandomRange(0, GWinSizeX);
	int32 y = RandomRange(0, GWinSizeY);

	Vec2 pos = GET_SINGLE(SceneManager)->ScreenToWorld({ (float)x,(float)y });

	// 나중에 보스 만들면 바꿔야함
	Monster* monster = GET_SINGLE(ObjectPool)->Get<Shubangelion>(L"Shubangelion");
	monster->SetPos({ pos.x,pos.y });
	monster->SetKey(L"Boss");
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(monster);
	
	GET_SINGLE(SpawnManager)->AddCurrentSpawnCount();
}
