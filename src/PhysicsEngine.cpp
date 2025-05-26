#include "PhysicsEngine.h"
#include "iostream"

PhysicsEngine::~PhysicsEngine()
{
	rigidbodies.clear();
}

void PhysicsEngine::StepWorld(float deltatime)
{
	for (Rigidbody* body : rigidbodies)
	{
		body->ApplyForce(glm::vec3(0.0f, -9.81f * body->mass, 0.0f), body->globalCentroid);
		std::cout << "POSITION:" << glm::to_string(body->position) << "\n\n";
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
		body->UpdateOrientation();
		body->UpdatePositionFromGlobalCentroid();

		body->globalInverseInertiaTensor = body->orientation * body->localInertiaTensor * body->inverseOrientation;

		if (body->position.y < 0.0f)
		{
			body->position = glm::vec3(body->position.x, 0.0f, body->position.z);
			body->linearVelocity = glm::vec3(body->linearVelocity.x, -body->linearVelocity.y * 0.8f, body->linearVelocity.z);
		}
		//std::cout << "VELOCITY: " << glm::to_string(rb->velocity) << "\n\n";
	}
}

void PhysicsEngine::AddRigidBody(Rigidbody* rigidbody)
{
	this->rigidbodies.push_back(rigidbody);
}
