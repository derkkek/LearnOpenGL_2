#pragma once
#include "glm/glm.hpp"

class Collider
{
public:
	Collider() = default;
	~Collider() = default;

	// already computed based on geometry
	float mass;
	glm::mat3 localInertiaTensor;
	glm::vec3 localCentroid;

	// geometry-related part not shown
private:

};

