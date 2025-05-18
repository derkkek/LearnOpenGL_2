#pragma once
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp> 
#include "glm/gtx/quaternion.hpp"
#include <glm/gtx/norm.hpp>

class Rigidbody
{
public:
	Rigidbody(glm::vec3 position, float area);
	virtual ~Rigidbody() {}

	virtual float CalcMomentOfInertia() = 0;

	void AddForce(glm::vec3 amount);
	void CalcAcc();
	void CalcVel(float deltatime);
	void CalcPos(float deltatime);

	glm::vec3 CalcAirDragForce(float air_density, float drag_coeffiecent);
	//bool CheckForCollisions();
	void Integrate(float dt);
	void Integrate_RungeKutta(float dt);


	glm::vec3 ForwardPosition();
	glm::quat Rotate(glm::vec3 angular_velocity, float dt);


	void ResetForce();

	const float AIRDENSITY = 1.23f; //  kg/m^3;
	const float DRAG_COEFF = 0.6f;
	float mass = 1.0f;

	glm::vec3 force = glm::vec3(0.0f);
	glm::vec3 acceleration = glm::vec3(0.0f);
	glm::vec3 velocity;
	glm::vec3 linearMomentum = mass * velocity;

	glm::vec3 impactForces = glm::vec3(0.0f);
	bool collision = false;

	float area;

	glm::vec3 position;
	glm::quat orientetion = glm::quat(1.0, 0.0, 0.0, 0.0);
	/*Calculate angular velocity with Tensors and torques, etc.*/
	float angularVelocity = 0.0f; // Orientation is a result of angular velocity, not a source for it.
private:

};
