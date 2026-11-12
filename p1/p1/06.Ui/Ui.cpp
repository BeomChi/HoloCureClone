#include "pch.h"
#include "Ui.h"
#include "../01.Manager/InputManager.h"
#include "../01.Manager/SceneManager.h"
#include "../01.Manager/ResourceManager.h"
#include "97.Engin/Component/Transform/Transform.h"
#include "97.Engin/Component/Renderer/MeshRenderer.h"

Ui::Ui()
{
	Transform* transform = new Transform();
	AddComponent(transform);

	auto meshRenderer = new MeshRenderer(SCENE->GetGraphics()->GetDevice(),
		SCENE->GetGraphics()->GetDeviceContext());
	AddComponent(meshRenderer);

	auto material = RESOURCE->Get<Material>(L"Default");
	meshRenderer->SetMaterial(material);
	auto mesh = RESOURCE->Get<Mesh>(L"Rectangle");
	meshRenderer->SetMesh(mesh);
}

Ui::~Ui()
{
}

void Ui::Init()
{
	Super::Init();
}

void Ui::Update()
{
	Super::Update();
}

void Ui::Render(HDC hdc)
{
	Super::Render(hdc);
}

RECT Ui::GetRect()
{
	float x = GetOrAddTransform()->GetPosition().x;
	float y = GetOrAddTransform()->GetPosition().y;

	float cx = _renderSize.x * GetOrAddTransform()->GetScale().x;
	float cy = _renderSize.y * GetOrAddTransform()->GetScale().y;

	float screenX = GWinSizeX * 0.5f + x;
	float screenY = GWinSizeY * 0.5f - y;

	RECT rect =
	{
		screenX - cx/ 2,
		screenY - cy / 2,
		screenX + cx / 2,
		screenY + cy / 2
	};

	return rect;
}

bool Ui::IsMouseInRect()
{
	RECT rect = GetRect();

	POINT mousePos = INPUT->GetMousePos();

	if (mousePos.x < rect.left)
		return false;
	if (mousePos.x > rect.right)
		return false;
	if (mousePos.y < rect.top)
		return false;
	if (mousePos.y > rect.bottom)
		return false;

	return true;
}
