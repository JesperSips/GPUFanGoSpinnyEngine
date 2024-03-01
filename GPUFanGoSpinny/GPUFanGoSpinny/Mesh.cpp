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
        CreateCube();
        break;
    }
}

Mesh::~Mesh()
{
}

void Mesh::CreateTriangle()
{
    m_numVertex = 3;

    Vertex vertice[] =
    {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    for (UINT i = 0; i < m_numVertex; i++)
    {
        m_vertexData.push_back(vertice[i]);
    }
}

void Mesh::CreateCube()
{
    m_numVertex = 24;

    Vertex vertice[] =
    {
        { {0, 0, 0}},
        { {0, 1, 0}},
        { {1, 1, 0}},
        { {1, 0, 0}},

        { {0, 1, 0}} ,
        { {0, 1, 1}} ,
        { {1, 1, 1}} ,
        { {1, 1, 0}} ,

        { {1, 0, 0}},
        { {1, 1, 0}},
        { {1, 1, 1}},
        { {1, 0, 1}},

        { {0, 0, 1}},
        { {0, 0, 0}},
        { {1, 0, 0}},
        { {1, 0, 1}},

        { {0, 0, 1}},
        { {0, 1, 1}},
        { {0, 1, 0}},
        { {0, 0, 0}},

        { {1, 0, 1}},
        { {1, 1, 1}},
        { {0, 1, 1}},
        { {0, 0, 1}}
    };

    for (UINT i = 0; i < m_numVertex; i++)
    {
        m_vertexData.push_back(vertice[i]);
    }
}
