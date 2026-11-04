#include "pch.h"
#include "Projectile.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "97.Engin/Component/Transform/Transform.h"
#include "97.Engin/Component/Renderer/MeshRenderer.h"


Projectile::Projectile()
{
	GetOrAddTransform();
	auto meshRenderer = new MeshRenderer(SCENE->GetGraphics()->GetDevice(), SCENE->GetGraphics()->GetDeviceContext());
	AddComponent(meshRenderer);

	auto material = RESOURCE->Get<Material>(L"Default");
	meshRenderer->SetMaterial(material);
	auto mesh = RESOURCE->Get<Mesh>(L"Rectangle");
	meshRenderer->SetMesh(mesh);
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

	//Vector pos = SCENE->WorldToScreen(_pos);
	Vec3 pos = GetTransform()->GetPosition();

	pos = SCENE->WorldToScreen(Vec2(pos.x, pos.y));

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





