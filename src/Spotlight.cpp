#include "Spotlight.h"

Spotlight::Spotlight(glm::vec3 Position, glm::vec3 Direction, float Cutoff, float OuterCutoff, float Constant, float Linear, float Quadratic, glm::vec3 Ambient, glm::vec3 Diffuse, glm::vec3 Specular)
	:position(Position), direction(Direction), cutOff(Cutoff), outerCutOff(OuterCutoff), constant(Constant), linear(Linear), quadratic(Quadratic),
	ambient(Ambient), diffuse(Diffuse), specular(Specular)
{

}

Spotlight::~Spotlight()
{
}

void Spotlight::PassUniforms(Shader shader, Camera camera)
{
    shader.setVec3("spotLight.position", camera.Position);
    shader.setVec3("spotLight.direction", camera.Front);
    shader.setVec3("spotLight.ambient", this->ambient);
    shader.setVec3("spotLight.diffuse", this->diffuse);
    shader.setVec3("spotLight.specular", this->specular);
    shader.setFloat("spotLight.constant", this->constant);
    shader.setFloat("spotLight.linear", this->linear);
    shader.setFloat("spotLight.quadratic", this->quadratic);
    shader.setFloat("spotLight.cutOff", this->cutOff);
    shader.setFloat("spotLight.outerCutOff", this->outerCutOff);
}
