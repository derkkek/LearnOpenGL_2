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

		std::cout << "FORCE GRAVITY: " << glm::to_string(rb->force) << "\n\n";

		rb->Integrate_RungeKutta(deltatime);

		glm::vec3 dragforce = rb->CalcAirDragForce(AIRDENSITY, DRAG_COEFF);
		rb->AddForce(dragforce);

		std::cout << "FORCE GRAVITY PLUS DRAG FORCE: " << glm::to_string(rb->force) << "\n\n";
		rb->ResetForce();
	}
}

void PhysicsEngine::AddRigidBody(Rigidbody* rigidbody)
{
	this->rigidbodies.push_back(rigidbody);
}
