#include "pch.h"
#include "AOE.h"
#include "../../01.Manager/GameManager.h"
#include "../../01.Manager/SceneManager.h"
#include "../../01.Manager/ResourceManager.h"
#include "03.Object/Entity/Entity.h"
#include "03.Object/Entity/Player/Player.h"
#include "97.Engin/Component/Transform/Transform.h"
#include "97.Engin/Component/Renderer/MeshRenderer.h"

AOE::AOE()
{
	GetOrAddTransform();
	auto meshRenderer = new MeshRenderer(SCENE->GetGraphics()->GetDevice(),SCENE->GetGraphics()->GetDeviceContext());
	AddComponent(meshRenderer);

	auto material = RESOURCE->Get<Material>(L"Default");
	meshRenderer->SetMaterial(material);
	auto mesh = RESOURCE->Get<Mesh>(L"Rectangle");
	meshRenderer->SetMesh(mesh);
}

AOE::~AOE()
{
}

void AOE::Init()
{
	SetLayer(LAYER_AREAATTACK);
	_entityType = EntityType::Mineral;
	Super::Init();
}

void AOE::Update()
{
	Super::Update();
}

void AOE::Render(HDC hdc)
{
	Super::Render(hdc);
}

void AOE::SetScaleMultple(float scale)
{
	_info._baseScale += scale;
	GetTransform()->SetScale(Vec3(_info._baseScale, _info._baseScale, 1));
	//SetScale({ _info._baseScale,_info._baseScale });
}

// 넉백 같은거 나중에 버프 효과로 따로 빼서 하는 것도 좋을거 같은디
void AOE::Knockback(GameObject* obj, GameObject* other, float force)
{
	Vec3 dir = other->GetTransform()->GetPosition() - GAMEMANAGER->GetPlayer()->GetTransform()->GetPosition();
	dir.Normalize();

	// 넉백 거리 만큼 dir을 곱해주고 거기에다가 객체의 위치를 더해서 위치를 설정하면 텔포가 되어버리는 데 음
	if (dir.Length() == 0)
		dir = { 1,0 };
	else
		dir.Normalize();

	float knockPower = force;
	static_cast<Entity*>(other)->SetState(State::Stagger);
	other->AddVelocity(dir * knockPower);
}

