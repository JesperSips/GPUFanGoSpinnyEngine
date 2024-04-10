#include "pch.h"
#include "Renderer.h"
#include "Window.h"

static Renderer* rendererPtr;

void OnWindowResize(GLFWwindow* p_window, int p_width, int p_height)
{
	rendererPtr->Resize(p_width, p_height);
}

void MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	static bool firstMouse = true;
	static float lastX = 0;
	static float lastY = 0;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xoffset *= global::mouseSensitivity;
	yoffset *= global::mouseSensitivity;

	global::UpdateMouseOffset(xpos, ypos, xoffset, yoffset);
}	

Window::Window(Renderer& p_ref, UINT32 p_width, UINT32 p_height, std::string p_title)
{
	rendererPtr = &p_ref;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	m_window = glfwCreateWindow(p_width, p_height, p_title.c_str(), nullptr, nullptr);

	glfwSetWindowSizeCallback(m_window, OnWindowResize);
	glfwSetCursorPosCallback(m_window, MouseCallback);

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
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
}

void Window::Update()
{
	glfwSwapBuffers(m_window);
}

bool Window::getIsQuitting() const
{
	return glfwWindowShouldClose(m_window);
}

HWND Window::GetWin32Window() const
{
	HWND hwnd = glfwGetWin32Window(m_window);
	if (!hwnd) {
		throw;
	}
	return hwnd;
}
