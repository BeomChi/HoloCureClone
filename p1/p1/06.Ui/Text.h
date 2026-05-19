#pragma once
#include "Ui.h"



class Text : public Ui
{
	using Super = Ui;
public:
	Text();
	virtual ~Text() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetText(const wstring& text) { _text = text; }
	wstring GetText() const { return _text; }

	void SetFontSize(const int32 fontSize);
	int32 GetFontSize() const { return _fontSize; }

	void SetColor(const COLORREF color) { _color = color; }
protected:
	wstring _text;
	int32 _fontSize = 16;
	COLORREF _color = RGB(255, 255, 255);
};

