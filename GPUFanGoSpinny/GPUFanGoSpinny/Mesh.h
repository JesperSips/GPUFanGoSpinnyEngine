#pragma once
struct Vertex
{
	float pos[3] = { 0,0,0 };
	float rgb[3] = { 0,0,0 };
};

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

	inline std::vector<Vertex> getVertexData() { return m_vertexData; }
	inline std::vector<GLuint> getIndices() { return m_indices; }

private:
	// Stores all the vertex data
	std::vector<Vertex>	 m_vertexData;

	// The amount of vertices this mesh has (not sure if this is necessary with the indices
	GLuint m_numVertex = 0;

	// Stores all indices (not sure if this just being integers is okay)
	std::vector<GLuint> m_indices;

	// The amount of indices this mesh has (no idea if this is necessary at all)
	GLuint m_numIndex = 0;

	// Create default meshes
	void CreateTriangle();
	void CreateQuad();
	void CreateCube();
};

