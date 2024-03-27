#pragma once
class ImguiManager
{
public:
	ImguiManager();
	~ImguiManager();

	void Initialize(GLFWwindow* p_window);
	void Terminate();
	void Update();
	void Render();
};

