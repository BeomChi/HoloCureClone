#pragma once
#include "Geometry.h"
#include "VertexData.h"

class GeometryHelper
{
public:
	static void CreateRectangle(Geometry<VertexColorData>* geomtry, Color color);
	static void CreateRectangle(Geometry<VertexTextureData>* geomtry);
};

