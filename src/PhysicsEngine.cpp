#include "PhysicsEngine.h"
#include "iostream"
#include "Broad.h" // for BVHNode, BoundingSphere, PotentialContact

PhysicsEngine::~PhysicsEngine()
{
	//rigidbodies.clear();
}

void PhysicsEngine::StepWorld(float deltatime)
{
    // Broadphase: get potential collision pairs
    std::vector<PotentialContact> potentialContacts = Broadphase();

    // Narrow phase: resolve only potential pairs
    for (const PotentialContact& pc : potentialContacts) {
        Rigidbody* bodyA = pc.body[0];
        Rigidbody* bodyB = pc.body[1];
        if (bodyA && bodyB && bodyA != bodyB && bodyA->CheckCollision(bodyB)) {
            Collision collision = bodyA->ResolveCollision(bodyB);
            bodyA->linearVelocity = collision.finalV1;
            bodyB->linearVelocity = collision.finalV2;
            collisions++;
        }
    }

    for (Rigidbody* body : rigidbodies)
    {
        // Integrate velocities
        body->linearVelocity += body->inverseMass * (body->forceAccumulator * deltatime);
        body->angularVelocity += body->globalInverseInertiaTensor * (body->torqueAccumulator * deltatime);

        // Integrate position
        body->globalCentroid += body->linearVelocity * deltatime;

        // Wall bounce logic (combine x and y checks)
        bool bounced = false;
        if (body->globalCentroid.y < 0.0f || body->globalCentroid.y > 500.0f) {
            body->linearVelocity.y = -body->linearVelocity.y;
            bounced = true;
        }
        if (body->globalCentroid.x < -500.0f || body->globalCentroid.x > 500.0f) {
            body->linearVelocity.x = -body->linearVelocity.x;
            bounced = true;
        }
        if (bounced) {
            body->globalCentroid += body->linearVelocity * deltatime;
            collisions++;
        }

        // Update physical properties
        body->UpdateOrientation();
        body->UpdatePositionFromGlobalCentroid();
        body->globalInverseInertiaTensor = body->orientation * body->localInertiaTensor * body->inverseOrientation;

        // Zero out accumulated force and torque
        body->forceAccumulator = glm::vec3(0.0f);
        body->torqueAccumulator = glm::vec3(0.0f);
    }
}

void PhysicsEngine::AddRigidBody(Rigidbody* rigidbody)
{
    this->rigidbodies.push_back(rigidbody);
    BoundingSphere sphere(rigidbody->globalCentroid, rigidbody->radius);
    if (!bvhRoot) {
        bvhRoot = new BVHNode<BoundingSphere>(nullptr, sphere, rigidbody);
    } else {
        bvhRoot->insert(rigidbody, sphere);
    }
}

// Returns a vector of potential collision pairs (broadphase)
std::vector<PotentialContact> PhysicsEngine::Broadphase() {
    std::vector<PotentialContact> potentialContacts;

    // Build the BVH
    BVHNode<BoundingSphere>* root = nullptr;
    for (Rigidbody* rb : rigidbodies) {
        // Add a larger padding factor to the radius (e.g. 2.0f)
        float paddedRadius = rb->radius;
        BoundingSphere sphere(rb->globalCentroid, paddedRadius);
        
        if (!root) {
            root = new BVHNode<BoundingSphere>(nullptr, sphere, rb);
        } else {
            root->insert(rb, sphere);
        }
    }

    // Collect potential contacts
    if (root) {
        // Estimate a reasonable upper bound for the number of contacts
        size_t maxContacts = 10;//rigidbodies.size() * (rigidbodies.size() - 1) / 2;
        potentialContacts.resize(maxContacts);

        unsigned found = root->getPotentialContacts(potentialContacts.data(), static_cast<unsigned>(maxContacts));
        potentialContacts.resize(found);

        // Debug output for number of potential contacts
        std::cout << "Broadphase found " << found << " potential contacts." << std::endl;

        delete root;
    }

    return potentialContacts;
}
