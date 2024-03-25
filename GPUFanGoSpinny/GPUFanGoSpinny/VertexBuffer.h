#pragma once
struct Vertex
{
    float pos[3] = { 0,0,0 };
    float rgb[3] = { 0,0,0 };
    float tex[2] = { 0,0 };
};

class VertexBuffer
{
public:
    VertexBuffer();
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

    void SetData(Vertex* data, GLsizei p_count);
    void SetIndices(const GLuint* indices, GLsizei p_count);

    GLuint GetVBO() const { return m_VBO; }
    GLuint GetEBO() const { return m_EBO; }
    GLsizei GetVertexCount() const { return m_vertexCount; }
    GLsizei GetIndexCount() const { return m_indexCount; }

private:
    std::vector<Vertex>	 m_vertexData;
    std::vector<GLuint> m_indices;

    GLuint m_VBO = 0;
    GLuint m_EBO = 0;

    GLsizei m_vertexCount = 0;
    GLsizei m_indexCount = 0;
};

