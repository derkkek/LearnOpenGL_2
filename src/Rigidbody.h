#pragma once
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
class Rigidbody
{
public:
	Rigidbody(glm::vec3 position);
	~Rigidbody() = default;

	void AddForce(glm::vec3 amount);
	void Translate(float deltatime);

	void CalcAcc();
	void CalcVel(float deltatime);
	void CalcPos(float deltatime);

	void ResetForce();

	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 orientetion = glm::vec3(0.0f);

	glm::vec3 force = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);
	glm::vec3 velocity = glm::vec3(0.0f);
	float mass = 1000.0f;
private:

};
