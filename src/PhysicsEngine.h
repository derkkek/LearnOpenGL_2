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

	void StepWorld(float deltatime);
	void AddRigidBody(Rigidbody* rigidbody);
	const int MaxUnits = 900;
	int collisions = 0;
	std::vector<Rigidbody*> rigidbodies;
	UniformGrid* grid;
	void HandleCollisions(std::vector<Rigidbody*> bodies);

private:
	std::vector<PotentialContact> Broadphase();
	void GridPartition();
	BVHNode<BoundingSphere>* bvhRoot = nullptr;

};
