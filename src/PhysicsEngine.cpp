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
		rb->AddForce(glm::vec3(0.0f, -9.81f * rb->mass, 0.0f));

		rb->Integrate(deltatime);

		rb->ResetForce();
	}
}

void PhysicsEngine::AddRigidBody(Rigidbody* rigidbody)
{
	this->rigidbodies.push_back(rigidbody);
}
