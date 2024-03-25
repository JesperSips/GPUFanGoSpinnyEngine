#include "pch.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
	// Generate vertex and index buffers
	GLuint VBO = 0, EBO = 0;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	m_VBO = VBO;
	m_EBO = EBO;
}

VertexBuffer::~VertexBuffer()
{
	Unbind();

	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);

	m_vertexData.clear();
	m_indices.clear();
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertexCount, m_vertexData.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indexCount, m_indices.data(), GL_STATIC_DRAW);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(Vertex* data, GLsizei p_count)
{
	m_vertexCount = p_count;

	for (int i = 0; i < m_vertexCount; i++)
	{
		m_vertexData.push_back(data[i]);
	}
}

void VertexBuffer::SetIndices(const GLuint* indices, GLsizei p_count)
{
	m_indexCount = p_count;

	for (int i = 0; i < m_indexCount; i++)
	{
		m_indices.push_back(indices[i]);
	}
}
