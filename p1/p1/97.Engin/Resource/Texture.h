#pragma once
#include "ResourceBase.h"


class Texture : public ResourceBase
{
	using Super = ResourceBase;
public:
	Texture(ComPtr<ID3D11Device> device);
	~Texture();

	ComPtr<ID3D11ShaderResourceView> GetComPtr() { return _shaderResourceView; }

	void Create(const wstring& path);
	void Create(HBITMAP bitmap);

	Vec2 GetSize() { return _size; }

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
	ComPtr<ID3D11Texture2D> _texture2D = nullptr;
	Vec2 _size = { 0.f,0.f };
};

