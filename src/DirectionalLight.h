#pragma once
#include "Shader.h"
#include "glm/glm.hpp"

class DirectionalLight
{
public:
	DirectionalLight(glm::vec3 Direction, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular);
	~DirectionalLight();
	void PassUniforms(Shader shader);


private:
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};





