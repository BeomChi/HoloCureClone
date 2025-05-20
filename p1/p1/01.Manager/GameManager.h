#pragma once
#include "Singleton.h"

class Player;

class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;

public:
	void Update();

	void SetPlayer(Player* player) { _player = player; }
	Player* GetPlayer() { return _player; }

	float GetPlayeTime() { return _playTime; }

private:
	Player* _player = nullptr;
	float _playTime = 0.f;
};

