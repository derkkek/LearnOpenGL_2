#include "PhysicsEngine.h"
#include "iostream"
#include "Broad.h" // for BVHNode, BoundingSphere, PotentialContact
#include <future>
#include <vector>
PhysicsEngine::PhysicsEngine()
{
   grid = new UniformGrid;
}

PhysicsEngine::~PhysicsEngine()
{
    delete grid;
}

void PhysicsEngine::StepWorld(float deltatime, glm::mat4* modelMatrices)
{  
    // Parallel collision handling
    std::vector<std::future<void>> futures;
    for (int x = 0; x < grid->NUM_CELLS; x++) 
    {
        for (int y = 0; y < grid->NUM_CELLS; y++) 
        {
            futures.push_back(std::async(std::launch::async, [this, x, y]() {
                HandleCollisions(*(grid->cells[x][y]));
                }));
        }
    }
    //for (auto& f : futures) f.get();

    for (size_t i = 0; i < rigidbodies.size(); i++ )  
    {  
        Rigidbody* body = rigidbodies.at(i);
        glm::vec3 oldCentroid = body->globalCentroid; 
        body->globalCentroid += body->linearVelocity * deltatime;

        if (body->globalCentroid.y < 0.0f || body->globalCentroid.y > 50000.0f) 
        {  
            body->linearVelocity.y = -body->linearVelocity.y;  
            body->globalCentroid += body->linearVelocity * deltatime;
        }  
        if (body->globalCentroid.x < 0.0f || body->globalCentroid.x > 50000.0f) 
        {  
            body->linearVelocity.x = -body->linearVelocity.x;
            body->globalCentroid += body->linearVelocity * deltatime;
        }  


        
        body->UpdatePositionFromGlobalCentroid();  
        grid->Move(body, oldCentroid.x, oldCentroid.y, body->globalCentroid.x, body->globalCentroid.y);
        modelMatrices[i] = body->getModel(); // it's here cuz of optimization... im currently in oop rocksolid hell...
    }  
}

void PhysicsEngine::AddRigidBody(Rigidbody* rigidbody)
{
    this->rigidbodies.push_back(rigidbody);
}

void PhysicsEngine::HandleCollisions(std::unordered_set<Rigidbody*> bodies)  
{  
    std::vector<Rigidbody*> bodyVector(bodies.begin(), bodies.end()); // Convert unordered_set to vector  

    for (size_t i = 0; i < bodyVector.size(); ++i)  
    {  
        for (size_t j = i + 1; j < bodyVector.size(); ++j)  
        {  
            if (bodyVector[i]->CheckCollision(bodyVector[j]))  
            {  
                Collision collision = bodyVector[i]->ResolveCollision(bodyVector[j]); 
                bodyVector[i]->linearVelocity = collision.finalV1;  
                bodyVector[j]->linearVelocity = collision.finalV2;  
            }  
        }  
    }  
}



