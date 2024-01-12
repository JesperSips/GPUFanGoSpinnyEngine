#pragma once
class Window
{
public:
	Window(UINT32 p_width, UINT32 p_height, std::wstring p_title, HINSTANCE p_hInstance);

	void SetupWindow();
	void Update();

	bool getIsQuitting() const {
		return m_isQuitting;
	}

	HWND GetWindowHandle() const {
		return m_hWnd;
	};

protected:
	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	void RegisterWindowClass();
	void CreateWindow();

	WNDCLASSEXW m_wcex = {};
	HWND m_hWnd = nullptr;
	HINSTANCE m_hInstance = nullptr;
	RECT m_windowRect = {};
	std::wstring m_title = L"default";

	UINT32 m_clientWidth = 0;
	UINT32 m_clientHeight = 0;
	float m_aspectRatio = 0;
	bool m_fullscreen = false;

	// Becomes true when the renderer needs to close
	bool m_isQuitting = false;
};
