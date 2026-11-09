#include "pch.h"
#include "Texture.h"

Texture::Texture(ComPtr<ID3D11Device> device) :	Super(ResourceType::Texture), _device(device)
{
}

Texture::~Texture()
{

}

void Texture::Create(const wstring& path)
{
	std::filesystem::path absolutePath =
		std::filesystem::absolute(path);

	std::string pathStr(path.begin(), path.end());

	std::cout << "Load Path: " << pathStr << std::endl;
	std::cout << "Absolute Path: "
		<< absolutePath.string() << std::endl;

	std::cout << "Exists: "
		<< std::filesystem::exists(path) << std::endl;

	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	assert(!path.empty());

	assert(std::filesystem::exists(path));

	HRESULT hr = LoadFromWICFile(path.c_str(), DirectX::WIC_FLAGS_NONE, &md, img);
	CHECK(hr);
	std::cout << "WIC: " << std::hex << hr << std::endl;

	hr = CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView.GetAddressOf());
	CHECK(hr);
	std::cout << "SRV: " << std::hex << hr << std::endl;

	_size.x = md.width;
	_size.y = md.height;
}
