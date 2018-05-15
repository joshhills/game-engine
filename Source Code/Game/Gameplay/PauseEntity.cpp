#include "PauseEntity.h"
#include <Graphics/Renderer.h>

PauseEntity::PauseEntity(EventManager * eventManager)
	: Entity(eventManager)
{
	// Create the visual representation.
	Mesh * mesh = Mesh::GenerateQuad(58.0f, 32.63f);
	Shader * shader = new Shader("./Resources/Shaders/baseTileVert.glsl", "./Resources/Shaders/baseTexturedFrag.glsl");
	GLuint tex = Renderer::LoadTexture("./Resources/Textures/Pause.png");
	graphicsData = new GraphicsData(mesh, shader, tex);

	gameObject->x = 0;
	gameObject->y = 0;
	gameObject->z = -1;

	enabled = true;
	transparent = true;
}

PauseEntity::~PauseEntity()
{}
