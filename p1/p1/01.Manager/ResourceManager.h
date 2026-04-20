#pragma once
#include "Singleton.h"

class Texture;
class Sprite;
class Animator;
class Sound;

class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;
public:
	~ResourceManager();

	void Init(HWND hwnd, fs::path resourcePath);
	void Clear();

	const fs::path& GetResourcePath() { return _resourcePath; }

	Texture* GetTexture(const wstring& key) { return _textures[key]; }
	Texture* LoadTexture(const wstring& key, const wstring& path, uint32 transparent = RGB(255, 0, 255));

	Sprite* GetSprite(const wstring& key) { return _sprites[key]; }
	Sprite* CreateSprite(const wstring& key, Texture* texture, int32 x = 0, int32 y = 0, int32 cx = 0, int32 cy = 0);

	Animator* GetAnimator(const wstring& key) { return _animators[key]; }
	Animator* CreateAnimator(const wstring& key);
	Sound* GetSound(const wstring& key) { return _sound[key]; }
	Sound* LoadSound(const wstring& key, const wstring& path);

private:
	HWND _hwnd = {};
	fs::path _resourcePath;

	unordered_map<wstring, Texture*> _textures;
	unordered_map<wstring, Sprite*> _sprites;
	unordered_map<wstring, Animator*> _animators;
	unordered_map<wstring, Sound*>_sound;
};

