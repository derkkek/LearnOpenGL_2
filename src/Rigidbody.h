#pragma once
#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtc/matrix_transform.hpp> // Include for glm::rotate
#include <glm/gtx/norm.hpp>
//#include "Collider.h"
#include <vector>
#include "CircleCollider.h"
struct Collision {
	glm::vec3 normal;
	glm::vec3 finalV1;
	glm::vec3 finalV2;
};

class Rigidbody
{
public:
	float mass;
	float inverseMass;
	glm::mat3 localInertiaTensor;
	glm::mat3 localInverseInertiaTensor;
	glm::mat3 globalInverseInertiaTensor;

	glm::vec3 globalCentroid;
	glm::vec3 localCentroid;

	glm::vec3 position;
	glm::mat3 orientation;
	glm::mat3 inverseOrientation = glm::transpose(orientation);
	glm::vec3 linearVelocity;
	glm::vec3 angularVelocity;

	glm::vec3 forceAccumulator;
	glm::vec3 torqueAccumulator;
	
	float radius;

	bool CheckCollision(Rigidbody* rb);

	Collision ResolveCollision(Rigidbody* rb);


	//std::vector<Collider> colliders;
	Rigidbody(glm::vec3 position, float area, float radius);
	~Rigidbody();
	void UpdateGlobalCentroidFromPosition();
	void UpdatePositionFromGlobalCentroid();

	void UpdateOrientation();

	//void AddCollider(Collider& collider);

	const glm::vec3 LocalToGlobal(const glm::vec3& p) const;
	const glm::vec3 GlobalToLocal(const glm::vec3& p) const;
	const glm::vec3 LocalToGlobalVec(const glm::vec3& v) const;
	const glm::vec3 GlobalToLocalVec(const glm::vec3& v) const;
  
	void ApplyForce(const glm::vec3& f, const glm::vec3& at);
	glm::mat3 RotationMatrix(const glm::vec3& axis, float angle);
private:
	void SIEulerIntegration(float dt);
};
