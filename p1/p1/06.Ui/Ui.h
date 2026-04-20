#pragma once
#include "../03.Object/GameObject.h"

class Ui : public GameObject
{
	using Super = GameObject;
public:
	Ui();
	virtual ~Ui();

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);


	// UI 관련 함수들
	// UI의 위치와 크기를 기준으로 하는 사각형 반환
	RECT GetRect();

	// UI의 위치와 크기를 기준으로 마우스가 해당 UI 영역에 있는지 확인
	bool IsMouseInRect();


};