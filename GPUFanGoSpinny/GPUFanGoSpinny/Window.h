#pragma once
struct GLFWwindow;

class Renderer;
class Window
{
public:
	Window(Renderer& p_ref, UINT32 p_width, UINT32 p_height, const std::string& p_title);
	~Window();

	void Update();

	bool getIsQuitting() const;

	HWND GetWin32Window() const;

	inline GLFWwindow* GetWindow() { return m_window; };

private:

	GLFWwindow* m_window;
};
