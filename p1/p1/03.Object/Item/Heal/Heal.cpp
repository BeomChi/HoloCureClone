#include "pch.h"
#include "Heal.h"
#include "../../../01.Manager/ResourceManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../01.Manager/GameManager.h"
#include "../../../03.Object/Entity/Player/Player.h"
#include "../../../04.Component/2D/AnimationComponent.h"
#include "../../../05.Resource/2D/Animator.h"


Heal::Heal()
{
	_itemType = ItemType::Heal;
}

Heal::~Heal()
{
}

void Heal::Init()
{
	int rand = RandomRange(0, 5);


	// 애니메이션 컴포넌트 추가
	AnimationComponent* ani = new AnimationComponent();
	ani->SetAnimation(GET_SINGLE(ResourceManager)->GetAnimator(L"HealObject"));

	Vec2Int size = ani->GetAnimator()->GetInfo().size;
	SetSize({ (float)size.x,(float)size.y });

	AddComponent(ani);

	

	Super::Init();
}

void Heal::Update()
{
	Super::Update();

	PlayerDistance();
}

void Heal::Render(HDC hdc)
{
	Super::Render(hdc);

	{
		Vec2 pos = GET_SINGLE(SceneManager)->WorldToScreen(_pos);
		wstring str = std::format(L"Exp :({0})", _exp);
		::TextOut(hdc, pos.x, pos.y - _size.y, str.c_str(), static_cast<int32>(str.size()));
	}
}

void Heal::AddToHeal(Player* obj)
{
	obj->Heal(50.f);

}

void Heal::ApplyEffect()
{
	if (_player == nullptr)
		return;

	AddToHeal(_player);
}
