#include "Cube.h"

Cube::Cube(const std::string& vertex_source, const std::string& fragment_source) : RenderableObject(vertex_source, fragment_source)
{
    DefineInstanceOffsets();
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
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 100);
    glBindVertexArray(0);
}

void Cube::SetupBuffer()
{

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->instanceVBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), &this->vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, this->instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 100, &translations[0], GL_STATIC_DRAW);



    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));


    // also set instance data
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, this->instanceVBO); // this attribute comes from a different vertex buffer
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Cube::AssignTexture(const std::string& path)
{
    this->textureID = TextureLoader::loadTexture(path.c_str());
}

void Cube::DefineInstanceOffsets()
{
    int index = 0;
    float offset = 5.0f;
    for (int x = -50; x < 50; x += 1)
    {
        glm::vec3 translation;
        translation.x = 1.5f * x + offset + 20.0f;//(float)x / 10.0f + offset;
        translation.y = sin(x);
        translation.z = 0.0f;
        translations[index++] = translation;
    }
}




