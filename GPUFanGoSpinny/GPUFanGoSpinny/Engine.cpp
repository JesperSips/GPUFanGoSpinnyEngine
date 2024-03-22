#include "pch.h"
#include "Mesh.h"
#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Initialize(HINSTANCE p_hInstance)
{
	m_renderer.Initialize(p_hInstance, 500, 500);

	Mesh* mesh = new Mesh(2);
	m_renderer.AddMesh(mesh);

	// Update loop starts here, make sure to initialize everything beforehand

	Update();

	Terminate();
}

void Engine::Update()
{
	while (!m_renderer.IsQuitting())
	{
		m_renderer.Update();
	}
}

void Engine::Terminate()
{
	m_renderer.Terminate();
}
