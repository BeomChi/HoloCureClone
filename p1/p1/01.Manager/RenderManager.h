#pragma once
#include "RenderHelper.h"


class RenderManager
{
public:
	RenderManager(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext);
	~RenderManager();

	void Init();
	void Update(Graphics* graphics);

private:
	void PushCameraData();
	void PushUiCameraData();
	void PushTransformData();
	void PushAnimationData();

	void GettherRenderableObjects();
	void RenderObjects(vector<GameObject*> renderObject);


private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
	Pipeline* _pipeline;

private:
	CameraData _cameraData;
	ConstantBuffer<CameraData>* _cameraBuffer;

	TransformData _transformData;
	ConstantBuffer<TransformData>* _transformBuffer;

	AnimationData _animationData;
	ConstantBuffer<AnimationData>* _animationBuffer;

private:
	RasterizerState* _rasterizerState;
	SamplerState* _samplerState;
	BlendState* _blendState;

	vector<GameObject*> _renderObjects;
	vector<GameObject*> _renderUiObjects;
	Matrix uiProjection;
};

