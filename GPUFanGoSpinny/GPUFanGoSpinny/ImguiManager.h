#pragma once
class Renderer;
class ImguiManager
{
public:
	ImguiManager();
	~ImguiManager();

	void Initialize(GLFWwindow& p_window, Renderer& p_ref);
	void Terminate();
	void Update(glm::vec4& p_clearColor);
	void Render();
};

