#include "pch.h"
#include "VertexBuffer.h"
#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(int p_default)
{
    switch (p_default)
    {
    case 1:
        CreateTriangle();
        break;
    case 2:
        CreateQuad();
        break;
    case 3:
        CreateCube();
        break;
    }
}

Mesh::~Mesh()
{
}

const GLsizei Mesh::getIndexSize()
{
    return m_vertexBuffer->GetIndexCount();
}

void Mesh::Bind()
{
    m_vertexBuffer->Bind();
}

// Default mesh functions:

// Original with no indices

//void Mesh::CreateTriangle()
//{
//    m_numVertex = 3;
//
//    Vertex vertice[] =
//    {
//    -0.5f, -0.5f, 0.0f,
//     0.5f, -0.5f, 0.0f,
//     0.0f,  0.5f, 0.0f
//    };
//
//    for (UINT i = 0; i < m_numVertex; i++)
//    {
//        m_vertexData.push_back(vertice[i]);
//    }
//}

void Mesh::CreateTriangle()
{
    int numVertex = 3;
    int numIndex = 3;

    Vertex vertices[] =
    {
    // positions,       // rgb color      // texcoords
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f
    };

    GLuint indices[] = {
        0,1,2
    };

    m_vertexBuffer = new VertexBuffer(vertices, numVertex, indices, numIndex);

    m_texture->loadTexture("Assets/meow.jpg", true);
}

void Mesh::CreateQuad()
{
    int numVertex = 4;
    int numIndex = 6;

    Vertex vertices[] =
    {
    // positions,       // rgb color      // texcoords
     0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f, 0.6f, 0.2f, 1.0f, 1.0f, 0.0f,// bottom right
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom left
    -0.5f,  0.5f, 0.0f, 0.4f, 1.0f, 0.6f, 0.0f, 1.0f// top left 
    };

    GLuint indices[] = { 
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };

    m_vertexBuffer = new VertexBuffer(vertices, numVertex, indices, numIndex);

    m_texture->loadTexture("Assets/meow.jpg", true);
}

//Original code without indices

//void Mesh::CreateCube()
//{
//    m_numVertex = 24;
//
//    Vertex vertice[] =
//    {
//        { {0, 0, 0}},
//        { {0, 1, 0}},
//        { {1, 1, 0}},
//        { {1, 0, 0}},
//
//        { {0, 1, 0}} ,
//        { {0, 1, 1}} ,
//        { {1, 1, 1}} ,
//        { {1, 1, 0}} ,
//
//        { {1, 0, 0}},
//        { {1, 1, 0}},
//        { {1, 1, 1}},
//        { {1, 0, 1}},
//
//        { {0, 0, 1}},
//        { {0, 0, 0}},
//        { {1, 0, 0}},
//        { {1, 0, 1}},
//
//        { {0, 0, 1}},
//        { {0, 1, 1}},
//        { {0, 1, 0}},
//        { {0, 0, 0}},
//
//        { {1, 0, 1}},
//        { {1, 1, 1}},
//        { {0, 1, 1}},
//        { {0, 0, 1}}
//    };
//
//    for (UINT i = 0; i < m_numVertex; i++)
//    {
//        m_vertexData.push_back(vertice[i]);
//    }
//}

void Mesh::CreateCube()
{
    int numVertex = 24;
    int numIndex = 36;

    Vertex vertices[] = {
    // positions,       // rgb color      // texcoords
    // Front face
    {-0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f},  // Bottom-left
    { 0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f},  // Bottom-right
    { 0.5f,  0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f},  // Top-right
    {-0.5f,  0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f},  // Top-left

    // Back face
    {-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f}, // Bottom-left
    { 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f}, // Bottom-right
    { 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f}, // Top-right
    {-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f}, // Top-left

    // Right face
    { 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f}, // Bottom-left
    { 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f}, // Bottom-right
    { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f}, // Top-right
    { 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f}, // Top-left

    // Left face
    {-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f}, // Bottom-left
    {-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f}, // Bottom-right
    {-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f}, // Top-right
    {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f}, // Top-left

    // Top face
    {-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f}, // Bottom-left
    { 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f}, // Bottom-right
    { 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f}, // Top-right
    {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f}, // Top-left

    // Bottom face
    {-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f}, // Bottom-left
    { 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f}, // Bottom-right
    { 0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f}, // Top-right
    {-0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f}  // Top-left
    
    };
    

    GLuint indices[] = {
        0, 1, 2,  // Front face
        2, 3, 0,
        4, 5, 6,  // Back face
        6, 7, 4,
        8, 9, 10, // Right face
        10, 11, 8,
        12, 13, 14, // Left face
        14, 15, 12,
        16, 17, 18, // Top face
        18, 19, 16,
        20, 21, 22, // Bottom face
        22, 23, 20
    };

    m_vertexBuffer = new VertexBuffer(vertices, numVertex, indices, numIndex);

    m_texture->loadTexture("Assets/meow.jpg", true);
}