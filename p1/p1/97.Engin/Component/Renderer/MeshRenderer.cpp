#include "pch.h"
#include "MeshRenderer.h"
#include "97.Engin/Resource/Mesh.h"


MeshRenderer::MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	: Super(ComponentType::MeshRenderer),_device(device)
{


}

MeshRenderer::~MeshRenderer()
{


}




