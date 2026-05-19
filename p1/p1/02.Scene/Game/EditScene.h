#pragma once
#include "../Scene.h"

class GameObject;
class Panel;

class EditScene : public Scene
{
	using Super = Scene;
public:
	EditScene();
	virtual ~EditScene() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	bool InSideObject(GameObject* obj);
	void SelectObject();
	void MoveSelectedObject();

	bool SaveScene(const wstring& filePath);

private:
	GameObject* _selectedObject = nullptr;
	Panel* _panel = nullptr;

	bool _isDragging = false;
	Vec2 _dragOffset = {};
};

