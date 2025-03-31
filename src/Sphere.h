#pragma once
#include "glm/glm.hpp"
#include "model.h"
#include "Shader.h"


class Sphere
{
public:
	Sphere(string const& path, glm::vec3 pos = glm::vec3(0), glm::vec3 vel = glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3 force = glm::vec3(0.0,100.0f,0.5f), glm::vec3 acceleration = glm::vec3(0), float mass = 1000.0f);
	~Sphere() = default;
	Model mesh;

	glm::vec3 GetNetForce();

	void AddForce(glm::vec3 amount);
	void CalcAcceleration();
	void CalcVelocity(float deltaTime);
	void Move(float deltatime);
	void HandleModelUniform(Shader &shader, string const& location);

	void Translate(float deltatime, Shader& shader, string const& model_location);

	glm::vec3 position;
	glm::mat4 model;
	glm::vec3 acceleration;


private:
	glm::vec3 velocity;
	glm::vec3 force;
	float mass;


};
