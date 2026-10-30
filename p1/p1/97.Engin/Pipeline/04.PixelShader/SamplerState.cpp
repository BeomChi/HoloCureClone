#include "pch.h"
#include "SamplerState.h"

SamplerState::SamplerState(ComPtr<ID3D11Device> device) : _device(device)
{
}

SamplerState::~SamplerState()
{
}

void SamplerState::Create()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	// wrap : 타일링
	// borader : 빈 공간 다른 색상으로 채우기
	// clamp : 뭐라고 설명을 해야하지? 뭔가 뭔가인
	// mirror : 반사
	// mirror one : 얘도 클램프처럼 나오네

	desc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.BorderColor[0] = 1.f;
	desc.BorderColor[1] = 0.f;
	desc.BorderColor[2] = 0.f;
	desc.BorderColor[3] = 1.f;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.MaxLOD = FLT_MAX;
	desc.MinLOD = FLT_MIN;
	desc.MipLODBias = 0.f;

	HRESULT hr = _device->CreateSamplerState(&desc, _samplerState.GetAddressOf());
	CHECK(hr);
}