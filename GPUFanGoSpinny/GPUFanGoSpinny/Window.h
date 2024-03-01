#pragma once
struct GLFWwindow;

class Window
{
public:
	Window(UINT32 p_width, UINT32 p_height, std::string p_title);
	~Window();

	void Update();

	bool getIsQuitting() const;

private:
	GLFWwindow* m_window;
};
