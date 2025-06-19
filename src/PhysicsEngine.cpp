#include "PhysicsEngine.h"
#include "iostream"
#include "Broad.h" // for BVHNode, BoundingSphere, PotentialContact

PhysicsEngine::PhysicsEngine()
{
   grid = new UniformGrid;
}

PhysicsEngine::~PhysicsEngine()
{
    delete grid;
}

void PhysicsEngine::StepWorld(float deltatime)
{

    for (int x = 0; x < grid->NUM_CELLS; x++)
    {
        for (int y = 0; y < grid->NUM_CELLS; y++)
        {
            HandleCollisions(grid->cells[x][y]);
        }
    }

    //for (size_t i = 0; i < rigidbodies.size(); ++i) {
    //    for (size_t j = i + 1; j < rigidbodies.size(); ++j) {
    //        // Check collision between rigidbodies[i] and rigidbodies[j]
    //        if (rigidbodies[i]->CheckCollision(rigidbodies[j])) {
    //            Collision collision = rigidbodies[i]->ResolveCollision(rigidbodies[j]);
    //            rigidbodies[i]->linearVelocity = collision.finalV1;
    //            rigidbodies[j]->linearVelocity = collision.finalV2;
    //        }
    //    }
    //}

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
        if (body->globalCentroid.x < 0.0f|| body->globalCentroid.x > 2000.0f) {
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

void PhysicsEngine::HandleCollisions(std::vector<Rigidbody*> bodies)
{
    for (size_t i = 0; i < bodies.size(); ++i) 
    {
        for (size_t j = i + 1; j < bodies.size(); ++j)
        {
            // Check collision between rigidbodies[i] and rigidbodies[j]
            if (bodies[i]->CheckCollision(bodies[j]))
            {
                Collision collision = bodies[i]->ResolveCollision(bodies[j]);
                bodies[i]->linearVelocity = collision.finalV1;
                bodies[j]->linearVelocity = collision.finalV2;
            }
        }
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

void PhysicsEngine::GridPartition()
{
    std::vector<Rigidbody*> grid[100][100];
    for (size_t i = 0; i < rigidbodies.size(); ++i) 
    {
        Rigidbody* body = rigidbodies.at(i);

        for (size_t j = 0; j < rigidbodies.size(); ++j)
        {
            if (body->globalCentroid.x <= 1.0f)
            {
                grid[0][j].push_back(body);

            }
        }
    }

}
