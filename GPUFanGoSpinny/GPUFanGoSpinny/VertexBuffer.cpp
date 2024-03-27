#include "pch.h"
#include "VertexBuffer.h"

static GLenum error;

VertexBuffer::VertexBuffer(Vertex* p_vertices, GLsizei p_vertexCount, const GLuint* p_indices, GLsizei p_indexCount)
{
	m_vertexCount = p_vertexCount;

	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertexData.push_back(p_vertices[i]);
	}

	m_indexCount = p_indexCount;

	for (int i = 0; i < m_indexCount; i++)
	{
		m_indices.push_back(p_indices[i]);
	}

	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertexCount, m_vertexData.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indexCount, m_indices.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// RGB attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glGenVertexArrays(1, &m_VAO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), nullptr, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint), nullptr, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// RGB attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);

	m_vertexData.clear();
	m_indices.clear();
}

void VertexBuffer::Bind(GLuint& p_VBO, GLuint& p_EBO)
{
	glBindVertexArray(m_VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertexCount, m_vertexData.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, p_EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indexCount, m_indices.data(), GL_STATIC_DRAW);
}

void VertexBuffer::Unbind()
{
	glBindVertexArray(0);
}

void VertexBuffer::SetData(Vertex* data, GLsizei p_count)
{
	glBindVertexArray(m_VAO);
	m_vertexCount = p_count;

	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertexData.push_back(data[i]);
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertexCount, m_vertexData.data(), GL_STATIC_DRAW);
}

void VertexBuffer::SetIndices(const GLuint* indices, GLsizei p_count)
{
	glBindVertexArray(m_VAO);

	m_indexCount = p_count;

	for (int i = 0; i < m_indexCount; i++)
	{
		m_indices.push_back(indices[i]);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indexCount, m_indices.data(), GL_STATIC_DRAW);
}
