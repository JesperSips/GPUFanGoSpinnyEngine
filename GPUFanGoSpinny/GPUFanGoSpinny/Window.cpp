#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#if defined(CreateWindow)
#undef CreateWindow
#endif

#include <algorithm>
#include <cassert>
#include <chrono>

#include "Window.h"

void Window::RegisterWindowClass(HINSTANCE p_hInst, LPCWSTR p_className)
{
	m_wcex.cbSize = sizeof(WNDCLASSEX);
	m_wcex.style = CS_HREDRAW | CS_VREDRAW;
	m_wcex.lpfnWndProc = &WndProc;
	m_wcex.cbClsExtra = 0;
	m_wcex.cbWndExtra = 0;
	m_wcex.hInstance = p_hInst;
	m_wcex.hIcon = LoadIcon(p_hInst, 0);
	m_wcex.hCursor = LoadCursor(0, IDC_ARROW);
	m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_wcex.lpszMenuName = NULL;
	m_wcex.lpszClassName = p_className;
	m_wcex.hIconSm = ::LoadIcon(p_hInst, NULL);

	if (!RegisterClassExW(&m_wcex))
	{
		throw;
	}
}

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
	
	HWND hWnd = CreateWindowEx(
		0,
		p_windowClassName,
		p_windowTitle,
		WS_OVERLAPPEDWINDOW,
		windowX,
		windowY,
		windowWidth,
		windowHeight,
		nullptr,
		nullptr,
		p_hInst,
		nullptr
	);

	assert(hWnd);

	m_hWnd = hWnd;
}
