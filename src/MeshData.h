#pragma once
#include "glm/glm.hpp"
#include "iostream"
#include <vector>

class MeshData
{

public:
	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 texCoord;
	};
	struct Texture
	{
		unsigned int ID;
		std::string path;
	};



	MeshData() = default;
	~MeshData() = default;
	const int GetVertexCount() const;
	void SetColor();


	glm::vec3 color;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

private:




};
