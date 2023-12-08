#pragma once
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
class Window
{
public: 
	Window() {};

	void RegisterWindowClass(HINSTANCE p_hInst, LPCWSTR p_className);
	void CreateWindow(const wchar_t* p_windowClassName, HINSTANCE p_hInst, const wchar_t* p_windowTitle, UINT32 p_width, UINT32 p_height);

	HWND GetWindowHandle() const {
		return m_hWnd;
	};

private:
	WNDCLASSEXW m_wcex = {};
	HWND m_hWnd = nullptr;
	RECT m_windowRect = {};

	UINT32 m_ClientWidth = 0;
	UINT32 m_ClientHeight = 0;
	bool m_fullscreen = false;

};

