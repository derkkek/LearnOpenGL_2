#include "Rigidbody.h"
#include <iostream>
#include <GLFW/glfw3.h>

Rigidbody::Rigidbody(glm::vec3 position)
	:position(position)
{

}

void Rigidbody::AddForce(glm::vec3 amount)
{
	this->force += amount;
}


void Rigidbody::CalcAcc()
{
	this->acceleration = this->force / this->mass;
}

void Rigidbody::CalcVel(float deltatime)
{
	this->velocity += this->acceleration * deltatime;
}

void Rigidbody::CalcPos(float deltatime)
{
	this->position += this->velocity * deltatime;
}

void Rigidbody::Integrate(float dt)
{
	// 1. compute acceleration
	CalcAcc();
	// 2. update velocity
	CalcVel(dt);

	// 3. update position
	CalcPos(dt);
	
	Rotate(glm::vec3(0.0f, 1.0f, 0.0f), dt);


	// 4. collision with ground (y=0)

	if (position.y < 0.0f) 
	{
		position.y = 0.0f;
		// invert Y velocity with restitution
		velocity.y = -velocity.y * 0.8f;
	}
}

glm::vec3 Rigidbody::ForwardPosition()
{
	return this->position;
}

glm::quat Rigidbody::Rotate(glm::vec3 angular_velocity, float dt)
{
	// Calculate rotation angle and axis
	float angle = glm::length(angular_velocity) * dt; // Magnitude of angular velocity × time
	glm::vec3 axis = glm::normalize(angular_velocity); // Rotation axis direction

	// Create rotation quaternion
	glm::quat angularDelta = glm::angleAxis(angle, axis);

	// Apply rotation in LOCAL space (order matters: orientetion * delta)
	this->orientetion = glm::normalize(this->orientetion * angularDelta);

	return angularDelta;
}

void Rigidbody::ResetForce()
{
	this->force = glm::vec3(0.0f);
}
