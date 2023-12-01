#pragma once
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
class Window
{
public: 
	Window();

	void CreateWindow(const wchar_t* p_windowClassName, HINSTANCE p_hInst, const wchar_t* p_windowTitle, UINT32 p_width, UINT32 p_height);

	HWND GetWindowHandle() const {
		return m_hWnd;
	};

private:
	HWND m_hWnd;
	RECT m_windowRect;

	UINT32 m_ClientWidth;
	UINT32 m_ClientHeight;
	bool m_fullscreen = false;

};

