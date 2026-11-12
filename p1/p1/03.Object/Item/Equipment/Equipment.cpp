#include "pch.h"
#include "Equipment.h"
#include "../../../01.Manager/GameManager.h"
#include "../../../01.Manager/InputManager.h"
#include "../../../01.Manager/SceneManager.h"
#include "../../../03.Object/Entity/Player/Player.h"

Equipment::Equipment()
{
	//_itemType = ItemType::Equipment;
}

Equipment::~Equipment()
{
}

void Equipment::Init()
{
	//Super::Init();
}

void Equipment::Update()
{
	//Super::Update();
}

void Equipment::Render(HDC hdc)
{
	//Super::Render(hdc);
}

bool Equipment::IsMaxLevel()
{
	if (_baseInfo._maxLevel == _baseInfo._level)
		return true;

	return false;
}


void Equipment::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const ProjectileEquipInfo& info)
{
	// 자식에서 오버라이드해서 사용
}

void Equipment::SetEquipInfo(const EquipmentBaseInfo& baseInfo, const AOEEquipInfo& info)
{
	// 자식에서 오버라이드해서 사용
}

/// @brief 무기 레벨 업 및 장착 효과 적용
/// @param player 현재 플레이어 객체 참조
/// @details 레벨을 1 증가시키고, 레벨에 맞는 장착 효과를 적용
void Equipment::UpgradeEquip(Player& player)
{
	if (_baseInfo._level >= _baseInfo._maxLevel)
		return; // 최대 레벨에 도달했으면 더 이상 업그레이드 불가


	_baseInfo._level++;        // 레벨 증가
	OnEquipEffect(player); // 장착 효과 갱신
}



/// @brief 무기의 최종 데미지 계산
/// @return 플레이어 공격력과 데미지 배율을 곱한 값
/// @details 플레이어 공격력과 플레이어 데미지 배율, 그리고 무기 자체 데미지 배율을 모두 곱해서 최종 데미지를 산출
DamageInfo  Equipment::CalculateDamge(float dmgMultiplier)
{
	Player* player = GAMEMANAGER->GetPlayer();
	Info playerInfo = player->GetInfo();

	DamageInfo dmg;
	dmg._attacker = player;

	int32 rand = RandomRange(0,100); // 0~1 사이 랜덤값
	dmg._isCritical = rand <= (int32)playerInfo._crtRate;

	float base = playerInfo._atk * playerInfo._dmgMultiplier * dmgMultiplier;
	dmg._finalDamage = static_cast<int32>(base * (dmg._isCritical ? playerInfo._crtMultplier : 1.0f));
	//cout << "최종 데미지 : " << dmg._finalDamage << endl;
	return dmg;
}

Vec3 Equipment::SpawnRandomPositionAroundPlayer()
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

/// @brief 탄환 발사 위치 계산
/// @details 플레이어 위치 기준 마우스 방향으로 일정 거리(_firePosLength) 떨어진 지점
/// @return Vec2 발사 위치
Vec3 Equipment::GetFirePos(float firePosLength)
{
	Vec3 firePos = GAMEMANAGER->GetPlayer()->GetTransform()->GetPosition();
	Vec3 dir = GetMousePosToPlayerDir();

	// 플레이어 위치에서 마우스 방향으로 _firePosLength 만큼 이동
	firePos += dir * firePosLength;

	return firePos;
}

/// @brief 플레이어 위치에서 마우스 위치를 월드 좌표로 변환 후 방향 벡터 계산
/// @return 정규화된 방향 벡터 (Vec2)
Vec3 Equipment::GetMousePosToPlayerDir()
{
	POINT mousePos = INPUT->GetMousePos();
	Vec3 mouseWorldPos = SCENE->ScreenToWorld(Vec2(mousePos.x, mousePos.y));
	Vec3 playerPos = GAMEMANAGER->GetPlayer()->GetTransform()->GetPosition();

	float dirX = mouseWorldPos.x - playerPos.x;
	float dirY = mouseWorldPos.y - playerPos.y;

	Vec3 dir = { dirX, dirY,0 };
	dir.Normalize();

	return dir;
}
