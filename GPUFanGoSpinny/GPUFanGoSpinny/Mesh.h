#pragma once
struct Vertex
{
	float pos[3] = { 0,0,0 };
};

class Mesh
{
public:
	Mesh();
	 //add number for a default mesh
	 //1 for triangle
	 //2 for cube
	Mesh(int p_default);
	~Mesh();

	inline std::vector<Vertex> getVertexData() { return m_vertexData; }

private:
	// Stores all the vertex data
	std::vector<Vertex>	 m_vertexData;

	// The amount of vertices this mesh has
	uint32_t m_numVertex = 0;

	// Create default meshes
	void CreateTriangle();
	void CreateCube();
};

