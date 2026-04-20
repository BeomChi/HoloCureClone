#pragma once
#include "Image.h"

class Sprite;




class Bar : public Image
{
	using Super = Image;
public:
	Bar();
	virtual ~Bar() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetValue(float current, float max);
	void SetBarLength(float length);      // 전체 길이 설정
	//void SetOriginPos(Vec2 pos);          // 좌측 기준 고정 위치 설정
	


protected:
	float _barLength = 0.f;       // 전체 길이
	float _currentValue = 0.f;
	float _maxValue = 0.f;

	//Vec2 _originPos = { 0, 0 };     // 항상 고정된 시작 위치 (좌측 기준)
};

