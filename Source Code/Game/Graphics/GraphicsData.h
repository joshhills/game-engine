#pragma once

#include "Mesh.h"
#include "Shader.h"
#include "RenderObject.h"

class GraphicsData {
public:
	GraphicsData(Mesh * mesh, Shader * shader, GLuint texture);
	GraphicsData(Mesh * mesh, Shader * shader);
	~GraphicsData();

	RenderObject & GetRenderObject();

	void ChangeShader(Shader * shader);
private:
	Mesh * mesh;
	Shader * shader;
	RenderObject renderObject;
};