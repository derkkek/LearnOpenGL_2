#include "Circle.h"

Circle::Circle(float radius, int vCount, glm::vec3 position, const std::string &texture_path)
	: RenderableObject(texture_path), radius(radius), vCount(vCount), momentOfInertia(0.25f * mass * radius * radius), Rigidbody(position, 3.14159f * radius * radius)
{
	BuildCircle();
}

const int Circle::GetVertexCount() const
{
    return mesh.vertices.size();
}

const glm::mat4 Circle::GetModel()
{
    UpdateModel();
    return this->model;
}

//float Circle::CalcMomentOfInertia()
//{
//	momentOfInertia = 0.25f * mass * radius * radius; // Moment of inertia for a solid disk
//    return momentOfInertia;
//}
//
//float Circle::CalcTorque()
//{
//    torque= radius * 1.0 - radius * 0.0f;
//    return torque;
//}
//
//float Circle::CalcAngularAcc()
//{
//	angularAcc = torque / momentOfInertia;
//    return angularAcc;
//}

void Circle::BuildCircle() 
{
    float angle = 360.0f / vCount;
    mesh.vertices.clear();

    // Add center vertex (index 0)
    mesh.vertices.push_back({
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

        mesh.vertices.push_back({ {x, y, 0.0f}, {u, v} });
    }

    // Update indices to use center vertex
    mesh.indices.clear();
    for (int i = 0; i < vCount; i++) {
        mesh.indices.push_back(0);                // Center vertex
        mesh.indices.push_back(i + 1);            // Current perimeter vertex
        mesh.indices.push_back((i + 1) % vCount + 1); // Next perimeter vertex (wraps around)
    }
}

void Circle::UpdateModel()
{
    this->model = glm::mat4(1.0f);

    //glm::mat4 rotationMatrix = glm::toMat4(orientation);

    this->model = glm::translate(this->model, this->position);

    //this->model *= rotationMatrix;
}
