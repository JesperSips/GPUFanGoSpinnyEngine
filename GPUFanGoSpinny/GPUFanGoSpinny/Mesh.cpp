#include "pch.h"
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
    m_numVertex = 3;
    m_numIndex = 3;

    Vertex vertice[] =
    {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    GLuint indices[] = {
        0,1,2
    };

    for (UINT i = 0; i < m_numVertex; i++)
    {
        m_vertexData.push_back(vertice[i]);
    }

    for (UINT i = 0; i < m_numIndex; i++)
    {
        m_indices.push_back(indices[i]);
    }
}

void Mesh::CreateQuad()
{
    m_numVertex = 4;
    m_numIndex = 6;

    Vertex vertice[] =
    {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };

    GLuint indices[] = { 
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };

    for (UINT i = 0; i < m_numVertex; i++)
    {
        m_vertexData.push_back(vertice[i]);
    }

    for (UINT i = 0; i < m_numIndex; i++)
    {
        m_indices.push_back(indices[i]);
    }
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
    m_numVertex = 8;
    m_numIndex = 36;

    Vertex vertices[] = {
        // Front face
        -0.5f, -0.5f,  0.5f,  // Bottom-left
         0.5f, -0.5f,  0.5f,  // Bottom-right
         0.5f,  0.5f,  0.5f,  // Top-right
        -0.5f,  0.5f,  0.5f,  // Top-left
        // Back face
        -0.5f, -0.5f, -0.5f,  // Bottom-left
         0.5f, -0.5f, -0.5f,  // Bottom-right
         0.5f,  0.5f, -0.5f,  // Top-right
        -0.5f,  0.5f, -0.5f,  // Top-left
    };

    GLuint indices[] = {
        // Front face
        0, 1, 2,
        2, 3, 0,
        // Right face
        1, 5, 6,
        6, 2, 1,
        // Back face
        7, 6, 5,
        5, 4, 7,
        // Left face
        4, 0, 3,
        3, 7, 4,
        // Bottom face
        4, 5, 1,
        1, 0, 4,
        // Top face
        3, 2, 6,
        6, 7, 3
    };

    for (UINT i = 0; i < m_numVertex; i++)
    {
        m_vertexData.push_back(vertices[i]);
    }

    for (UINT i = 0; i < m_numIndex; i++)
    {
        m_indices.push_back(indices[i]);
    }
}