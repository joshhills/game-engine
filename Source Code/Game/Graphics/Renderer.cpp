#include "Renderer.h"

Renderer::Renderer(Window &parent) : OGLRenderer(parent)	{
	time = 0;

	// Begin modifications to 3rd party code.
	// Josh Hills
	// 140177712
	// Enable alpha and culling.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// End modifications to 3rd party code.
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

		// TODO: Add custom code.
		if (o.GetTexture())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, o.GetTexture());
			GLuint sampler = glGetUniformLocation(program, "activeTex");
			glUniform1i(sampler, 0);
		}

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