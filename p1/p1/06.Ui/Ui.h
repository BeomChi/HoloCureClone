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



	RECT GetRect();
	bool IsMouseInRect();


};