#pragma once
#include "Ui.h"

class Sprite;

enum ButtonState
{
	BS_Default,
	BS_Pressed,
	BS_Clicked,

	BS_MaxCount,
};


class Button : public Ui
{
	using Super = Ui;
public:
	Button();
	virtual ~Button() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	
	Sprite* GetSprite(ButtonState state) { return _sprites[state]; }

	void SetCurrentSprite(Sprite* sprite) { _currentSprite = sprite; }
	void SetSprite(Sprite* sprite, ButtonState state) { _sprites[state] = sprite; }
	void SetButtonState(ButtonState state);

protected:
	Sprite* _currentSprite = nullptr;
	Sprite* _sprites[BS_MaxCount] = {};
	ButtonState _state = BS_Default;

	float _sumTime = 0;

public:
	template<typename T>
	void AddOnClickDelegate(T* owner, void(T::* func)())
	{
		_onClick = [owner, func]()
			{
				(owner->*func)();
			};
	}

	function<void(void)> _onClick = nullptr;
};

