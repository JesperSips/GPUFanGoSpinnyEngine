#include "pch.h"

#include "ImguiManager.h"
#include "Mesh.h"
#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	delete m_window;
}

bool Renderer::IsQuitting()
{
	return m_window->getIsQuitting(); 
}

#ifdef OpenGL
void Renderer::AddMesh(Mesh* p_mesh)
{
	m_mesh = p_mesh;
	m_mesh->Bind();
}
#endif
