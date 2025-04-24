#include "Cube.h"

Cube::Cube(Renderer& renderer, const std::string& vertex_source, const std::string& fragment_source) : RenderableObject(renderer, vertex_source, fragment_source)
{
    SetupBuffer();
    AssignTexture();

}

void Cube::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos)
{
    this->shader.use();

    shader.setMat4("model", this->model);
    shader.setMat4("view",view);
    shader.setMat4("projection", projection);
    shader.setVec3("viewPos", viewPos);
    shader.setInt("texture1", 0);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, this->textureID);
    //shader.setMat4("view")

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Cube::SetupBuffer()
{
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), &this->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
}

void Cube::AssignTexture(const std::string& path)
{
    this->textureID = TextureLoader::loadTexture(path.c_str());
}




