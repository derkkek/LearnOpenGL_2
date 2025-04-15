#pragma once
#include "IRenderable.h"
#include "glm/glm.hpp"
#include "model.h"
#include "Shader.h"
#include <random>

const int MIN_SECTOR_COUNT = 2;
const int MIN_STACK_COUNT = 2;

class Sphere : public IRenderable
{
public:
	//Sphere(string const& path, glm::vec3 pos = glm::vec3(0), float mass = 100000.0f, glm::vec3 vel = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 force = glm::vec3(0.0,0.0f,0.0f), glm::vec3 acceleration = glm::vec3(0));
	Sphere(glm::vec3 position, glm::vec3 velocity, float mass, int sectors = 36, int stacks = 18, int up = 3);
	~Sphere() = default;

	//std::unique_ptr<Model> mesh;

	glm::vec3 GetNetForce();

	void AddForce(glm::vec3 amount);
	void CalcAcceleration();
	void CalcVelocity(float deltaTime);
	void Move(float deltatime);
	void CalcGravitation(Sphere &sphere, float G);

	void Translate(float deltatime, Shader& shader, string const& model_location);
	void Bind();

	float GetRS(float G, float speedOfLight);
	float GetDimple(float G, float speedOfLight);


	//Procedural Generation
	void clearArrays();
	void buildVerticesSmooth();

	void addVertex(float x, float y, float z);
	void addNormal(float nx, float ny, float nz);
	void addTexCoord(float s, float t);
	void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);
	void SetupBuffer();
	void buildInterleavedVertices();
	
	//interface contracts
	virtual void Draw() const override;
	virtual const glm::mat4 getModelMatrix() const override;
	virtual const glm::vec3 getObjectColor() const override;

	void printSelf() const;
	void set(float radius, int sectors, int stacks, int up);


	glm::vec3 position;
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 acceleration;
	float mass;
	glm::vec3 force;
	glm::vec3 velocity;
	
	const float* getVertices() const { return vertices.data(); }
	std::vector<float> vertices;
	float radius;

	glm::vec3 color;

private:
	// for vertex data
	unsigned int getVertexCount() const { return (unsigned int)vertices.size() / 3; }
	unsigned int getNormalCount() const { return (unsigned int)normals.size() / 3; }
	unsigned int getTexCoordCount() const { return (unsigned int)texCoords.size() / 2; }
	unsigned int getIndexCount() const { return (unsigned int)indices.size(); }
	unsigned int getTriangleCount() const { return getIndexCount() / 3; }
	unsigned int getVertexSize() const { return (unsigned int)vertices.size() * sizeof(float); }
	unsigned int getNormalSize() const { return (unsigned int)normals.size() * sizeof(float); }
	unsigned int getTexCoordSize() const { return (unsigned int)texCoords.size() * sizeof(float); }
	unsigned int getIndexSize() const { return (unsigned int)indices.size() * sizeof(unsigned int); }
	const float* getNormals() const { return normals.data(); }
	const float* getTexCoords() const { return texCoords.data(); }
	const unsigned int* getIndices() const { return indices.data(); }
	
	glm::vec3 GenerateRandomColor();
	void HandleModelUniform(Shader& shader, string const& location);


	unsigned int VAO, VBO, EBO;
	int sectorCount;                        // longitude, # of slices
	int stackCount;                         // latitude, # of stacks
	int upAxis;                             // +X=1, +Y=2, +z=3 (default)
	
	std::vector<float> normals;
	std::vector<float> texCoords;
	std::vector<unsigned int> indices;

	// interleaved
	std::vector<float> interleavedVertices;
	int interleavedStride;

};
