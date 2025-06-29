#include "pch.h"
#include "BLBook.h"
#include "../../../../01.Manager/InputManager.h"
#include "../../../../01.Manager/TimeManager.h"
#include "../../../../01.Manager/SceneManager.h"
#include "../../../../01.Manager/GameManager.h"
#include "../../../../01.Manager/ObjectManager.h"
#include "../../../../03.Object/ObjectPool/ObjectPool.h"
#include "../../../../03.Object/Projectile/BLBookObj.h"
#include "../../../../03.Object/Entity/Player/Player.h"





BLBook::BLBook()
{
}

BLBook::~BLBook()
{
}

void BLBook::Init()
{
	SetEquipInfo({ L"BLBook",1,7,3,0,1,0,3,1});

	_shieldAngle = 360 / _info._count;
	_playerToshield = 100;
	
}

void BLBook::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	for (int i = 0; i < _info._count;i++)
	{
		if (i >= _blBook.size())
		{
			auto* obj = GET_SINGLE(ObjectPool)->Get<BLBookObj>(L"BLBook");
			//obj->Activate();
			obj->SetDmg(CalculateDamge());

			GET_SINGLE(ObjectManager)->AddObject(obj);
			_blBook.push_back(obj);
		}
		else if (_blBook[i] == nullptr || !_blBook[i]->GetIsActivity())
		{
			_blBook[i] = GET_SINGLE(ObjectPool)->Get<BLBookObj>(L"BLBook");
			//_blBook[i]->Activate();

			_blBook[i]->SetDmg(CalculateDamge());
			GET_SINGLE(ObjectManager)->AddObject(_blBook[i]);
		}

		Vector shieldPos = GET_SINGLE(GameManager)->GetPlayer()->GetPos();

		float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();
		_shieldRoateAngle += (15 * deltaTime) * PI / 180;
		float shieldDinstance = (i * _shieldAngle) * PI / 180;

		shieldPos.x += cos(_shieldRoateAngle + shieldDinstance) * _playerToshield;
		shieldPos.y += sin(_shieldRoateAngle + shieldDinstance) * _playerToshield;
		_blBook[i]->SetPos(shieldPos);
	}

	
}

void BLBook::Render(HDC hdc)
{
}

void BLBook::OnEquipEffect(Player& player)
{
	ApplyEffectByLevel(_info._level);

	// 각도 계산하는거 넣어줘야함
}



void BLBook::OnUnequipEffect(Player& player)
{

}



void BLBook::ApplyEffect()
{
}

void BLBook::UseAbility(const Player& player)
{
}
