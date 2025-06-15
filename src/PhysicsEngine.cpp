#include "PhysicsEngine.h"
#include "iostream"

PhysicsEngine::~PhysicsEngine()
{
	//rigidbodies.clear();
}

void PhysicsEngine::StepWorld(float deltatime)
{
	for (Rigidbody* body : rigidbodies)
	{
		Rigidbody* currentBody = body;
		//body->ApplyForce(glm::vec3(9.81f * body->mass, -9.81f * body->mass, 0.0f), body->globalCentroid);
		for (Rigidbody* body : rigidbodies)
		{

			if (currentBody != body)
			{

				if (currentBody->CheckCollision(body))
				{
					Collision collision = currentBody->ResolveCollision(body);
					currentBody->linearVelocity = collision.finalV1;
					body->linearVelocity = collision.finalV2;
					collisions++;
				}

			}

		}

		
		// integrate linear velocity
		body->linearVelocity += body->inverseMass * (body->forceAccumulator * deltatime);

		// integrate angular velocity
		body->angularVelocity += body->globalInverseInertiaTensor * (body->torqueAccumulator * deltatime);



		// integrate position
		body->globalCentroid += body->linearVelocity * deltatime;

		// integrate orientation
		//const glm::vec3 axis = glm::normalize(body->angularVelocity);
		//const float angle = glm::length(body->angularVelocity) * deltatime;
		//body->orientation = body->RotationMatrix(axis, angle) * body->orientation;

		// update physical properties
		body->UpdateOrientation();
		body->UpdatePositionFromGlobalCentroid();


		body->globalInverseInertiaTensor = body->orientation * body->localInertiaTensor * body->inverseOrientation;

		if (body->globalCentroid.y < 0.0f || body->globalCentroid.y > 50.0f)
		{
			//body->position = glm::vec3(body->position.x, 0.0f, body->position.z);
			body->linearVelocity = glm::vec3(body->linearVelocity.x, -body->linearVelocity.y, body->linearVelocity.z);
			body->globalCentroid += body->linearVelocity * deltatime;
			body->UpdatePositionFromGlobalCentroid();
			collisions++;
		}

		if (body->globalCentroid.x < -50.0f || body->globalCentroid.x > 50.0f)
		{
			//body->position = glm::vec3(body->position.x, 0.0f, body->position.z);
			body->linearVelocity = glm::vec3(-body->linearVelocity.x, body->linearVelocity.y, body->linearVelocity.z);
			body->globalCentroid += body->linearVelocity * deltatime;
			body->UpdatePositionFromGlobalCentroid();
			collisions++;
		}
		// zero out accumulated force and torque
		body->forceAccumulator = glm::vec3(0.0f);
		body->torqueAccumulator = glm::vec3(0.0f);
		//std::cout << "VELOCITY: " << glm::to_string(rb->velocity) << "\n\n";
	}
}

void PhysicsEngine::AddRigidBody(Rigidbody* rigidbody)
{
	this->rigidbodies.push_back(rigidbody);
}
