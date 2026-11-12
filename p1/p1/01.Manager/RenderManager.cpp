#include "pch.h"
#include "RenderManager.h"
#include "97.Engin/Pipeline/Pipeline.h"
#include "97.Engin/Component/Renderer/MeshRenderer.h"
#include "97.Engin/Component/Camera/Camera.h"
#include "01.Manager/SceneManager.h"
#include "02.Scene/Scene.h"
#include "03.Object/GameObject.h"
#include "04.Component/2D/SpriteRenderer.h"
#include "97.Engin/Resource/Mesh.h"
#include "97.Engin/Resource/Texture.h"
#include "97.Engin/Resource/Sprite.h"
#include "97.Engin/Component/Animation/Animator.h"
#include "97.Engin/Component/Transform/Transform.h"



RenderManager::RenderManager(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
	: _device(device), _deviceContext(deviceContext)
{
}

RenderManager::~RenderManager()
{
	SAFE_DELETE(_pipeline);
	SAFE_DELETE(_cameraBuffer);
	SAFE_DELETE(_transformBuffer);
	SAFE_DELETE(_animationBuffer);
	SAFE_DELETE(_rasterizerState);
	SAFE_DELETE(_samplerState);
	SAFE_DELETE(_blendState);
}

void RenderManager::Init()
{
	_pipeline = new Pipeline(_deviceContext);

	_cameraBuffer = new ConstantBuffer<CameraData>(_device, _deviceContext);
	_cameraBuffer->Create();

	_transformBuffer = new ConstantBuffer<TransformData>(_device, _deviceContext);
	_transformBuffer->Create();

	_animationBuffer = new ConstantBuffer<AnimationData>(_device, _deviceContext);
	_animationBuffer->Create();
	
	_rasterizerState = new RasterizerState(_device);
	_rasterizerState->Create();

	_samplerState = new SamplerState(_device);
	_samplerState->Create();

	_blendState = new BlendState(_device);
	_blendState->Create();

	/*uiProjection = Matrix::CreateOrthographicOffCenter(
		0.0f, GWinSizeX,
		GWinSizeY, 0.0f,
		-1.0f, 1.0f
	);

	uiProjection = Matrix::CreateScale(
		0.0025f,
		0.00333333f,
		1.0f
	);*/

	uiProjection = Matrix(
		0.0025f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.00333333f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

}

void RenderManager::Update(Graphics* graphics)
{
	graphics->RenderBegin();

	GettherRenderableObjects();

	PushCameraData();
	RenderObjects(_renderObjects);

	PushUiCameraData();
	RenderObjects(_renderUiObjects);


	graphics->RenderEnd();
}

void RenderManager::PushCameraData()
{
	_cameraData.matView = Camera::s_matView;
	_cameraData.matProjection = Camera::s_matProjection;
	
	_cameraBuffer->CopyData(_cameraData);
}

void RenderManager::PushUiCameraData()
{
	_cameraData.matView = Matrix::Identity;
	_cameraData.matProjection = uiProjection;
	//_cameraData.matView = Matrix::Identity;
	//_cameraData.matProjection = Matrix::CreateScale(0.5f, 0.5f, 1.f);

	/*cout << "UI PROJECTION" << endl;

	for (int i = 0; i < 4; i++)
	{
		cout
			<< _cameraData.matProjection.m[i][0] << " "
			<< _cameraData.matProjection.m[i][1] << " "
			<< _cameraData.matProjection.m[i][2] << " "
			<< _cameraData.matProjection.m[i][3] << endl;
	}*/
	_cameraBuffer->CopyData(_cameraData);
}

void RenderManager::PushTransformData()
{
	_transformBuffer->CopyData(_transformData);
}

void RenderManager::PushAnimationData()
{
	_animationBuffer->CopyData(_animationData);
}

void RenderManager::GettherRenderableObjects()
{
	_renderObjects.clear();
	_renderUiObjects.clear();

	for (int i = 0; i < LAYER_UI; i++)
	{
		auto& gameObjects = SCENE->GetCurrentScene()->GetGameObjects(i);
		for (const auto& gameObject : gameObjects)
		{
			MeshRenderer* meshRenderer = gameObject->GetMeshRenderer();
			if (meshRenderer && gameObject->GetIsActivity() != false)
				_renderObjects.push_back(gameObject);
		}
	}
	auto& gameObjects = SCENE->GetCurrentScene()->GetGameObjects(LAYER_UI);

	for (const auto& gameObject : gameObjects)
	{
		MeshRenderer* meshRenderer = gameObject->GetMeshRenderer();
		if (meshRenderer && gameObject->GetIsActivity() != false)
			_renderUiObjects.push_back(gameObject);
	}

}

void RenderManager::RenderObjects(vector<GameObject*> renderObject)
{
	for (const auto& gameObject : renderObject)
	{
		if (!gameObject->GetIsActivity())
			continue;

		MeshRenderer* meshRenderer = gameObject->GetMeshRenderer();
		if (meshRenderer == nullptr)
			continue;

		Transform* transform = gameObject->GetTransform();
		if (transform == nullptr)
			continue;

		Matrix matSize;

		Animator* animator = gameObject->GetAnimator();
		SpriteRenderer* spriteRenderer = gameObject->GetSpriteRenderer();
		if (animator)
		{
			const Keyframe& keyframe = animator->GetCurrentKeyframe();
			_animationData.spriteOffset = keyframe.offset;
			_animationData.spriteSize = keyframe.size;
			_animationData.textureSize = animator->GetCurrentAnimation()->GetTexture()->GetSize();
			_animationData.useAnimation = 1.f;

			PushAnimationData();
			_pipeline->SetConstantBuffer(2, SS_VertexShader, _animationBuffer);
			_pipeline->SetTexture(0, SS_PixelShader, animator->GetCurrentAnimation()->GetTexture());
			
			matSize = SetRenderScale(keyframe.size);
		}
		else if (spriteRenderer)
		{
			const SpriteInfo& sprite = spriteRenderer->GetSprite()->GetInfo();
			_animationData.spriteOffset = sprite.offset;
			_animationData.spriteSize = sprite.size;
			_animationData.textureSize = spriteRenderer->GetSprite()->GetTexture()->GetSize();
			_animationData.useAnimation = 1.f;

			PushAnimationData();
			_pipeline->SetConstantBuffer(2, SS_VertexShader, _animationBuffer);
			_pipeline->SetTexture(0, SS_PixelShader, spriteRenderer->GetSprite()->GetTexture());
			matSize = SetRenderScale(sprite.size);
		}
		else
		{
			_animationData.spriteOffset = Vec2(0.f, 0.f);
			_animationData.spriteSize = Vec2(0.f, 0.f);
			_animationData.textureSize = Vec2(0.f, 0.f);
			_animationData.useAnimation = 0.f;

			PushAnimationData();
			_pipeline->SetConstantBuffer(2, SS_VertexShader, _animationBuffer);
			_pipeline->SetTexture(0, SS_PixelShader, meshRenderer->GetTexture());

			matSize = SetRenderScale(meshRenderer->GetTexture()->GetSize());

			auto texture = meshRenderer->GetTexture();

			cout
				<< "Texture Size: "
				<< texture->GetSize().x
				<< ", "
				<< texture->GetSize().y
				<< endl;

			Vec3 pos = transform->GetPosition();

			cout
				<< "Position: "
				<< pos.x << ", "
				<< pos.y << ", "
				<< pos.z
				<< endl;
		}

		_transformData.matWorld = matSize * transform->GetWorldMatrix();
		PushTransformData();

		PipelineInfo info;
		info.inputLayout = meshRenderer->GetInputLayout();
		info.vertexShader = meshRenderer->GetVertexShader();
		info.pixelShader = meshRenderer->GetPixelShader();
		info.rasterizerState = _rasterizerState;
		info.blendState = _blendState;

		_pipeline->UpdatePipeline(info);

		_pipeline->SetVertexBuffer(meshRenderer->GetMesh()->GetVertexBuffer());
		_pipeline->SetIndexBuffer(meshRenderer->GetMesh()->GetIndexBuffer());
		_pipeline->SetConstantBuffer(0, SS_VertexShader, _transformBuffer);
		_pipeline->SetConstantBuffer(1, SS_VertexShader, _cameraBuffer);
		//_pipeline->SetTexture(0, SS_PixelShader, meshRenderer->GetTexture());
		_pipeline->SetSamplerState(0, SS_PixelShader, _samplerState);

		_pipeline->DrawIndexed(meshRenderer->GetMesh()->GetIndexBuffer()->GetCount(), 0, 0);

	}
}

Matrix RenderManager::SetRenderScale(Vec2 size)
{
	Matrix matSize = Matrix::CreateScale(
		size.x,
		size.y,
		1.0f
	);
	return matSize;
}


