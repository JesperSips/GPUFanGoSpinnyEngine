#include "pch.h"

#include "Window.h"
#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
}

void Renderer::Initialize(HINSTANCE p_hInstance, int p_width, int p_height)
{
	m_window = new Window(p_width, p_height, L"GPU fan go spinny engine", p_hInstance);
	m_window->SetupWindow();

	glViewport(0, 0, p_width, p_height);
	wglMakeCurrent(m_window->GetDeviceContext(), m_window->GetRenderContext());

	Update();

	Terminate();
}

void Renderer::Render()
{
	glClearColor(0.9f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Update()
{
	while (!m_window->getIsQuitting())
	{
		Render();
		m_window->Update();
	}
}

void Renderer::Terminate()
{
}
