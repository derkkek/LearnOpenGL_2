#include "Rigidbody.h"
#include <iostream>

Rigidbody::Rigidbody(glm::vec3 position)
	:position(position)
{
}

void Rigidbody::AddForce(glm::vec3 amount)
{
	this->force += amount;
}

void Rigidbody::Translate(float deltatime)
{
	CalcAcc();
	CalcVel(deltatime);
	CalcPos(deltatime);

	//std::cout << glm::to_string(this->position) << "\n";
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

void Rigidbody::ResetForce()
{
	this->force = glm::vec3(0.0f);
}
