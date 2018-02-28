#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent)	{
	time = 0;
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer(void)	{
	 
}

void	Renderer::RenderScene() {
	for(vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i ) {
		Render(*(*i));
	}
}

void	Renderer::Render(const RenderObject &o) {
	modelMatrix = o.GetWorldTransform();

	time += 0.1f;

	if(o.GetShader() && o.GetMesh()) {
		GLuint program = o.GetShader()->GetShaderProgram();
		
		glUseProgram(program);

		UpdateShaderMatrices(program);
		glUniform1f(glGetUniformLocation(program, "time"), time);

		o.Draw();
	}

	for(vector<RenderObject*>::const_iterator i = o.GetChildren().begin(); i != o.GetChildren().end(); ++i ) {
		Render(*(*i));
	}
}

void	Renderer::UpdateScene(float msec) {
	for(vector<RenderObject*>::iterator i = renderObjects.begin(); i != renderObjects.end(); ++i ) {
		(*i)->Update();
	}
}

GLuint Renderer::LoadTexture(const string& filename) {
	GLuint texName = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	if (texName == 0) {
		cout << "Texture file " << filename << " failed to load!" << std::endl;
	}

	return texName;
}