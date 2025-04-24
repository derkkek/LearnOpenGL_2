#include "Sphere.h"

//Sphere::Sphere(string const& path, glm::vec3 pos, float mass, glm::vec3 vel, glm::vec3 force, glm::vec3 acceleration)
//	:mesh(std::make_unique<Model>(path)), position(pos), velocity(vel), force(force), acceleration(acceleration), mass(mass)
//{
//
//}

Sphere::Sphere(Renderer& renderer, const std::string& vertex_source, const std::string& fragment_source, glm::vec3 position, glm::vec3 velocity, float mass, int sectors, int stacks, int up)
    : RenderableObject(renderer, vertex_source, fragment_source), 
      interleavedStride((3 + 3 + 2) * sizeof(float)), position(position), velocity(velocity), mass(mass)
{
    set(mass, sectors, stacks, up);
}

void Sphere::set(float radius, int sectors, int stacks, int up)
{
    if (mass > 0)
        this->radius = 8.0f / 3.0f * glm::pow(mass, 1.0f / 3.0f) * (1 / glm::pi<float>());
    this->sectorCount = sectors;
    if (sectors < MIN_SECTOR_COUNT)
        this->sectorCount = MIN_SECTOR_COUNT;
    this->stackCount = stacks;
    if (stacks < MIN_STACK_COUNT)
        this->stackCount = MIN_STACK_COUNT;
    this->upAxis = up;
    if (up < 1 || up > 3)
        this->upAxis = 3;

    this->color = GenerateRandomColor();


    buildVerticesSmooth();
    SetupBuffer();
    printSelf();
}

void Sphere::Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos)
{
    this->shader.use();
    this->shader.setMat4("model", this->model);
    this->shader.setMat4("view", view);
    this->shader.setMat4("projection", projection);
    this->shader.setVec3("viewPos", viewPos);
    this->shader.setVec3("Color", this->color);

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
}

glm::vec3 Sphere::GenerateRandomColor()
{
    std::random_device rd;  // Seed
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    return glm::vec3(dis(gen), dis(gen), dis(gen));
}

glm::vec3 Sphere::GetNetForce()
{
	return this->force;
}

void Sphere::AddForce(glm::vec3 amount)
{
	this->force += amount;
}

void Sphere::CalcAcceleration()
{
	this->acceleration = this->force / this->mass;
}

void Sphere::CalcVelocity(float deltaTime)
{
	this->velocity += acceleration * deltaTime;
}

void Sphere::Move(float deltatime)
{
	this->position += this->velocity * deltatime;

	glm::mat4 initModel = glm::mat4(1.0f);
	this->model = initModel;
	this->model = glm::translate(this->model, this->position); // translate it down so it's at the center of the scene
}

void Sphere::HandleModelUniform(Shader &shader, string const &location)
{
	shader.setMat4("model", this->model);
}

void Sphere::CalcGravitation(Sphere &sphere, float G)
{
	glm::vec3 forceVectoral = glm::vec3(0);
	glm::vec3 distance = sphere.position - this->position;
	glm::vec3 direction = glm::normalize(distance);


	float scalarForce = ((G * this->mass * sphere.mass) / std::pow(glm::distance(this ->position, sphere.position), 2));

	forceVectoral = scalarForce * direction;
	this->AddForce(forceVectoral);
	sphere.AddForce(-forceVectoral);	
}

void Sphere::Translate(float deltatime, Shader& shader, string const& model_location)
{
	CalcAcceleration();
	CalcVelocity(deltatime);
	Move(deltatime);
	HandleModelUniform(shader, model_location);
	this->force = glm::vec3(0);
}

void Sphere::Bind()
{
    glBindVertexArray(this->VAO);
}

float Sphere::GetRS(float G, float speedOfLight)
{
	return (2 * G * this->mass) / (speedOfLight * speedOfLight);
}

float Sphere::GetDimple(float G, float speedOfLight)
{
	return 2 * sqrt(this->GetRS(G, speedOfLight) * (this->radius - this->GetRS(G , speedOfLight)));
}




void Sphere::buildInterleavedVertices()
{
    std::vector<float>().swap(interleavedVertices);

    std::size_t i, j;
    std::size_t count = vertices.size();
    for (i = 0, j = 0; i < count; i += 3, j += 2)
    {
        interleavedVertices.push_back(vertices[i]);
        interleavedVertices.push_back(vertices[i + 1]);
        interleavedVertices.push_back(vertices[i + 2]);

        interleavedVertices.push_back(normals[i]);
        interleavedVertices.push_back(normals[i + 1]);
        interleavedVertices.push_back(normals[i + 2]);

        interleavedVertices.push_back(texCoords[j]);
        interleavedVertices.push_back(texCoords[j + 1]);
    }
}


void Sphere::clearArrays()
{
    std::vector<float>().swap(vertices);
    std::vector<float>().swap(normals);
    std::vector<float>().swap(texCoords);
    std::vector<unsigned int>().swap(indices);
}

void Sphere::addVertex(float x, float y, float z)
{
    vertices.push_back(x);
    vertices.push_back(y);
    vertices.push_back(z);
}



///////////////////////////////////////////////////////////////////////////////
// add single normal to array
///////////////////////////////////////////////////////////////////////////////
void Sphere::addNormal(float nx, float ny, float nz)
{
    normals.push_back(nx);
    normals.push_back(ny);
    normals.push_back(nz);
}



///////////////////////////////////////////////////////////////////////////////
// add single texture coord to array
///////////////////////////////////////////////////////////////////////////////
void Sphere::addTexCoord(float s, float t)
{
    texCoords.push_back(s);
    texCoords.push_back(t);
}



///////////////////////////////////////////////////////////////////////////////
// add 3 indices to array
///////////////////////////////////////////////////////////////////////////////
void Sphere::addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
{
    indices.push_back(i1);
    indices.push_back(i2);
    indices.push_back(i3);
}



void Sphere::buildVerticesSmooth()
{
    const float PI = acos(-1.0f);

    // clear memory of prev arrays
    clearArrays();

    float x, y, z, xy;                              // vertex position
    float nx, ny, nz, lengthInv = 1.0f / radius;    // normal
    float s, t;                                     // texCoord

    float sectorStep = 2 * PI / sectorCount;
    float stackStep = PI / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount; ++i)
    {
        stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
        xy = radius * cosf(stackAngle);             // r * cos(u)
        z = radius * sinf(stackAngle);              // r * sin(u)

        // add (sectorCount+1) vertices per stack
        // the first and last vertices have same position and normal, but different tex coords
        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep;           // starting from 0 to 2pi

            // vertex position
            x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
            addVertex(x, y, z);

            // normalized vertex normal
            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            addNormal(nx, ny, nz);

            // vertex tex coord between [0, 1]
            s = (float)j / sectorCount;
            t = (float)i / stackCount;
            addTexCoord(s, t);
        }
    }

    // indices
    //  k1--k1+1
    //  |  / |
    //  | /  |
    //  k2--k2+1
    unsigned int k1, k2;
    for (int i = 0; i < stackCount; ++i)
    {
        k1 = i * (sectorCount + 1);     // beginning of current stack
        k2 = k1 + sectorCount + 1;      // beginning of next stack

        for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
        {
            // 2 triangles per sector excluding 1st and last stacks
            if (i != 0)
            {
                addIndices(k1, k2, k1 + 1);   // k1---k2---k1+1
            }

            if (i != (stackCount - 1))
            {
                addIndices(k1 + 1, k2, k2 + 1); // k1+1---k2---k2+1
            }
        }
    }

    // generate interleaved vertex array as well
    buildInterleavedVertices();
}
void Sphere::SetupBuffer()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, interleavedVertices.size() * sizeof(float), interleavedVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, interleavedStride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, interleavedStride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, interleavedStride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sphere::printSelf() const
{
    std::cout << "===== Sphere =====\n"
        << "        Radius: " << radius << "\n"
        << "  Sector Count: " << sectorCount << "\n"
        << "   Stack Count: " << stackCount << "\n"
        << "       Up Axis: " << (upAxis == 1 ? "X" : (upAxis == 2 ? "Y" : "Z")) << "\n"
        << "Triangle Count: " << getTriangleCount() << "\n"
        << "   Index Count: " << getIndexCount() << "\n"
        << "  Vertex Count: " << getVertexCount() << "\n"
        << "  Normal Count: " << getNormalCount() << "\n"
        << "TexCoord Count: " << getTexCoordCount() << std::endl;
}
