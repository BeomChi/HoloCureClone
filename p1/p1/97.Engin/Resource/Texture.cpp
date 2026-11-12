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

void Texture::Create(HBITMAP bitmap)
{
	BITMAP bm{};
	GetObject(bitmap, sizeof(BITMAP), &bm);

	cout
		<< "Bitmap Width: " << bm.bmWidth
		<< ", Height: " << bm.bmHeight
		<< ", BitsPixel: " << bm.bmBitsPixel
		<< endl;

	BITMAPINFO bi{};
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = bm.bmWidth;
	bi.bmiHeader.biHeight = -bm.bmHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;

	vector<uint8> pixels(
		bm.bmWidth * bm.bmHeight * 4
	);
	
	HDC memDC = CreateCompatibleDC(GAME->GetHdcBack());

	int result = GetDIBits(
		memDC,
		bitmap,
		0,
		bm.bmHeight,
		pixels.data(),
		&bi,
		DIB_RGB_COLORS
	);

	for (size_t i = 0; i < pixels.size(); i += 4)
	{
		pixels[i + 3] = 255;
	}

	DeleteDC(memDC);

	cout << "GetDIBites: " << result << endl;

	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = bm.bmWidth;
	desc.Height = bm.bmHeight;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA data{};
	data.pSysMem = pixels.data();
	data.SysMemPitch = bm.bmWidth * 4;

	HRESULT hr = _device->CreateTexture2D(
		&desc,
		&data,
		_texture2D.GetAddressOf()
	);
	CHECK(hr);

	hr = _device->CreateShaderResourceView(
		_texture2D.Get(),
		nullptr,
		_shaderResourceView.GetAddressOf()
	);
	CHECK(hr);

	cout << "_shaderResourceView: "
		<< (_shaderResourceView.Get() != nullptr)
		<< endl;

	cout << "_texture2D: "
		<< (_texture2D.Get() != nullptr)
		<< endl;

	_size.x = bm.bmWidth;
	_size.y = bm.bmHeight;
}
