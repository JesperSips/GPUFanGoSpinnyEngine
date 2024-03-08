#include "pch.h"

#include "Mesh.h"
#include "Window.h"
#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	delete m_window;
}

// from learnopengl
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.54f, 0.81f, 0.94f, 1.0f);\n"
"}\n\0";

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	m_VAO = VAO;

	CompileShaders();

	Update();

	Terminate();
}

void Renderer::CompileShaders()
{
	//Create shaders, code from learnOpenGL
	const GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		throw;
	}

	const GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		throw;
	}

	const GLint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		throw;
	}

	glUseProgram(shaderProgram);
	m_shaderProgram = shaderProgram;
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Renderer::Render()
{
	glClearColor(0.9f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_shaderProgram);
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
