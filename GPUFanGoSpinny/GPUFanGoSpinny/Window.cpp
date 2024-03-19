#include "pch.h"
#include "Window.h"

void OnWindowResize(GLFWwindow* p_window, int p_width, int p_height)
{
	glViewport(0, 0, p_width, p_height);
}

Window::Window(UINT32 p_width, UINT32 p_height, std::string p_title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	m_window = glfwCreateWindow(p_width, p_height, p_title.c_str(), nullptr, nullptr);
	glfwSetWindowSizeCallback(m_window, OnWindowResize);

	if (!m_window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		throw;
	}

	// Check OpenGL context version
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	std::cout << "OpenGL context version: " << major << "." << minor << std::endl;

	glfwMakeContextCurrent(m_window);
	// Check for errors after making context current
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Error making OpenGL context current: " << error << std::endl;
		throw;
	}
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
