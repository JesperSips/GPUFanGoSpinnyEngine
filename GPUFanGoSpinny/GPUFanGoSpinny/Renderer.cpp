#include "pch.h"

#include "Mesh.h"
#include "Window.h"
#include "Shader.h"
#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	delete m_window;
}

void Renderer::Initialize(HINSTANCE p_hInstance, int p_width, int p_height, Mesh* p_mesh)
{
	glfwInit();

	m_mesh = p_mesh;

	m_window = new Window(p_width, p_height, "GPU fan go spinny engine");

	if (glewInit() != GLEW_OK) {
		std::cerr << "GLEW init failed" << std::endl;
		throw;
	}

	glViewport(0, 0, p_width, p_height);

	GLuint VBO = 0, EBO = 0, VAO = 0;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_mesh->getVertexData().size(), m_mesh->getVertexData().data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_mesh->getIndices().size(), m_mesh->getIndices().data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// RGB attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	m_VAO = VAO;

	m_shader = new Shader("Shaders/vshader.vs", "Shaders/fshader.fs");

	Update();

	Terminate();
}

void Renderer::Render()
{
	glClearColor(0.9f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_shader->use();
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::Update()
{
	while (!m_window->getIsQuitting())
	{
		Render();
		m_window->Update();
	}
}

void Renderer::Terminate()
{
	glfwTerminate();
}
