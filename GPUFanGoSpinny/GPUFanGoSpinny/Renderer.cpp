#include "pch.h"

#include "ImguiManager.h"
#include "Mesh.h"
#include "Window.h"
#include "Shader.h"
#include "Camera.h"
#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	delete m_window;
}

void Renderer::Initialize(HINSTANCE p_hInstance, int p_width, int p_height)
{
	if(glfwInit() != GLFW_TRUE){
		std::cerr << "GLFW init failed" << std::endl;
		throw;
	}

	m_window = new Window(p_width, p_height, "GPU fan go spinny engine");
	
	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW init failed" << std::endl;
		throw;
	}

	m_camera = new Camera(float(p_width / p_height), 80.f);

	m_GUI = new ImguiManager();
	m_GUI->Initialize(m_window->GetWindow());
	
	glViewport(0, 0, p_width, p_height);

	glEnable(GL_DEPTH_TEST);

	m_shader = new Shader("Shaders/vshader.vs", "Shaders/fshader.fs");

	// Temporary transformation code
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

bool Renderer::IsQuitting()
{
	return m_window->getIsQuitting(); 
}

void Renderer::Render()
{ 
	model = glm::rotate(model, global::deltaTime * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

	GLenum error;

	glClearColor(0.9f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader->use();

	unsigned int modelLoc = glGetUniformLocation(m_shader->m_ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	unsigned int viewLoc = glGetUniformLocation(m_shader->m_ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));

	unsigned int projLoc = glGetUniformLocation(m_shader->m_ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));

	// Check for OpenGL errors
	while ((error = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error before draw call: " << error << std::endl;
		throw;
	}

	glDrawElements(GL_TRIANGLES, m_mesh->getIndexSize(), GL_UNSIGNED_INT, 0);

	// Check for OpenGL errors
	while ((error = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL error after draw call: " << error << std::endl;
		throw;
	}

	m_GUI->Render();
}

void Renderer::Update()
{
	glfwPollEvents();

	// Camera also handles some inputs that affect the window currently
	m_camera->Update(m_window->GetWindow());
	m_GUI->Update();

	Render();
	m_window->Update();
}

void Renderer::Terminate()
{
	glfwTerminate();
}

void Renderer::AddMesh(Mesh* p_mesh)
{
	m_mesh = p_mesh;
	m_mesh->Bind();
}
