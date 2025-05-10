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
	this->acceleration += this->force / this->mass;
}

void Rigidbody::CalcVel(float deltatime)
{
	if (this->position.y <= 0.0f)
	{
		this->velocity = -this->velocity;
		this->position.y += 0.01f;
	}
	this->velocity += this->acceleration * deltatime;
}

void Rigidbody::CalcPos(float deltatime)
{
	this->position += this->velocity * deltatime;
}

void Rigidbody::ResetForce()
{
	this->force = glm::vec3(0.0f);
}
