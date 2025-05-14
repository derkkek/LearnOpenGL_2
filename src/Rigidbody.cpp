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

void Rigidbody::Integrate_RungeKutta(float dt)
{
	// Save initial state (position and velocity)
	glm::vec3 p0 = position;
	glm::vec3 v0 = velocity;

	// Compute initial acceleration (F/m)
	CalcAcc();
	glm::vec3 a = acceleration;  // Store acceleration since force is constant for RK4 steps

	// Compute RK4 slopes for velocity (k1v, k2v, k3v, k4v) and position (k1p, k2p, k3p, k4p)
	glm::vec3 k1v = a * dt;
	glm::vec3 k1p = v0 * dt;

	glm::vec3 k2v = a * dt;  // Acceleration remains constant (no drag/velocity-dependent forces)
	glm::vec3 k2p = (v0 + 0.5f * k1v) * dt;

	glm::vec3 k3v = a * dt;  // Same as k2v
	glm::vec3 k3p = (v0 + 0.5f * k2v) * dt;

	glm::vec3 k4v = a * dt;  // Same as k1v
	glm::vec3 k4p = (v0 + k3v) * dt;

	// Update velocity and position using weighted averages
	velocity = v0 + (k1v + 2.0f * k2v + 2.0f * k3v + k4v) / 6.0f;
	position = p0 + (k1p + 2.0f * k2p + 2.0f * k3p + k4p) / 6.0f;

	// Handle rotation (same as Euler)
	Rotate(glm::vec3(0.0f, 1.0f, 0.0f), dt);

	// Collision with ground (y = 0)
	if (position.y < 0.0f)
	{
		position.y = 0.0f;
		velocity.y = -velocity.y * 0.8f;  // Apply restitution
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
