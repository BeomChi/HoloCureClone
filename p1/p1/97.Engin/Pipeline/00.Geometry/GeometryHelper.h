#pragma once
#include "97.Engin/Pipeline/00.Geometry/Geometry.h"
#include "97.Engin/Pipeline/00.Geometry/VertexData.h"

class GeometryHelper
{
public:
	static void CreateRectangle(Geometry<VertexColorData>* geomtry, Color color);
	static void CreateRectangle(Geometry<VertexTextureData>* geomtry);
};

