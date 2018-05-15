#pragma once
#include <nclgl\OGLRenderer.h>

#include "RenderObject.h"

#include <vector>

using std::vector;

class Renderer : public OGLRenderer	{
public:
	Renderer(Window &parent);
	~Renderer(void);

	virtual void	RenderScene();

	virtual void	Render(const RenderObject &o);

	virtual void	UpdateScene(float msec);

	void	AddRenderObject(RenderObject &r) {
		renderObjects.push_back(&r);
	}

	// Edit
	void ClearRenderObjects() {
		renderObjects.clear();
	}
	// End edit

	static GLuint LoadTexture(const string& filename);

protected:
	float time;
	vector<RenderObject*> renderObjects;
};

