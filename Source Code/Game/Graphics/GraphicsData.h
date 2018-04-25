#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "RenderObject.h"

class GraphicsData {
public:
	GraphicsData(Mesh * mesh, Shader * shader);
	~GraphicsData();

	RenderObject & GetRenderObject();

private:
	Mesh * mesh;
	Shader * shader;
	RenderObject renderObject;
};