#pragma once
#include "Rigidbody.h"
#include "Broad.h"
#include <vector>
class PhysicsEngine
{
public:
	PhysicsEngine() = default;
	~PhysicsEngine();

	void StepWorld(float deltatime);
	void AddRigidBody(Rigidbody* rigidbody);
	const int MaxUnits = 1000;
	int collisions = 0;
	std::vector<Rigidbody*> rigidbodies;

private:
	std::vector<PotentialContact> Broadphase();
	BVHNode<BoundingSphere>* bvhRoot = nullptr;

};
