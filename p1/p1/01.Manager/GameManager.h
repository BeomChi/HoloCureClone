#pragma once
#include "Singleton.h"

class Player;

enum class GameState
{
	None,
	Title,
	InGame,
	Paused,
	GameOver,
	Clear
};

class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;

public:
	void Update();

	void SetPlayer(Player* player) { _player = player; }
	Player* GetPlayer() { return _player; }

	float GetPlayeTime() { return _playTime; }

	int32 GetCurrentStage() { return _stage; }

private:
	Player* _player = nullptr;
	float _playTime = 0.f;

	int32 _stage = 0;

	GameState _state = GameState::None;
};

