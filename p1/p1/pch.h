#pragma once


#include "Enums.h"
#include "Types.h"
#include "Values.h"
#include "Defines.h"
#include "Utils.h"

#define NOMINMAX
#include <vector>
#include <list>
#include <map>
#include <array>
#include <unordered_map>
#include <string>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <random>
#include <iostream>
#include <format>
#include <filesystem>


#include <assert.h>
#include <windows.h>


using namespace std;

namespace fs = std::filesystem;

#pragma comment(lib, "Msimg32.lib")


#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>



// »ç¿îµå
#include <mmsystem.h>
#include <dsound.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dsound.lib")


// Engin
#include <d3d11.h>
#include<d3dcompiler.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <DirectXTex/DirectXTex.h>
#include <DirectXTex/DirectXTex.inl>

//using namespace DirectX;
using namespace Microsoft::WRL;

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment(lib,"DirectXTex\\DirectXTex_Debug.lib")
#else
#pragma comment(lib,"DirectXTex\\DirectXTex.lib")
#endif

#include "97.Engin/Pipeline/Graphics.h"
#include "97.Engin/Pipeline/01.InputAssembler/VertexBuffer.h"
#include "97.Engin/Pipeline/01.InputAssembler/IndexBuffer.h"
#include "97.Engin/Pipeline/01.InputAssembler/InputLayout.h"
#include "97.Engin/Pipeline/00.Geometry/Geometry.h"
#include "97.Engin/Pipeline/00.Geometry/GeometryHelper.h"
#include "97.Engin/Pipeline/00.Geometry/VertexData.h"
#include "97.Engin/Pipeline/02.VertexShader/ShaderBase.h"
#include "97.Engin/Pipeline/02.VertexShader/ConstantBuffer.h"
#include "97.Engin/Pipeline/03.Rasterizer/RasterizerState.h"
#include "97.Engin/Pipeline/04.PixelShader/SamplerState.h"
#include "97.Engin/Pipeline/05.OutputMerge/BlendState.h"
#include "97.Engin/Pipeline/Pipeline.h"
#include "97.Engin/Component/Transform/Transform.h"

// Game
#include "00.MainGame/Game.h"

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif