#include "Skybox.h"

Skybox::Skybox() : RenderableObject()
{
    SetupBuffer();
    AssignTexture();
}
const int Skybox::GetVertexCount() const
{
    return 108 / 3;
}
const glm::mat4 Skybox::GetModel()
{
    return glm::mat4(1.0f);
}
void Skybox::SetupBuffer()
{
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), &this->vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindVertexArray(0);
}

void Skybox::AssignTexture()
{
    this->textureID = TextureLoader::loadCubemap(this->faces);
}

//void Skybox::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos)
//{
//    this->shader.use();
//    this->shader.setInt("skybox", 0);
//
//    // draw skybox as last
//    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
//    glm::mat4 manipulatedView = glm::mat4(glm::mat3(view)); // remove translation from the view matrix
//    this->shader.setMat4("view", manipulatedView);
//    this->shader.setMat4("projection", projection);
//    // skybox cube
//    glBindVertexArray(this->VAO);
//    glActiveTexture(GL_TEXTURE0);
//    glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//    glBindVertexArray(0);
//    glDepthFunc(GL_LESS); // set depth function back to default
//
//}
