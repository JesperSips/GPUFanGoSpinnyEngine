#pragma once
class VertexBuffer
{
public:
    // Create a VBO, EBO and VAO including all the vertex and index data for this mesh
    // Include vertex data, vertex count, index data and index count
    VertexBuffer(Vertex* p_vertices, GLsizei p_vertexCount, const GLuint* p_indices, GLsizei p_indexCount);
    // Create a VBO, EBO and VAO that includes the vertex attributes but no vertex or index data
    VertexBuffer();
    ~VertexBuffer();

    void Bind();
    void Unbind();

    void SetData(Vertex* data, GLsizei p_count);
    void SetIndices(const GLuint* indices, GLsizei p_count);

    GLsizei GetVertexCount() const { return m_vertexCount; }
    GLsizei GetIndexCount() const { return m_indexCount; }

private:
    std::vector<Vertex>	 m_vertexData;
    std::vector<GLuint> m_indices;

    GLsizei m_vertexCount = 0;
    GLsizei m_indexCount = 0;

    GLuint m_VBO = 0;
    GLuint m_EBO = 0;
    GLuint m_VAO = 0;
};

