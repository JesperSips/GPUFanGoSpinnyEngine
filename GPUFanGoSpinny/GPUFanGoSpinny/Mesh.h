#pragma once
#include "Texture.h"

class VertexBuffer;
class Mesh
{
public:
	Mesh();
	 //add number for a default mesh
	 // 1 for triangle
	 // 2 for quad
	 // 3 for cube
	Mesh(int p_default);
	~Mesh();

	const GLsizei getIndexSize();

	void Bind(GLuint& p_VBO, GLuint& p_EBO);

private:
	// Number used to identify mesh
	// Not sure if this will be necessary in the future
	//unsigned int m_ID = 0;

	// Vertex Buffer class
	VertexBuffer* m_vertexBuffer = nullptr;

	// Texture class, making new here isnt necessary, fix that
	Texture* m_texture = new Texture();

	// Create default meshes
	void CreateTriangle();
	void CreateQuad();
	void CreateCube();
};

