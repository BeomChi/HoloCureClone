#include "pch.h"
#include "Panel.h"


Panel::Panel()
{
	SetLayer(LAYER_UI);
}

Panel::~Panel()
{
	Clear(); // 패널 제거
}

void Panel::Init()
{
	Super::Init();

	for (Ui* panel : _panels)
	{
		if (panel != nullptr)
		{
			panel->Init();
		}
	}
}

void Panel::Update()
{
	Super::Update();
	
	for (Ui* panel : _panels)
	{
		if (panel != nullptr)
		{
			if (!panel->GetIsActivity())
				continue;

			panel->Update();
		}
	}
}

void Panel::Render(HDC hdc)
{
	Super::Render(hdc);
	for (Ui* panel : _panels)
	{
		if (panel != nullptr)
		{
			if (!panel->GetIsActivity())
				continue;

			panel->Render(hdc);
		}
	}
	
}

void Panel::AddPanel(Ui* panel)
{
	if (panel == nullptr)
		return;

	_panels.push_back(panel);
}

void Panel::RemovePanel(Ui* panel)
{
	if (panel == nullptr)
		return;

	auto it = find(_panels.begin(), _panels.end(), panel);
	if (it != _panels.end())
	{
		_panels.erase(it);
	}
}

void Panel::Clear()
{
	for (Ui* panel : _panels)
	{
		if (panel != nullptr)
		{
			SAFE_DELETE(panel);
		}
	}

	_panels.clear();
}

