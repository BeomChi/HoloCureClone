#include "pch.h"
#include "Text.h"


Text::Text()
{
	SetLayer(LAYER_UI);
	_size = { 100.f,50.f };
}

Text::~Text()
{
}

void Text::Init()
{
	Super::Init();
}

void Text::Update()
{
	Super::Update();
	
	

}

void Text::Render(HDC hdc)
{
	float currentXSize = _size.x;
	float nextXSize = _fontSize * _text.size() * 1.2f;

	// 글자 길이가 사이즈를 넘어가면 안나오는 현상을 개선하기 위해 증설 작업
	if (currentXSize <= nextXSize)
		_size.x = nextXSize;



	if (!_text.empty())
	{
		Utils::DrawTextFont(hdc, _pos, _text, _fontSize, _color, L"맑은 고딕", (int)_size.x, (int)_size.y);
	}
	else
	{
		Utils::DrawRect(hdc, _pos, _size.x, _size.y);
	}
}

void Text::SetFontSize(const int32 fontSize)
{
	_fontSize = fontSize;
	_size.x = fontSize * _text.size() * 1.2f; // 글자 수에 따라 가로 크기 조정 (글자당 0.6배)
	_size.y = fontSize * 1.2f;
}

