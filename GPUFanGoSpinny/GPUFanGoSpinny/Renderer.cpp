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
	m_window = new Window(p_width, p_height, L"I am in hell", p_hInstance);
	m_window->SetupWindow();
}
