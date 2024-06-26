#pragma once
#include "Renderer.h"
class RendererGL :
    public Renderer
{
public:
	RendererGL();
	~RendererGL();

	void Initialize(int p_width, int p_height);

	void Update();
	void Terminate();

	void Resize(int p_width, int p_height);

	glm::mat4 model = glm::mat4(1.0f);

protected:

	virtual void Render();
};

