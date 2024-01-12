#pragma once
class Window
{
public: 
	Window() {};

	void SetupWindow();

	HWND GetWindowHandle() const {
		return m_hWnd;
	};

protected:
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void RegisterWindowClass(HINSTANCE p_hInst, LPCWSTR p_className);
	void CreateWindow(const wchar_t* p_windowClassName, HINSTANCE p_hInst, const wchar_t* p_windowTitle, UINT32 p_width, UINT32 p_height);

	WNDCLASSEXW m_wcex = {};
	HWND m_hWnd = nullptr;
	RECT m_windowRect = {};

	UINT32 m_ClientWidth = 0;
	UINT32 m_ClientHeight = 0;
	bool m_fullscreen = false;

};

