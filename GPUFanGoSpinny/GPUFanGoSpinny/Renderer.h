#pragma once
class Mesh;
class Shader;
class Window;
class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize(HINSTANCE p_hInstance, int p_width, int p_height);
	
	bool IsQuitting();

	void Update();
	void Terminate();

	void AddMesh(Mesh* p_mesh);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection;

private:
	Window* m_window = nullptr;

	GLuint m_VBO = 0;
	GLuint m_EBO = 0;
	GLuint m_VAO = 0;

	Shader* m_shader = nullptr;

	// The mesh that will be drawn to the screen, currently this is only one mesh, later this will be an array of meshes
	Mesh* m_mesh = nullptr;

	void Render();
};

