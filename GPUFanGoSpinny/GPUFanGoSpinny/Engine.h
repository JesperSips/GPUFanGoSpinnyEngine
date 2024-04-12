#pragma once
#include "Renderer.h"

class Engine
{
public:
	Engine();
	~Engine();

	void Initialize();

	void Update();
	void Terminate();
private:
	Renderer* m_renderer = nullptr;
};

