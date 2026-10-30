#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(ComPtr<ID3D11Device> device)	
	: Super(ResourceType::Mesh), _device(device)
{
}

Mesh::~Mesh()
{
	SAFE_DELETE(_geometry);
	SAFE_DELETE(_vertexBuffer);
	SAFE_DELETE(_indexBuffer);
}

void Mesh::CreateDefautRectangle()
{
	// VertexData
	_geometry = new Geometry<VertexTextureData>();
	GeometryHelper::CreateRectangle(_geometry);

	// VertexBuffer
	_vertexBuffer = new VertexBuffer(_device);
	_vertexBuffer->Create(_geometry->GetVertices());

	// IndexBuffer
	_indexBuffer = new IndexBuffer(_device);
	_indexBuffer->Create(_geometry->GetIndices());
}
