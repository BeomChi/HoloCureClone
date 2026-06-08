#pragma once
#include "Singleton.h"
#include "Signal.hpp"

class Player;


class GameManager : public Singleton<GameManager>
{
	friend class Singleton<GameManager>;

public:
	Signal<bool> OnGameOverHudActivity;
	Signal<bool> OnDebugShow;
	void Update();

	void SetPlayer(Player* player) 
	{ 
		_player = player; 
		//cout << "[DEBUG] GameManager::SetPlayer - 林家: " << _player << endl;
	}
	Player* GetPlayer() 
	{ 
		//cout << "[DEBUG] GameManager::GetPlayer - 馆券 林家: " << _player << endl;
		return _player; 
	}

	float GetPlayeTime() { return _playTime; }

	int32 GetCurrentStage() { return _stage; }

	void SetState(GameState state) { _state = state; }
	GameState GetState() const { return _state; }

	void GameOver();
	void SetDebugShow(bool isShow) { OnDebugShow(isShow); _isDebugShow = isShow; }
	bool GetDebugShow() const { return _isDebugShow; }

private:
	Player* _player = nullptr;
	float _playTime = 0.f;
	bool _isDebugShow = false;

	int32 _stage = 0;
	GameState _state = GameState::None;

	int32 _toTalKillCount = 0;
};

