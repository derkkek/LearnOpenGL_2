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
	for (Rigidbody* body : rigidbodies)
	{

		// integrate linear velocity
		body->linearVelocity += body->inverseMass * (body->forceAccumulator * deltatime);

		// integrate angular velocity
		body->angularVelocity += body->globalInverseInertiaTensor * (body->torqueAccumulator * deltatime);

		// zero out accumulated force and torque
		body->forceAccumulator = glm::vec3(0.0f);
		body->torqueAccumulator = glm::vec3(0.0f);

		// integrate position
		body->globalCentroid += body->linearVelocity * deltatime;

		// integrate orientation
		const glm::vec3 axis = glm::normalize(body->angularVelocity);
		const float angle = glm::length(body->angularVelocity) * deltatime;
		body->orientation = body->RotationMatrix(axis, angle) * body->orientation;

		// update physical properties
		//body->UpdateOrientation();
		body->UpdatePositionFromGlobalCentroid();

		//std::cout << "VELOCITY: " << glm::to_string(rb->velocity) << "\n\n";
	}
}

void PhysicsEngine::AddRigidBody(Rigidbody* rigidbody)
{
	this->rigidbodies.push_back(rigidbody);
}
