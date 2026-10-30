#pragma once
#include "97.Engin/Resource/ResourceBase.h"

enum class SoundType
{
	BGM,
	Normal,
};

class Sound : public ResourceBase
{
	using Super = ResourceBase;
public:
	Sound();
	virtual ~Sound();

	bool LoadWave(fs::path fullPath);
	void Play(bool loop = false);
	void Stop(bool reset = false);

private:
	virtual void Load(const wstring& path) {}
	virtual void Save(const wstring& path) {}

private:
	LPDIRECTSOUNDBUFFER _soundBuffer = nullptr;
	DSBUFFERDESC _bufferDesc = {};
};

