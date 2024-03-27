#pragma once
struct GLFWWindow;
class ImguiManager
{
public:
	ImguiManager();
	~ImguiManager();

	void Initialize(GLFWwindow* p_window);
	void Terminate();
	void Update();
	void Render();

private:
	GLFWWindow* m_window = nullptr;
};

