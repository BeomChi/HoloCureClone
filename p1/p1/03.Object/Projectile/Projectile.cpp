#include "pch.h"
#include "Projectile.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/GameManager.h"


Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::Init()
{
	SetLayer(LAYER_AREAATTACK);
	_entityType = EntityType::Mineral;
	Super::Init();
}

void Projectile::Update()
{
	Super::Update();

	Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(_pos);

	if (pos.x <= -50 || pos.y <= -50 ||
		pos.x >= GWinSizeX + 50|| pos.y >= GWinSizeY + 50)
	{
		_isActivity = false;
	}
}

void Projectile::Render(HDC hdc)
{
	Super::Render(hdc);

}





