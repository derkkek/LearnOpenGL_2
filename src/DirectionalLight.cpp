#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 Direction, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular)
	:direction(Direction), ambient(Ambient), diffuse(Diffuse), specular(Specular)
{
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::PassUniforms(Shader shader)
{
    shader.setVec3("dirLight.direction", this->direction);
    shader.setVec3("dirLight.ambient", this->ambient);
    shader.setVec3("dirLight.diffuse", this->ambient);
    shader.setVec3("dirLight.specular", this->specular);
}
