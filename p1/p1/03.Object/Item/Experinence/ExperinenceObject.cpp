#include "../../../pch.h"
#include "ExperinenceObject.h"
#include "../../../01.Manager/ResourceManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../01.Manager/GameManager.h"
#include "../../../03.Object/Entity/Player/Player.h"
#include "../../../04.Component/2D/SpriteRenderer.h"
#include "../../../05.Resource/2D/Sprite.h"


ExperinenceObject::ExperinenceObject()
{
	_itemType = ItemType::Exp;
}

ExperinenceObject::~ExperinenceObject()
{
}

void ExperinenceObject::Init()
{
	int rand = RandomRange(0, 5);

	// 스프라이트 초기화
	_sprites[0] = GET_SINGLE(ResourceManager)->GetSprite(L"Exp01");
	_sprites[1] = GET_SINGLE(ResourceManager)->GetSprite(L"Exp02");
	_sprites[2] = GET_SINGLE(ResourceManager)->GetSprite(L"Exp03");
	_sprites[3] = GET_SINGLE(ResourceManager)->GetSprite(L"Exp04");
	_sprites[4] = GET_SINGLE(ResourceManager)->GetSprite(L"Exp05");
	_sprites[5] = GET_SINGLE(ResourceManager)->GetSprite(L"Exp06");

	// 렌더러 넣어주고
	SpriteRenderer* sprite = new SpriteRenderer();
	sprite->SetSprite(_sprites[rand]);

	Vec2Int size = sprite->GetSprite()->GetSize();
	SetSize({ (float)size.x,(float)size.y });

	AddComponent(sprite);

	_exp = _expArr[rand];

	Super::Init();
}

void ExperinenceObject::Update()
{
	Super::Update();
}

void ExperinenceObject::Render(HDC hdc)
{
	Super::Render(hdc);

	{
		Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(_pos);
		wstring str = std::format(L"Exp :({0})", _exp);
		::TextOut(hdc, pos.x, pos.y - _size.y, str.c_str(), static_cast<int32>(str.size()));
	}
}

void ExperinenceObject::AddToExp(Player* obj)
{
	obj->AddExp(_exp);
	obj->CheckLevelUpExp();
}

void ExperinenceObject::ApplyEffect()
{
	if (_player == nullptr)
		return;

	AddToExp(_player);
}
