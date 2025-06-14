#include "MeshData.h"
#include "glad/glad.h"
#include <random>

const int MeshData::GetVertexCount() const
{
	return this->vertices.size();
}

void MeshData::SetColor()
{
    std::random_device rd;  // Seed
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    this->color = glm::vec3(dis(gen), dis(gen), dis(gen));
}
