#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#if defined(CreateWindow)
#undef CreateWindow
#endif

#include <algorithm>
#include <cassert>
#include <chrono>

#include "Window.h"

void Window::CreateWindow(const wchar_t* p_windowClassName, HINSTANCE p_hInst, const wchar_t* p_windowTitle, UINT32 p_width, UINT32 p_height)
{
	int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);
	RECT windowRect = { 0,0, static_cast<LONG>(p_width), static_cast<LONG>(p_height) };
	::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	m_windowRect = windowRect;

	int windowWidth = m_windowRect.right - m_windowRect.left;
	int windowHeight = m_windowRect.bottom - m_windowRect.top;

	// Center the window within the screen. Clamp to 0, 0 for the top-left corner.
	int windowX = std::max<int>(0, (screenWidth - windowWidth) / 2);
	int windowY = std::max<int>(0, (screenHeight - windowHeight) / 2);

	HWND hWnd = ::CreateWindowEx(
		NULL,
		p_windowClassName,
		p_windowTitle,
		WS_OVERLAPPEDWINDOW,
		windowX,
		windowY,
		windowWidth,
		windowHeight,
		NULL,
		NULL,
		p_hInst,
		nullptr
	);

	assert(hWnd && "Failed to create window");

	m_hWnd = hWnd;
}
