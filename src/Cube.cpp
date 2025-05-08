#include "Cube.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Cube::Cube(glm::vec3 position) 
    : position(position)
{
    SetupBuffer();
    AssignTexture();
}

void Cube::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos)
{
    
}

const int Cube::GetVertexCount() const
{
    return 180/5; // size of vertices divided by size of a vertex.
}

void Cube::Translate(float deltatime)
{
    this->model = glm::mat4(1.0f);
    glm::vec3 vel = this->velocity;
    this->position += vel * deltatime;
    this->model = glm::translate(this->model, this->position);
}

void Cube::SetupBuffer()
{

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->instanceVBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), &this->vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Cube::AssignTexture(const std::string& path)
{
    this->textureID = TextureLoader::loadTexture(path.c_str());
}



