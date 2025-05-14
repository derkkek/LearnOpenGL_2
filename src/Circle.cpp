#include "Circle.h"

Circle::Circle(float radius, int vCount, glm::vec3 position)
	:radius(radius), vCount(vCount),rigidbody(new Rigidbody(position))
{
	BuildCircle();
    SetupBuffer();
    AssignTexture();
}

const int Circle::GetVertexCount() const
{
    return vertices.size();
}

const glm::mat4 Circle::GetModel()
{
    UpdateModel();
    return this->model;
}

void Circle::BuildCircle() {
    float angle = 360.0f / vCount;
    vertices.clear();

    // Add center vertex (index 0)
    vertices.push_back({
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec2(0.5f, 0.5f) // UV for center
        });

    // Perimeter vertices (indices 1 to vCount)
    for (int i = 0; i < vCount; i++) {
        float currentAngle = angle * i;
        float x = radius * cos(glm::radians(currentAngle));
        float y = radius * sin(glm::radians(currentAngle));

        float u = (x / (2 * radius)) + 0.5f;
        float v = (-y / (2 * radius)) + 0.5f;

        vertices.push_back({ {x, y, 0.0f}, {u, v} });
    }

    // Update indices to use center vertex
    indices.clear();
    for (int i = 0; i < vCount; i++) {
        indices.push_back(0);                // Center vertex
        indices.push_back(i + 1);            // Current perimeter vertex
        indices.push_back((i + 1) % vCount + 1); // Next perimeter vertex (wraps around)
    }
}

void Circle::SetupBuffer() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Buffer interleaved vertex data
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Position attribute (location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute (location 1)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(1);

    // Element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Circle::AssignTexture()
{
    this->textureID = TextureLoader::loadTexture("resource/textures/awesomeface.png");
}

void Circle::UpdateModel()
{
    this->model = glm::mat4(1.0f);

    glm::mat4 rotationMatrix = glm::toMat4(this->rigidbody->orientetion);

    this->model = glm::translate(this->model, this->rigidbody->ForwardPosition());

    this->model *= rotationMatrix;
}
