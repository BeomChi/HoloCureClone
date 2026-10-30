#pragma once
#include "ResourceBase.h"

class Mesh : public ResourceBase
{
    using Super = ResourceBase;
public:
    Mesh(ComPtr<ID3D11Device> device);
    virtual ~Mesh();

    void CreateDefautRectangle();

    VertexBuffer* GetVertexBuffer() { return _vertexBuffer; }
    IndexBuffer* GetIndexBuffer() { return _indexBuffer; }


private:
    ComPtr<ID3D11Device> _device;


    Geometry<VertexTextureData>* _geometry;
    VertexBuffer* _vertexBuffer = nullptr;
    IndexBuffer* _indexBuffer = nullptr;
};

