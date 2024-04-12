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
	delete m_renderer;
}

void Engine::Initialize()
{

#ifdef OpenGL
	m_renderer = new RendererGL();
#endif


#ifdef DX12
	m_renderer = new RendererDX();
#endif

	m_renderer->Initialize(500, 500);

#ifdef OpenGL
	Mesh* mesh = new Mesh(3);
	m_renderer->AddMesh(mesh);
#endif

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
