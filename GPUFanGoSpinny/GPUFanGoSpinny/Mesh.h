#pragma once

class VertexBuffer;
class Texture;
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

	void Bind();

private:
	// Number used to identify mesh
	// Not sure if this will be necessary in the future
	//unsigned int m_ID = 0;

	// Vertex Buffer class
	VertexBuffer* m_vertexBuffer = nullptr;

	// Texture class
	Texture* m_texture = nullptr;

	// Create default meshes
	void CreateTriangle();
	void CreateQuad();
	void CreateCube();
};

