#include "PhysicsEngine.h"
#include "iostream"
#include "Broad.h" // for BVHNode, BoundingSphere, PotentialContact

PhysicsEngine::~PhysicsEngine()
{
	//rigidbodies.clear();
}

void PhysicsEngine::StepWorld(float deltatime)
{

    for (size_t i = 0; i < rigidbodies.size(); ++i) {
        for (size_t j = i + 1; j < rigidbodies.size(); ++j) {
            // Check collision between rigidbodies[i] and rigidbodies[j]
            if (rigidbodies[i]->CheckCollision(rigidbodies[j])) {
                Collision collision = rigidbodies[i]->ResolveCollision(rigidbodies[j]);
                rigidbodies[i]->linearVelocity = collision.finalV1;
                rigidbodies[j]->linearVelocity = collision.finalV2;
            }
        }
    }

    for (Rigidbody* body : rigidbodies)
    {
        // Integrate velocities
        
        //body->linearVelocity += body->inverseMass * (body->forceAccumulator * deltatime);

        // Integrate position
        body->globalCentroid += body->linearVelocity * deltatime;

        // Wall bounce logic (combine x and y checks)
        bool bounced = false;
        if (body->globalCentroid.y < 0.0f || body->globalCentroid.y > 1000.0f) {
            body->linearVelocity.y = -body->linearVelocity.y;
            bounced = true;
        }
        if (body->globalCentroid.x < -1000.0f || body->globalCentroid.x > 1000.0f) {
            body->linearVelocity.x = -body->linearVelocity.x;
            bounced = true;
        }
        if (bounced) {
            body->globalCentroid += body->linearVelocity * deltatime;
            collisions++;
        }

        // Update physical properties
        body->UpdatePositionFromGlobalCentroid();

    }
}

void PhysicsEngine::AddRigidBody(Rigidbody* rigidbody)
{
    this->rigidbodies.push_back(rigidbody);
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
