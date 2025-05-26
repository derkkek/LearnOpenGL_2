#pragma once
#include "glm/glm.hpp"
#include "Rigidbody.h"

class Collider
{
public:
	Collider() = default;
	~Collider() = default;

	// already computed based on geometry
	float mass;
	glm::mat3 localInertiaTensor;
	glm::vec3 localCentroid;

	Rigidbody* Body();
	// geometry-related part not shown
private:
	Rigidbody* body;
	Collider* next;

       
};

