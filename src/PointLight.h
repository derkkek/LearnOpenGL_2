#pragma once
#include "glm/glm.hpp"
#include "Shader.h"

class PointLight
{
public:
	PointLight(glm::vec3 Position, float Constant, float Linear, float Quadratic, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular);
	~PointLight();
    void PassUniforms(Shader shader, int light_index);

private:
    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

};
