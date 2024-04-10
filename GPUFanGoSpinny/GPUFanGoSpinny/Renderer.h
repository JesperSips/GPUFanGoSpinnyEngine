#pragma once
class Mesh;
class Shader;
class Window;
class Camera;
class ImguiManager;
class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	virtual void Initialize(HINSTANCE p_hInstance, int p_width, int p_height);
	
	bool IsQuitting();

	virtual void Update();
	virtual void Terminate();

	void AddMesh(Mesh* p_mesh);

	glm::mat4 model = glm::mat4(1.0f);

protected:
	Window* m_window = nullptr;

	Camera* m_camera = nullptr;

	ImguiManager* m_GUI = nullptr;

	Shader* m_shader = nullptr;

	// The mesh that will be drawn to the screen, currently this is only one mesh, later this will be an array of meshes
	Mesh* m_mesh = nullptr;

	virtual void Render();
};

