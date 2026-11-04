#include "pch.h"
#include "Spawner.h"
#include "../../01.Manager/TimeManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/SpawnManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../02.Scene/Scene.h"
#include "../../03.Object/ObjectPool/ObjectPool.h"
#include "../../03.Object/Entity/Monster/Monster.h"
#include "../../03.Object/Entity/Monster/NormalMonster.h"
#include "../../03.Object/Entity/Monster/Fubura.h"
#include "../../03.Object/Entity/Monster/Shubangelion.h"
#include "../../03.Object/Entity/Player/Player.h"


Spawner::Spawner()
{
}

Spawner::~Spawner()
{
}

void Spawner::Init()
{
	GetOrAddTransform();
}

void Spawner::Update()
{
	
}

//void Spawner::Render(HDC hdc)
//{
//	
//}

void Spawner::NormalMonsterSpawn()
{
	Vec3 pos = SpawnRandomPositionAroundPlayer();

	Monster* monster = GET_SINGLE(ObjectPool)->Get<NormalMonster>(L"NormalMonster");
	monster->GetTransform()->SetPosition({ pos.x,pos.y,0 });
	monster->SetState(State::Spawn);
	SCENE->GetCurrentScene()->AddObject(monster);

	GET_SINGLE(SpawnManager)->AddCurrentSpawnCount();
}

void Spawner::SpawnMidleBoss(int32 Stage)
{
	// 지금은 이렇게 해놓지만 나중에 스테이지에 맞게 소환하도록 해야함
	// 이차원 배열로 해서 [stage - 1][현재 소환된 중간보스 수]

	Vec3 pos = SpawnRandomPositionAroundPlayer();

	Monster* monster = GET_SINGLE(ObjectPool)->Get<Fubura>(L"Fubura");
	monster->GetTransform()->SetPosition({ pos.x,pos.y,0 });
	monster->SetState(State::Spawn);
	SCENE->GetCurrentScene()->AddObject(monster);

	GET_SINGLE(SpawnManager)->AddCurrentSpawnCount();
}

void Spawner::SpawnBoss(int32 Stage)
{
	Vec3 pos = SpawnRandomPositionAroundPlayer();

	Monster* monster = GET_SINGLE(ObjectPool)->Get<Shubangelion>(L"Shubangelion");
	monster->GetTransform()->SetPosition({ pos.x,pos.y,0 });
	monster->SetKey(L"Boss");
	SCENE->GetCurrentScene()->AddObject(monster);
	
	GET_SINGLE(SpawnManager)->AddCurrentSpawnCount();
}

Vec3 Spawner::SpawnRandomPositionAroundPlayer()
{
	// 윈도우 화면 내 임의 위치 생성
	int randX = RandomRange(-GWinSizeX / 2, GWinSizeX / 2);
	int randY = RandomRange(-GWinSizeY / 2, GWinSizeY / 2);

	Vec3 playerPos = GAMEMANAGER->GetPlayer()->GetTransform()->GetPosition();

	// 화면 좌표를 월드 좌표로 변환
	Vec3 randOffset = { (float)randX, (float)randY, 0 };
	Vec3 randPos = playerPos + randOffset;

	return randPos;
}