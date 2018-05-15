#include "GraphicsData.h"

GraphicsData::GraphicsData(Mesh * mesh, Shader * shader) :
	mesh(mesh),
	shader(shader),
	renderObject(mesh, shader)
{
	// Make scale the same as physics bounding scale.
	renderObject.SetModelMatrix(Matrix4::Translation(Vector3(0, 0, 0)) * Matrix4::Scale(Vector3(1, 1, 1)));
	renderObject.Update();
}

GraphicsData::GraphicsData(Mesh * mesh, Shader * shader, GLuint texture) :
	mesh(mesh),
	shader(shader),
	renderObject(mesh, shader, texture)
{
	// Make scale the same as physics bounding scale.
	renderObject.SetModelMatrix(Matrix4::Translation(Vector3(0, 0, 0)) * Matrix4::Scale(Vector3(1, 1, 1)));
	renderObject.Update();
}

GraphicsData::~GraphicsData()
{}

RenderObject & GraphicsData::GetRenderObject()
{
	return renderObject;
}

void GraphicsData::ChangeShader(Shader * shader)
{
	this->shader = shader;
	renderObject.SetShader(this->shader);
}
