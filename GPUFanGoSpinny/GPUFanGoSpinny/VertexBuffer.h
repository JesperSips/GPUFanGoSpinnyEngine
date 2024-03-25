#pragma once
class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void Bind(GLuint& p_VBO, GLuint& p_EBO);
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
};

