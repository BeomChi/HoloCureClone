#include "pch.h"
#include "DamageText.h"
#include "01.Manager/TimeManager.h"
#include "01.Manager/SceneManager.h"

DamageText::DamageText()
{
}

DamageText::~DamageText()
{
}

void DamageText::Init()
{
	Super::Init();
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

	if (!_text.empty())
	{
		Utils::DrawTextFont(hdc, screenPos, _text, _fontSize, _color, L"맑은 고딕", (int)_size.x, (int)_size.y);
	}
	else
	{
		Utils::DrawRect(hdc, _pos, _size.x, _size.y);
	}
	//Super::Render(hdc);
}

void DamageText::Reset()
{
	_duration = _baseDuration;
	_velocity = { 0, -1.2f }; // 텍스트가 위로 떠오르는 속도
	SetColor(RGB(255, 255, 255));
}

void DamageText::ShowDamage(float damage, Vec2 pos, bool isCritical)
{
	SetText(std::to_wstring(static_cast<int32>(damage)));
	SetPos(pos);

	if (isCritical)
	{
		SetColor(RGB(255, 0, 0));
	}
}

