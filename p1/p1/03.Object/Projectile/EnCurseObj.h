#pragma once
#include "../GameObject.h"

struct EnCurseObjInfo
{
	float _dmg = 0;
	float _speed = 0;

	int32 _count = 0;
};



class Animator;
class AnimationComponent;


class EnCurseObj :   public GameObject
{
	using Super = GameObject;
public:
	EnCurseObj();
	virtual ~EnCurseObj() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	//void SetDir(DirState dir) { _dir = dir; }
	void SetDmg(float dmg) { _info._dmg = dmg; }

	virtual void OnTriggerEnter(Collider* collider, Collider* other) override;
	virtual void OnTriggerExit(Collider* collider, Collider* other) override;

	virtual void Reset() override;

	void SetState(DirState dir);
	void UpdateAnimation();
private:
	EnCurseObjInfo _info;
	DirState _dir;

	Animator* _dirAni[2] = {};
	AnimationComponent* _ani = nullptr;
};

