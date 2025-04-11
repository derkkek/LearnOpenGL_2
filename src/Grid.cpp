#include "Grid.h"

Grid::Grid(float size, int divisions) 
{
    float step = size / divisions;
    float halfSize = size / 2.0f;

    // x axis
    for (int zStep = 0; zStep <= divisions; ++zStep) 
    {
        float z = -halfSize + zStep * step;
        for (int xStep = 0; xStep < divisions; ++xStep) 
        {
            float xStart = -halfSize + xStep * step;
            float xEnd = xStart + step;
            float y = 0;
            vertices.push_back(xStart); vertices.push_back(y); vertices.push_back(z);
            vertices.push_back(xEnd);   vertices.push_back(y); vertices.push_back(z);
        }
    }
    
    // zaxis
    for (int xStep = 0; xStep <= divisions; ++xStep) 
    {
        float x = -halfSize + xStep * step;
        for (int zStep = 0; zStep < divisions; ++zStep) 
        {
            float zStart = -halfSize + zStep * step;
            float zEnd = zStart + step;
            float y = 0;
            vertices.push_back(x); vertices.push_back(y); vertices.push_back(zStart);
            vertices.push_back(x); vertices.push_back(y); vertices.push_back(zEnd);
        }
        
    }

    SetupBuffer();
    originalVertices = vertices;
}

void Grid::SetupBuffer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

void Grid::PassUniforms(Shader& shader, std::string const& model_location, std::string const& projection_location)
{
    shader.setMat4(model_location, this->model);
    //shader.setMat4(projection_location, this->projection);
}


void Grid::UpdateBuffer()
{
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Grid::Draw()
{
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_LINES, 0, vertices.size() / 3); // 3 components per vertex
}

void Grid::Print()
{
    for (size_t i = 0; i < vertices.size(); i += 3)
    {
        std::cout << "Position: ("
            << vertices[i] << ", "
            << vertices[i + 1] << ", "
            << vertices[i + 2] << ")" << std::endl;
    }
}

void Grid::resetVertices()
{
    vertices = originalVertices;
}

float Grid::CalcRadialDistance(glm::vec3 sphereCenter, float grid_x, float grid_y, float grid_z)
{
    float dx = grid_x - sphereCenter.x;
    float dy = grid_y - sphereCenter.y;
    float dz = grid_z - sphereCenter.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

float Grid::CalcSchwarzschildRadius(float G, float sphereMass, float lightSpeed)
{
    return ((2 * G * sphereMass) / (lightSpeed * lightSpeed));

}

void Grid::BendGrid(const Sphere& sphere, float G, float sphereMass, float lightSpeed)
{
    float rs = CalcSchwarzschildRadius(G, sphereMass, lightSpeed);

    float originalMaxY =0;

    for (int i = 0; i < vertices.size(); i += 3) {
       originalMaxY = std::max(originalMaxY, vertices[i + 1]);
    }

    float verticalShift = abs(sphere.position.y - originalMaxY);


    for (size_t i = 0; i < vertices.size(); i += 3)
    {
        glm::vec3 vertexPos(vertices[i], vertices[i + 1], vertices[i + 2]);

        float r = glm::length(vertexPos - sphere.position); // CalcRadialDistance(sphere.position, vertexPos.x, vertexPos.y, vertexPos.z);
        float curve = 0.0f;
        if (r > rs)
        {
            curve = 4.0f * sqrt(rs * 1000.0f* (r - rs));
        }
        vertices[i + 1] = curve -verticalShift;
    }
}

void Grid::UpdateGridVertices(std::vector<Sphere*>& spheres, const float G, const float c) 
{
    // centre of mass calc

    //for (const auto& spherePtr : spheres) {
    //    const Sphere& sphere = *spherePtr; // Dereference the pointer
    //    comY += sphere.mass * sphere.position.y;
    //    totalMass += sphere.mass;
    //}




    for (int i = 0; i < vertices.size(); i += 3) {

        // mass bending space
        glm::vec3 vertexPos(vertices[i], vertices[i + 1], vertices[i + 2]);
        glm::vec3 totalDisplacement(0.0f);
        float r{};
        float shpereY{};
        float constant = 3.0f;
        for (const auto& spherePtr : spheres) 
{
            const Sphere& sphere = *spherePtr;

            //glm::vec3 toObject = sphere.position - vertexPos;
            float distance = glm::distance(sphere.position,vertexPos);
            //float distance_m = distance * 1000.0f;
            float rs = (2 * G * sphere.mass) / (c * c);

            r = constant * sqrt(rs * (distance - rs));
            /*if (dz > rs)*/
            
            totalDisplacement.y += r;

            
            shpereY += sphere.position.y;
        }
        vertices[i + 1] = totalDisplacement.y - 100 * constant; // -4.0f / 3.0f * shpereY;// -abs(verticalShift);
    }
}
