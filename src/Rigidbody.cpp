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
	ResetForce();
}

void Rigidbody::CalcAcc()
{
	this->acceleration += this->force / this->mass;
}

void Rigidbody::CalcVel(float deltatime)
{
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
