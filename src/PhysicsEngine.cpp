#include "PhysicsEngine.h"
#include "iostream"

PhysicsEngine::~PhysicsEngine()
{
	for (Rigidbody* rb : rigidbodies)
	{
		delete rb;
		rb = nullptr;
	}
}

void PhysicsEngine::StepWorld(float deltatime)
{
	for (Rigidbody* rb : rigidbodies)
	{
		rb->Integrate(deltatime);



		//std::cout << "VELOCITY: " << glm::to_string(rb->velocity) << "\n\n";
	}
}

void PhysicsEngine::AddRigidBody(Rigidbody* rigidbody)
{
	this->rigidbodies.push_back(rigidbody);
}
