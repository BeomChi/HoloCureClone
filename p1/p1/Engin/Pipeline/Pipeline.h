#pragma once

struct PipelineInfo
{
	InputLayout* inputLayout;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	RasterizerState* rasterizerState;
	BlendState* blendState;
	D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
};


class Pipeline
{
public:
	Pipeline(ComPtr<ID3D11DeviceContext> deviceContext);
	~Pipeline();

	void UpdatePipeline(PipelineInfo info);

	void SetVertexBuffer(VertexBuffer* vertexBuffer);
	void SetIndexBuffer(IndexBuffer* indexBuffer);

	template<typename T>
	void SetConstantBuffer(uint32 slot, uint32 scope, T* constantBuffer)
	{
		if (scope & SS_VertexShader)
		{
			_deviceContext->VSSetConstantBuffers(slot, 1, constantBuffer->GetComPtr().GetAddressOf());
		}

		if (scope & SS_PixelShader)
		{
			_deviceContext->PSSetConstantBuffers(slot, 1, constantBuffer->GetComPtr().GetAddressOf());
		}
	}

	void SetTexture(uint32 slot, uint32 scope, Texture* texture);
	void SetSamplerState(uint32 slot, uint32 scope, SamplerState* samplerState);

	void Draw(uint32 vertexCount, uint32 startVertexLocation);
	void DrawIndexed(uint32 indexCount, uint32 startIndexLocation, uint32 baseVertexLocation);

private:
	ComPtr<ID3D11DeviceContext> _deviceContext;
};

