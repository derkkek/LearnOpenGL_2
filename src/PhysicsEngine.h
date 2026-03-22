#pragma once
#include "Rigidbody.h"
#include "UniformGrid.h"
#include "Broad.h"
#include <vector>
class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void StepWorld(float deltatime, glm::mat4* modelMatrices);
	void AddRigidBody(Rigidbody* rigidbody);
	const int MaxUnits = 25000;
	float bound;
	int collisions = 0;
	std::vector<Rigidbody*> rigidbodies;
	UniformGrid* grid;
	void HandleCollisions(int cellX, int cellY);

private:

	//BVHNode<BoundingSphere>* bvhRoot = nullptr;

};
