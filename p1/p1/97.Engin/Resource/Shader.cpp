#include "pch.h"
#include "Shader.h"

Shader::Shader() : Super(ResourceType::Shader)
{
	
}

Shader::~Shader()
{
	SAFE_DELETE(_inputLayout);
	SAFE_DELETE(_vertexShader);
	SAFE_DELETE(_pixelShader);
}
