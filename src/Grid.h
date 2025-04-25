#pragma once
#include <vector>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "iostream"
#include <GLFW/glfw3.h>
#include "Sphere.h"
#include "Renderer.h"

#include "RenderableObject.h"


class Grid : public RenderableObject
{
public:
	Grid(float size, int divisions, const std::string& vertex_source, const std::string& fragment_source);
	~Grid() = default;

	void SetupBuffer();
	void PassUniforms(Shader& shader, std::string const& location, std::string const& projection_location);
	void BendGrid(const Sphere& sphere, float G, float sphereMass, float lightSpeed);
	void UpdateGridVertices(const std::vector<Sphere*>& spheres, const float G, const float c);

	void UpdateBuffer();

	void Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos) override;
	
	void Print();



	glm::mat4 model = glm::mat4(1.0f);


private:
	float left = -100.0f, right = 100.0f;  // Expand grid range
	float front = -100.0f, back = 100.0f;
	float step = 5.0f;

	std::vector<float> vertices;
	std::vector<float> originalVertices;

	float CalcRadialDistance(glm::vec3 sphereCenter, float grid_x, float grid_y, float grid_z);
	float CalcSchwarzschildRadius(float G, float sphereMass, float lightSpeed);
	void resetVertices();
	glm::mat4 view;
	glm::vec3 color = glm::vec3(0.5f);

	glm::mat4 projection = glm::ortho(
		-10.0f, 10.0f,  // X-axis range (left/right)
		-10.0f, 10.0f,  // Z-axis becomes Y after rotation (bottom/top)
		-100.0f, 100.0f  // Near/far (adjust to include Y=0)
	);

};

