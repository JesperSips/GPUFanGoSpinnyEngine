#pragma once
#include "Renderer.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Initialize(HINSTANCE p_hInstance);

	void Update();
	void Terminate();
private:
	Renderer m_renderer;
};

