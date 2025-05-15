#include "RenderableObject.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "TextureLoader.h"

RenderableObject::RenderableObject(const std::string& texture_path)
{
    AssignTexture(texture_path.c_str());
}

unsigned int RenderableObject::GetVao()
{
	return this->VAO;
}

unsigned int RenderableObject::GetTexId()
{
	return this->textureID;
}

void RenderableObject::SetupBuffer()
{
    std::cout << "SETUP BUFFER CALLED\n\n";
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Buffer interleaved vertex data
    glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(MeshData::Vertex), mesh.vertices.data(), GL_STATIC_DRAW);

    // Position attribute (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute (location 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MeshData::Vertex), (void*)offsetof(MeshData::Vertex, texCoord));
    glEnableVertexAttribArray(1);

    // Element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderableObject::AssignTexture(const std::string& path)
{
    this->textureID = TextureLoader::loadTexture(path.c_str());
}

MeshData RenderableObject::SendMeshData()
{
    return this->mesh;
}
