#include "pch.h"
#include "Heal.h"
#include "../../../01.Manager/ResourceManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../01.Manager/GameManager.h"
#include "../../../03.Object/Entity/Player/Player.h"
#include "97.Engin/Component/Animation/Animator.h"
#include "97.Engin/Resource/Animation.h"


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
	Animator* ani = new Animator();
	ani->SetAnimation(RESOURCE->Get<Animation>(L"HealObject"));

	//Vec2Int size = ani->GetAnimator()->GetInfo().size;
	//SetSize({ (float)size.x,(float)size.y });

	AddComponent(ani);

	

	Super::Init();
}

void Heal::Update()
{
	Super::Update();

	PlayerDistance();
}

//void Heal::Render(HDC hdc)
//{
//	Super::Render(hdc);
//
//}

void Heal::AddToHeal(Player* obj)
{
	obj->Heal(_healAmount);

}

void Heal::ApplyEffect()
{
	if (_player == nullptr)
		return;

	AddToHeal(_player);
}
