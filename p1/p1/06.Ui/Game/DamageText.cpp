#include "pch.h"
#include "DamageText.h"
#include "01.Manager/TimeManager.h"
#include "01.Manager/SceneManager.h"
#include "01.Manager/ResourceManager.h"
#include "../../05.Resource/2D/Sprite.h"

DamageText::DamageText()
{
	
}

DamageText::~DamageText()
{
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (_sprite[j][i])
			{
				//delete _sprite[j][i];
				_sprite[j][i] = nullptr;
			}
		}
	}
}

void DamageText::Init()
{
	Super::Init();

	_sprite[0][0] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeNormal0");
	_sprite[0][1] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeNormal1");
	_sprite[0][2] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeNormal2");
	_sprite[0][3] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeNormal3");
	_sprite[0][4] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeNormal4");
	_sprite[0][5] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeNormal5");
	_sprite[0][6] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeNormal6");
	_sprite[0][7] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeNormal7");
	_sprite[0][8] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeNormal8");
	_sprite[0][9] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeNormal9");
	_sprite[1][0] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeExclusive0");
	_sprite[1][1] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeExclusive1");
	_sprite[1][2] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeExclusive2");
	_sprite[1][3] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeExclusive3");
	_sprite[1][4] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeExclusive4");
	_sprite[1][5] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeExclusive5");
	_sprite[1][6] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeExclusive6");
	_sprite[1][7] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeExclusive7");
	_sprite[1][8] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeExclusive8");
	_sprite[1][9] = GET_SINGLE(ResourceManager)->GetSprite(L"NumberTypeExclusive9");

	SetScale({ 2,2 });
	_velocity = { 0,-12 };
}

void DamageText::Update()
{
	Super::Update();

	float dt = GET_SINGLE(TimeManager)->GetDeltaTime();

	_duration -= dt;
	_pos.y += _velocity.y * dt; // 텍스트가 위로 떠오르는 효과


	if (_duration <= 0)
	{
		SetIsActivity(false); // 텍스트 비활성화
	}
}

void DamageText::Render(HDC hdc)
{
	// 월드 좌표 → 스크린 좌표로 변환 (카메라에 따라 보정됨)
	Vec2 screenPos = GET_SINGLE(SceneManager)->WorldToScreen(_pos);

	float offsetX = 0;

	for (wchar_t c : _text)
	{
		if (c < L'0' || c > L'9')
			continue;

		int digit = c - L'0';
		Sprite* digitSprite = _sprite[_currentSpriteIndex][digit];

		if (digitSprite == nullptr)
			continue;

		Vec2Int size = digitSprite->GetSize();

		float renderSizeX = (float)size.x * _scale.x;
		float renderSizeY = (float)size.y * _scale.y;

		
		if (digitSprite)
		{
			::TransparentBlt(
				hdc,							// 그릴 대상 HDC
				(int32)(screenPos.x + offsetX),	// 화면상 x좌표
				(int32)screenPos.y,				// 화면상 y좌표
				(int32)renderSizeX,					// 그릴 너비
				(int32)renderSizeY,					// 그릴 높이
				digitSprite->GetDC(),             // 스프라이트가 그려진 메모리 DC
				digitSprite->GetPos().x,          // 원본 이미지에서의 x 좌표 (부분 추출용, 보통 0)
				digitSprite->GetPos().y,          // 원본 이미지에서의 y 좌표
				digitSprite->GetSize().x,         // 원본 이미지에서의 너비
				digitSprite->GetSize().y,         // 원본 이미지에서의 높이
				digitSprite->GetTransparent());   // 투명색 (보통 RGB 값)

			offsetX += renderSizeX; // 다음 숫자 위치로 이동
		}
	}


	//Super::Render(hdc);
}

void DamageText::Reset()
{
	_duration = _baseDuration;
	_currentSpriteIndex = 0;
	_velocity = { 0, -1.2f }; // 텍스트가 위로 떠오르는 속도
	SetColor(RGB(255, 255, 255));
}

void DamageText::ShowDamage(float damage, Vec2 pos, bool isCritical)
{
	SetText(std::to_wstring(static_cast<int32>(damage)));
	SetPos(pos);

	if (isCritical)
	{
		_currentSpriteIndex = 1;
	}
}

