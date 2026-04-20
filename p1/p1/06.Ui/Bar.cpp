#include "pch.h"
#include "Bar.h"
#include "../05.Resource/2D/Sprite.h"

Bar::Bar()
{
}

Bar::~Bar()
{
}

void Bar::Init()
{
	Super::Init();
}

void Bar::Update()
{
	Super::Update();
	
	if (_maxValue <= 0.f) 
		return;

	//float ratio = _currentValue / _maxValue;
	//ratio = clamp(ratio, 0.f, 1.f);


	// X축 길이만 비율 조정 (Y는 고정)
	//SetSize({ _barLength * ratio, _size.y });

	// 좌측 고정 위치 기준
	//SetPos(_originPos);
}

void Bar::Render(HDC hdc)
{
	if (_sprites == nullptr)
		return;

	float ratio = _currentValue / _maxValue;
	int fullWidth = _sprites->GetSize().x;
	int fullHeight = _sprites->GetSize().y;

	int srcWidth = static_cast<int>(fullWidth * ratio);
	int dstWidth = static_cast<int>(_size.x * ratio);

	::TransparentBlt(
		hdc,
		(int32)_pos.x,					// 왼쪽 정렬을 위해 얘는 사이즈의 반 값을 안뺌
		(int32)_pos.y - _size.y / 2,
		dstWidth,
		(int32)_size.y,
		_sprites->GetDC(),
		_sprites->GetPos().x,
		_sprites->GetPos().y,
		srcWidth,
		fullHeight,
		_sprites->GetTransparent());
	
}

void Bar::SetValue(float current, float max)
{
	cout << "[Bar::SetValue] 호출됨: " << current << " / " << max << endl;
	_currentValue = current;
	_maxValue = max;
}

void Bar::SetBarLength(float length)
{
	_barLength = length;
	_size.x = _barLength;
}

//void Bar::SetOriginPos(Vec2 pos)
//{
//	_originPos = pos;
//	SetPos(_originPos);
//}

