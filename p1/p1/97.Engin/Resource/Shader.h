#pragma once
#include "ResourceBase.h"


class Shader : public ResourceBase
{
	using Super = ResourceBase;
public:
	Shader();
	virtual ~Shader();

	InputLayout* GetInputLayout() { return _inputLayout; }
	VertexShader* GetVertexShader() { return _vertexShader; }
	PixelShader* GetPixelShader() { return _pixelShader; }

private:
	friend class ResourceManager;
	InputLayout* _inputLayout = nullptr;
	VertexShader* _vertexShader;
	PixelShader* _pixelShader;
};
