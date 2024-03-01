#include "pch.h"
#include "Window.h"

Window::Window(UINT32 p_width, UINT32 p_height, std::string p_title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	m_window = glfwCreateWindow(p_width, p_height, p_title.c_str(), nullptr, nullptr);

	if (!m_window)
	{
		throw;
	}

	glfwMakeContextCurrent(m_window);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
}

void Window::Update()
{
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

bool Window::getIsQuitting() const
{
	return glfwWindowShouldClose(m_window);
}
