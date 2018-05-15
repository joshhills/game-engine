#include "BackgroundEntity.h"
#include <Graphics/Renderer.h>

BackgroundEntity::BackgroundEntity(EventManager * eventManager)
	: Entity(eventManager)
{
	// Create the visual representation.
	Mesh * mesh = Mesh::GenerateQuad(300.0f, 168.0f);
	Shader * shader = new Shader("./Resources/Shaders/baseTileVert.glsl", "./Resources/Shaders/baseTexturedFrag.glsl");
	GLuint tex = Renderer::LoadTexture("./Resources/Textures/Background.png");
	graphicsData = new GraphicsData(mesh, shader, tex);

	gameObject->x = 0;
	gameObject->y = 0;
	gameObject->z = 10;

	enabled = true;
	transparent = false;
}

BackgroundEntity::~BackgroundEntity()
{}
