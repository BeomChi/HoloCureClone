#pragma once
#include "97.Engin/Resource/ResourceBase.h"


class Texture;
class Sprite;
class Animation;
class Sound;

class ResourceManager
{
public:
	ResourceManager(ComPtr<ID3D11Device> device);
	~ResourceManager();

	void Init(HWND hwnd, fs::path resourcePath);
	void Clear();

	const fs::path& GetResourcePath() { return _resourcePath; }

	template<typename T>
	T* Load(const wstring& key, const wstring& path);

	template<typename T>
	bool Add(const wstring& key, T* obj);

	template<typename T>
	T* Get(const wstring& key);

	template<typename T>
	ResourceType GetResourceType();

	//Texture* GetTexture(const wstring& key) { return _textures[key]; }
	Texture* LoadTexture(const wstring& key, const wstring& path, uint32 transparent = RGB(255, 0, 255));

	//Sprite* GetSprite(const wstring& key) { return _sprites[key]; }
	Sprite* CreateSprite(const wstring& key, Texture* texture, int32 x = 0, int32 y = 0, int32 cx = 0, int32 cy = 0);

	//Animator* GetAnimator(const wstring& key) { return _animators[key]; }
	Animation* CreateAnimator(const wstring& key);

	//Sound* GetSound(const wstring& key) { return _sound[key]; }
	Sound* LoadSound(const wstring& key, const wstring& path);

private:
	void CreateDefaultTexture();
	void CreateDefaultAnimation();
	void CreateDefaultShader();
	void CreateDefaultMaterial();
	void CreateDefaultMesh();

private:
	HWND _hwnd = {};
	fs::path _resourcePath;

	/*unordered_map<wstring, Texture*> _textures;
	unordered_map<wstring, Sprite*> _sprites;
	unordered_map<wstring, Animator*> _animators;
	unordered_map<wstring, Sound*>_sound;*/

private:
	ComPtr<ID3D11Device> _device;

	using KeyObjMap = map<wstring, ResourceBase*>;
	array<KeyObjMap, RESOURCE_TYPE_COUNT> _resources;

};

template<typename T>
inline T* ResourceManager::Load(const wstring& key, const wstring& path)
{
	ResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(resourceType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return static_cast<T*>(findIt->second);

	T* obj = new T();
	obj->Load(path);
	keyObjMap[key] = obj;


	return obj;
}

template<typename T>
inline bool ResourceManager::Add(const wstring& key, T* obj)
{
	ResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(resourceType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return false;

	keyObjMap[key] = obj;

	return true;
}

template<typename T>
inline T* ResourceManager::Get(const wstring& key)
{
	ResourceType resourceType = GetResourceType<T>();
	KeyObjMap& keyObjMap = _resources[static_cast<uint8>(resourceType)];

	auto findIt = keyObjMap.find(key);
	if (findIt != keyObjMap.end())
		return static_cast<T*>(findIt->second);

	return nullptr;
}

template<typename T>
inline ResourceType ResourceManager::GetResourceType()
{
	if (is_same_v<T, Texture>)
		return ResourceType::Texture;
	if (is_same_v<T, Mesh>)
		return ResourceType::Mesh;
	if (is_same_v<T, Animation>)
		return ResourceType::Animation;
	if (is_same_v<T, Shader>)
		return ResourceType::Shader;
	if (is_same_v<T, Material>)
		return ResourceType::Material;
	if (is_same_v<T, Sound>)
		return ResourceType::Sound;
	if (is_same_v<T, Sprite>)
		return ResourceType::Sprite;

	assert(false);
	return ResourceType::None;
}
