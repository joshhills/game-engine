#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "RenderObject.h"

class GraphicsData {
public:
	// TODO: Do these need to be pointers?
	GraphicsData(Mesh * mesh, Shader * shader);
	~GraphicsData();

	RenderObject & GetRenderObject();

private:
	Mesh * mesh;
	Shader * shader;
	RenderObject renderObject;
};