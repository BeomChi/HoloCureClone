#include "pch.h"
#include "Button.h"
#include "../01.Manager/InputManager.h"
#include "../01.Manager/TimeManager.h"
#include "../04.Component/2D/SpriteRenderer.h"
#include "97.Engin/Resource/Sprite.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Init()
{
	Super::Init();
	_spriteRenderer = GetSpriteRenderer();
	SetButtonState(BS_Default);
}

void Button::Update()
{
	Super::Update();
	POINT mousePos = INPUT->GetMousePos();
	float deltaTime = TIME->GetDeltaTime();

	if (_state == BS_Clicked)
	{
		_sumTime += deltaTime;

		if (_sumTime >= 0.2f)
		{
			_sumTime = 0;
			SetButtonState(BS_Default);
		}
	}

	if (IsMouseInRect())
	{
		if (INPUT->GetButton(KeyType::LeftMouse))
		{
			SetButtonState(BS_Pressed);
		}
		else
		{
			if (_state == BS_Pressed)
			{
				SetButtonState(BS_Clicked);

				if (_onClick)
					_onClick();
			}
		}
	}
	else
	{
		SetButtonState(BS_Default);
	}
}

void Button::Render(HDC hdc)
{
	
	/*if (_currentSprite)
	{
		::TransparentBlt(hdc,
			(int32)_pos.x - _size.x / 2,
			(int32)_pos.y - _size.y / 2,
			_size.x,
			_size.y,
			_currentSprite->GetDC(),
			_currentSprite->GetPos().x,
			_currentSprite->GetPos().y,
			_currentSprite->GetSize().x,
			_currentSprite->GetSize().y,
			_currentSprite->GetTransparent());
	}
	else
	{
		Utils::DrawRect(hdc, _pos, _size.x, _size.y);
	}*/
}

void Button::SetButtonState(ButtonState state)
{
	_state = state;

	if (_sprites[state])
	{
		SetCurrentSprite(_sprites[state]);
		_spriteRenderer->SetSprite(_currentSprite);
	}
}
