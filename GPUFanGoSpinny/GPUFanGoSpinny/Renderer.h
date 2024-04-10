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

	virtual void Initialize(HINSTANCE p_hInstance, int p_width, int p_height) = 0;
	
	bool IsQuitting();

	virtual void Update() = 0;
	virtual void Terminate() = 0;

	// ifdef OpenGL here is really bad, but it was the easiest way to fix the error for now
#ifdef OpenGL
	void AddMesh(Mesh* p_mesh);
#endif

	virtual void Resize(int p_width, int p_height) = 0;

protected:
	Window* m_window = nullptr;

	Camera* m_camera = nullptr;

	ImguiManager* m_GUI = nullptr;

	Shader* m_shader = nullptr;

#ifdef OpenGL
	// The mesh that will be drawn to the screen, currently this is only one mesh, later this will be an array of meshes
	Mesh* m_mesh = nullptr;
#endif
	virtual void Render() = 0;
};

