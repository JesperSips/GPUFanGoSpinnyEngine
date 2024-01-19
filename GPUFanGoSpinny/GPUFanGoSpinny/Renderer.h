#pragma once
class Window;
class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize(HINSTANCE p_hInstance, int p_width, int p_height);

private:
	Window* m_window = nullptr;

	void Render();
	void Update();
	void Terminate();
};

