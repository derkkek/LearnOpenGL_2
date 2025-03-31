#include "Sphere.h"

Sphere::Sphere(string const& path, glm::vec3 pos, glm::vec3 vel, glm::vec3 force, glm::vec3 acceleration, float mass)
	:mesh(path), position(pos), velocity(vel), force(force), acceleration(acceleration), mass(mass)
{

}

glm::vec3 Sphere::GetNetForce()
{
	return this->force;
}

void Sphere::AddForce(glm::vec3 amount)
{
	this->force += amount;
}

void Sphere::CalcAcceleration()
{
	this->acceleration = this->force / this->mass;
}

void Sphere::CalcVelocity(float deltaTime)
{
	this->velocity += acceleration * deltaTime;
}

void Sphere::Move(float deltatime)
{
	this->position += this->velocity * deltatime;

	glm::mat4 initModel = glm::mat4(1.0f);
	this->model = initModel;
	this->model = glm::translate(this->model, this->position); // translate it down so it's at the center of the scene
	this->model = glm::scale(this->model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
}

void Sphere::HandleModelUniform(Shader &shader, string const &location)
{
	shader.setMat4("model", this->model);
}

void Sphere::Translate(float deltatime, Shader& shader, string const& model_location)
{
	CalcAcceleration();
	CalcVelocity(deltatime);
	Move(deltatime);
	HandleModelUniform(shader, model_location);
	this->force = glm::vec3(0);
}
