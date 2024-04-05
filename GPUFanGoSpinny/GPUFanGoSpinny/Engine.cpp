#include "pch.h"
#include "Mesh.h"

#ifdef OpenGL
#include "RendererGL.h"
#endif

#ifdef DX12
#include "RendererDX.h"
#endif

#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::Initialize(HINSTANCE p_hInstance)
{

#ifdef OpenGL
	m_renderer = new RendererGL();
#endif


#ifdef DX12
	m_renderer = new RendererDX();
#endif

	m_renderer->Initialize(p_hInstance, 500, 500);

	Mesh* mesh = new Mesh(3);
	m_renderer->AddMesh(mesh);

	// Update loop starts here, make sure to initialize everything beforehand

	Update();

	Terminate();
}

void Engine::Update()
{
	while (!m_renderer->IsQuitting())
	{
		global::UpdateGlobalValues();
		m_renderer->Update();
	}
}

void Engine::Terminate()
{
	m_renderer->Terminate();
}
