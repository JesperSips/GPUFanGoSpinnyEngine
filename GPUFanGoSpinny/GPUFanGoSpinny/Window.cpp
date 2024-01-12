#include "pch.h"
#include "Window.h"

void Window::RegisterWindowClass()
{
	m_wcex.cbSize = sizeof(WNDCLASSEX);
	m_wcex.style = CS_HREDRAW | CS_VREDRAW;
	m_wcex.lpfnWndProc = &wndProc;
	m_wcex.cbClsExtra = 0;
	m_wcex.cbWndExtra = 0;
	m_wcex.hInstance = m_hInstance;
	m_wcex.hIcon = LoadIcon(m_hInstance, 0);
	m_wcex.hIconSm = ::LoadIcon(m_hInstance, NULL);
	m_wcex.hCursor = LoadCursor(0, IDC_ARROW);
	m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	m_wcex.lpszMenuName = NULL;
	m_wcex.lpszClassName = L"Window";

	if (!RegisterClassExW(&m_wcex))
	{
		throw;
	}
}

void Window::CreateWindow()
{
	RECT windowRect = { 0,0, static_cast<LONG>(m_clientWidth), static_cast<LONG>(m_clientHeight) };
	::AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	m_windowRect = windowRect;

	int screenWidth = ::GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = ::GetSystemMetrics(SM_CYSCREEN);

	int windowWidth = m_windowRect.right - m_windowRect.left;
	int windowHeight = m_windowRect.bottom - m_windowRect.top;

	// Center the window within the screen. Clamp to 0, 0 for the top-left corner.
	int windowX = std::max<int>(0, (screenWidth - windowWidth) / 2);
	int windowY = std::max<int>(0, (screenHeight - windowHeight) / 2);
	
	HWND hWnd = CreateWindowEx(
		0,
		m_wcex.lpszClassName,
		m_title.c_str(),
		WS_OVERLAPPEDWINDOW,
		windowX,
		windowY,
		windowWidth,
		windowHeight,
		nullptr,
		nullptr,
		m_hInstance,
		nullptr
	);

	assert(hWnd);

	m_hWnd = hWnd;
}


Window::Window(UINT32 p_width, UINT32 p_height, std::wstring p_title, HINSTANCE p_hInstance)
{
	m_clientWidth = p_width;
	m_clientHeight = p_height;
	m_aspectRatio = static_cast<float>(p_width) / static_cast<float>(p_height);
	m_title = p_title;
	m_hInstance = p_hInstance;
}

void Window::SetupWindow()
{
	RegisterWindowClass();
	CreateWindow();
	ShowWindow(m_hWnd, SW_NORMAL);
}

void Window::Update()
{
	// Window Loop sends events.
	MSG msg = {};
	// Process any messages in the queue.
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			m_isQuitting = true;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT Window::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (message)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		/* stop event queue thread */
		PostQuitMessage(0);
		break;
	default:
		result = DefWindowProc(hWnd, message, wParam, lParam);
	}
	return result;
}
