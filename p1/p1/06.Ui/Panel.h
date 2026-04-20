#pragma once
#include "Ui.h"


class Panel : public Ui
{
	using Super = Ui;
public:
	Panel();
	virtual ~Panel() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void AddPanel(Ui* panel);
	void RemovePanel(Ui* panel);
	
	void Clear();


private:
	vector<Ui*> _panels; // 패널 리스트
};

