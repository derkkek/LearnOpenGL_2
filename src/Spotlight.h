#pragma once
#include "glm/glm.hpp"
#include "Shader.h"
#include "Camera.h"

class Spotlight
{
public:
	Spotlight(glm::vec3 Position, glm::vec3 Direction, float Cutoff, float OuterCutoff, float Constant, float Linear, float Quadratic, 
        glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular);
	~Spotlight();
    void PassUniforms(Shader shader, Camera camera);

private:
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};
