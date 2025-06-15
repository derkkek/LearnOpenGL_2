#pragma once
#include "Rigidbody.h"
#include <vector>
class PhysicsEngine
{
public:
	PhysicsEngine() = default;
	~PhysicsEngine();

	void StepWorld(float deltatime);
	void AddRigidBody(Rigidbody* rigidbody);
	const int MaxUnits = 300;
	int collisions = 0;
private:
	std::vector<Rigidbody*> rigidbodies;

};
