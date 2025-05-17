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
	const int MaxUnits = 10;

private:
	std::vector<Rigidbody*> rigidbodies;

};
