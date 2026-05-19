#include "pch.h"
#include "ResourceManager.h"
#include "../05.Resource/2D/Sprite.h"
#include "../05.Resource/2D/Texture.h"
#include "../05.Resource/2D/Animator.h"
#include "../05.Resource/Sound/Sound.h"


ResourceManager::~ResourceManager()
{
	Clear();
}

void ResourceManager::Init(HWND hwnd, fs::path resourcePath)
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;
}

void ResourceManager::Clear()
{
	for (auto& item : _textures)
		SAFE_DELETE(item.second);

	_textures.clear();

	for (auto& item : _sprites)
		SAFE_DELETE(item.second);

	_sprites.clear();

	for (auto& item : _animators)
		SAFE_DELETE(item.second);

	_animators.clear();

	for (auto& item : _sound)
		SAFE_DELETE(item.second);

	_sound.clear();
}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent)
{
	if (_textures.find(key) != _textures.end())
		return _textures[key];

	fs::path fullPath = _resourcePath / path;

	Texture* texture = new Texture();
	texture->Loadbmp(_hwnd, fullPath.c_str());
	texture->SetTransparent(transparent);
	_textures[key] = texture;

	return texture;
}

Sprite* ResourceManager::CreateSprite(const wstring& key, Texture* texture, int32 x, int32 y, 
	int32 cx, int32 cy)
{
	if (_sprites.find(key) != _sprites.end())
		return _sprites[key];


	if (cx == 0)
		cx = texture->GetSize().x;

	if (cy == 0)
		cy = texture->GetSize().y;

	Sprite* sprite = new Sprite(texture, x, y, cx, cy);
	_sprites[key] = sprite;

	return sprite;
}

Animator* ResourceManager::CreateAnimator(const wstring& key)
{
	if (_animators.find(key) != _animators.end())
		return _animators[key];

	Animator* ani = new Animator();
	_animators[key] = ani;

	return ani;
}

Sound* ResourceManager::LoadSound(const wstring& key, const wstring& path)
{
	if (_sound.find(key) != _sound.end())
		return _sound[key];

	fs::path fullPath = _resourcePath / path;

	Sound* sound = new Sound();
	sound->LoadWave(fullPath);
	_sound[key] = sound;

	return sound;
}
