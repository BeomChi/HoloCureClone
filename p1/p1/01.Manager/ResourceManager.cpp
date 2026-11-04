#include "pch.h"
#include "ResourceManager.h"
#include "97.Engin/Resource/Texture.h"
#include "97.Engin/Resource/Animation.h"
#include "97.Engin/Resource/Material.h"
#include "97.Engin/Resource/Shader.h"
#include "97.Engin/Resource/Mesh.h"
#include "97.Engin/Resource/Sprite.h"
#include "../05.Resource/Sound/Sound.h"


ResourceManager::ResourceManager(ComPtr<ID3D11Device> device) : _device(device)
{
}

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
	for (auto& resourceMap : _resources)
	{
		for (auto& resource : resourceMap)
		{
			SAFE_DELETE(resource.second);
		}

		resourceMap.clear();
	}

	/*for (auto& item : _textures)
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

	_sound.clear();*/
}

Texture* ResourceManager::LoadTexture(const wstring& key, const wstring& path, uint32 transparent)
{
	Texture* texture = Get<Texture>(key);
	if (texture != nullptr)
		return texture;

	fs::path fullPath = _resourcePath / path;

	texture = new Texture(_device);

	texture->SetName(key);
	texture->Create(fullPath.wstring());
	Add(texture->GetName(), texture);

	//texture->Loadbmp(_hwnd, fullPath.c_str());
	//texture->SetTransparent(transparent);
	//_textures[key] = texture;

	return texture;
}

Sprite* ResourceManager::CreateSprite(const wstring& key, Texture* texture, int32 x, int32 y, 
	int32 cx, int32 cy)
{
	Sprite* sprite = Get<Sprite>(key);
	if (sprite != nullptr)
		return sprite;


	if (cx == 0)
		cx = texture->GetSize().x;

	if (cy == 0)
		cy = texture->GetSize().y;

	sprite = new Sprite(texture, x, y, cx, cy);
	sprite->SetName(key);
	Add(sprite->GetName(), sprite);
	//_sprites[key] = sprite;

	return sprite;
}

Animation* ResourceManager::CreateAnimator(const wstring& key)
{
	Animation* ani = Get<Animation>(key);
	if (ani != nullptr)
		return ani;

	ani = new Animation();
	ani->SetName(key);
	Add(ani->GetName(), ani);

	return ani;
}

Sound* ResourceManager::LoadSound(const wstring& key, const wstring& path)
{
	Sound* sound = Get<Sound>(key);
	if (sound != nullptr)
		return sound;

	fs::path fullPath = _resourcePath / path;

	sound = new Sound();
	sound->SetName(key);
	sound->LoadWave(fullPath);
	Add(sound->GetName(), sound);

	return sound;
}

void ResourceManager::CreateDefaultTexture()
{
	{
		fs::path fullPath = _resourcePath / L"¿¤µû²ô.png";
		auto texture = new Texture(_device);
		texture->SetName(L"¿¤·¼·¹");
		texture->Create(fullPath.wstring());
		Add(texture->GetName(), texture);
	}
	{
		fs::path fullPath = _resourcePath / L"Sprite\\Player\\GuraAniLeft.bmp";
		auto texture = new Texture(_device);
		texture->SetName(L"Gura");
		texture->Create(fullPath.wstring());
		Add(texture->GetName(), texture);
	}


}

void ResourceManager::CreateDefaultAnimation()
{
	Animation* animation = new Animation();

	animation->SetName(L"GuraAnim");
	animation->SetTexture(Get<Texture>(L"Gura"));
	animation->SetLoop(true);

	animation->AddKeyframe(Keyframe{ Vec2{0.f,34.f},Vec2{64.f,34.f},0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{64.f,34.f},Vec2{64.f,34.f},0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{128.f,34.f},Vec2{64.f,34.f},0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{192.f,34.f},Vec2{64.f,34.f},0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{256.f,34.f},Vec2{64.f,34.f},0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{320.f,34.f},Vec2{64.f,34.f},0.1f });

	Add(animation->GetName(), animation);


}

void ResourceManager::CreateDefaultShader()
{
	// Shaders vertex
	VertexShader* vertexShader = new VertexShader(_device);
	vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");

	// input layout
	InputLayout* inputLayout = new InputLayout(_device);
	inputLayout->Create(VertexTextureData::descs, vertexShader->GetBlob());

	// Shader pixel
	PixelShader* pixelShader = new PixelShader(_device);
	pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	Shader* shader = new Shader();
	shader->SetName(L"Default");
	shader->_vertexShader = vertexShader;
	shader->_inputLayout = inputLayout;
	shader->_pixelShader = pixelShader;
	Add(shader->GetName(), shader);
}

void ResourceManager::CreateDefaultMaterial()
{
	Material* material = new Material();
	material->SetName(L"Default");
	material->SetShader(Get<Shader>(L"Default"));
	material->SetTexture(Get<Texture>(L"¿¤·¼·¹"));
	Add(material->GetName(), material);
}

void ResourceManager::CreateDefaultMesh()
{
	Mesh* mesh = new Mesh(_device);
	mesh->SetName(L"Rectangle");
	mesh->CreateDefautRectangle();
	Add(mesh->GetName(), mesh);
}
