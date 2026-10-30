#pragma once

#define GET_SINGLE(classname)	classname::GetInstance()

#define SAFE_DELETE(ptr)		\
	if (ptr)					\
	{							\
		delete ptr;				\
		ptr = nullptr;			\
	}

#define CHECK(p) assert(SUCCEEDED(p))

#define GAME GGame
#define SCENE GAME->GetSceneManager()
#define TIME GAME->GetTimeManager()
#define INPUT GAME->GetInputManager()
#define GAMEMANAGER GAME->GetGameManager()
#define RESOURCE GAME->GetResourceManager()
#define EQUIPMENT GAME->GetEquipmentManager()
#define SOUND GAME->GetSoundManager()
#define RENDER GAME->GetRenderManager()

#ifdef _DEBUG
#define LOG(x) std::cout << x << std::endl;
#else
#define LOG(x)
#endif