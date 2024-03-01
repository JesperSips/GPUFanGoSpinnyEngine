#pragma once
class Mesh;
class Window;
class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize(HINSTANCE p_hInstance, int p_width, int p_height, Mesh* p_mesh);

private:
	Window* m_window = nullptr;
	GLint m_shaderProgram = 0;
	GLuint m_VAO = 0;

	// The mesh that will be drawn to the screen, currently this is only one mesh, later this will be an array of meshes
	Mesh* m_mesh = nullptr;

	void CompileShaders();
	void Render();
	void Update();
	void Terminate();
};

