#pragma once
#include <glm/glm.hpp>

class CircleCollider
{
public:
	CircleCollider(glm::vec3 pos, float radius);
	~CircleCollider() = default;

	glm::vec3 position;
	//float radius;

	bool CheckCollision(CircleCollider &circle_collider);
private:

};

