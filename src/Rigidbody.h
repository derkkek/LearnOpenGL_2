#pragma once
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp> 
#include "glm/gtx/quaternion.hpp"
class Rigidbody
{
public:
	Rigidbody(glm::vec3 position);
	~Rigidbody() = default;

	void AddForce(glm::vec3 amount);
	void CalcAcc();
	void CalcVel(float deltatime);
	void CalcPos(float deltatime);


	void Integrate(float dt);
	void Integrate_RungeKutta(float dt);


	glm::vec3 ForwardPosition();
	glm::quat Rotate(glm::vec3 angular_velocity, float dt);


	void ResetForce();

	float mass = 1000.0f;


	glm::vec3 force = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);
	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 linearMomentum = mass * velocity;


	glm::vec3 position;
	glm::quat orientetion = glm::quat(1.0, 0.0, 0.0, 0.0);
	/*Calculate angular velocity with Tensors and torques, etc.*/
	glm::vec3 angularVelocity = glm::vec3(0.0f); // Orientation is a result of angular velocity, not a source for it.

private:

};
