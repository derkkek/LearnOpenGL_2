#include "PointLight.h"

PointLight::PointLight(glm::vec3 Position, float Constant, float Linear, float Quadratic, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular)
	:position(Position), constant(Constant), linear(Linear), quadratic(Quadratic), ambient(Ambient), diffuse(Diffuse), specular(Specular)
{
}

PointLight::~PointLight()
{
}

void PointLight::PassUniforms(Shader shader, int light_index)
{
    std::string index = std::to_string(light_index);

    shader.setVec3("pointLights[" + index + "].position", this->position);
    shader.setVec3("pointLights[" + index + "].ambient",this->ambient);
    shader.setVec3("pointLights[" + index + "].diffuse", this->diffuse);
    shader.setVec3("pointLights[" + index + "].specular", this->specular);
    shader.setFloat("pointLights[" + index + "].constant", this->constant);
    shader.setFloat("pointLights[" + index + "].linear", this->linear);
    shader.setFloat("pointLights[" + index + "].quadratic", this->quadratic);
}
