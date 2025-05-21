#pragma once
#include "../GameObject.h"

class Spawner :    public GameObject
{
	using Super = GameObject;
public:
	Spawner();
	virtual ~Spawner() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void NormalMonsterSpawn();
	void SpawnMidleBoss(int32 Stage);
	void SpawnBoss(int32 Stage);

private:
	
};

