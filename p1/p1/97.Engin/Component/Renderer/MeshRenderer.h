#pragma once
#include "97.Engin/Component/Component.h"
#include "97.Engin/Resource/Material.h"
#include "97.Engin/Resource/Shader.h"

class Mesh;
class Material;

class MeshRenderer : public Component
{
	using Super = Component;
public:
	MeshRenderer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	virtual ~MeshRenderer();


	void SetMesh(Mesh* mesh) { _mesh = mesh; }
	void SetTexture(Texture* texture) { _material->SetTexture(texture); }
	void SetMaterial(Material* material) { _material = material; }
	void SetShader(Shader* shader) { _material->SetShader(shader); }

	Material* GetMaterial() { return _material; }
	VertexShader* GetVertexShader() { return GetMaterial()->GetShader()->GetVertexShader(); }
	InputLayout* GetInputLayout() { return GetMaterial()->GetShader()->GetInputLayout(); }
	PixelShader* GetPixelShader() { return GetMaterial()->GetShader()->GetPixelShader(); }

	Mesh* GetMesh() { return _mesh; }
	Texture* GetTexture() { return GetMaterial()->GetTexture(); }

private:
	ComPtr<ID3D11Device> _device;

	friend class RenderManager;

	// 얘네 수명 관리는 ResourceManager에서 함 그래서 여기서 SAFE_DELETE 할 필요 없음
	// 대신 디폴트 대신 따로 만든 애들은 반드시 ResourceManager에 있는 Add로 반드시 넣어주기
	// 안그러면 줄줄 샘
	Mesh* _mesh;
	Material* _material;

};

