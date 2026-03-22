#include "PhysicsEngine.h"
#include <iostream>
#include <mutex>
#include <vector>
#include <future>
#include <algorithm>

PhysicsEngine::PhysicsEngine() : bound(50000.0f)
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
    futures.reserve(grid->NUM_CELLS * grid->NUM_CELLS);

    for (int x = 0; x < grid->NUM_CELLS; x++) {
        for (int y = 0; y < grid->NUM_CELLS; y++) {
            futures.push_back(std::async(std::launch::async,
                [this, x, y]() {
                    HandleCollisions(x, y);
                }
            ));
        }
    }

    // Wait for all tasks to complete
    for (auto& fut : futures) {
        fut.get();
    }

    // Update positions and handle boundaries
    for (size_t i = 0; i < rigidbodies.size(); i++) {
        Rigidbody* body = rigidbodies.at(i);
        glm::vec3 oldCentroid = body->globalCentroid;
        // Update position
        body->globalCentroid += body->linearVelocity * deltatime;

        // Handle boundaries
        if (body->globalCentroid.y < 0.0f) {
            body->linearVelocity.y = -(body->linearVelocity.y);
            body->globalCentroid.y = 0.0f;
        }
        else if (body->globalCentroid.y > bound) {
            body->linearVelocity.y = -(body->linearVelocity.y);
            body->globalCentroid.y = bound;
        }

        if (body->globalCentroid.x < 0.0f) {
            body->linearVelocity.x = -(body->linearVelocity.x);
            body->globalCentroid.x = 0.0f;
        }
        else if (body->globalCentroid.x > bound) {
            body->linearVelocity.x = -(body->linearVelocity.x);
            body->globalCentroid.x = bound;
        }

        body->UpdatePositionFromGlobalCentroid();
        // Update model matrix
        grid->Move(body, oldCentroid.x, oldCentroid.y, body->globalCentroid.x, body->globalCentroid.y);
        modelMatrices[i] = body->getModel();
    }

}

void PhysicsEngine::AddRigidBody(Rigidbody* rigidbody)
{
    rigidbodies.push_back(rigidbody);
}

void PhysicsEngine::HandleCollisions(int cellX, int cellY)
{
    auto& currentCell = *grid->cells[cellX][cellY];
    if (currentCell.empty()) return;

    // Collect bodies from 3x3 neighborhood
    std::vector<Rigidbody*> nearbyBodies;
    nearbyBodies.reserve(currentCell.size());  // Estimate max capacity

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            int nx = cellX + dx;
            int ny = cellY + dy;

            if (nx >= 0 && nx < grid->NUM_CELLS &&
                ny >= 0 && ny < grid->NUM_CELLS)
            {
                auto& neighborSet = *grid->cells[nx][ny];
                nearbyBodies.insert(nearbyBodies.end(), neighborSet.begin(), neighborSet.end());
            }
        }
    }

    // Process collisions without nested loops
    for (auto bodyA : currentCell) {
        for (auto bodyB : nearbyBodies) {
            // Skip invalid pairs efficiently
            if (bodyA >= bodyB) continue;

            // Lock both bodies
            std::lock(bodyA->mtx, bodyB->mtx);
            std::lock_guard<std::mutex> lockA(bodyA->mtx, std::adopt_lock);
            std::lock_guard<std::mutex> lockB(bodyB->mtx, std::adopt_lock);

            if (bodyA->CheckCollision(bodyB)) {
                Collision collision = bodyA->ResolveCollision(bodyB);
                bodyA->linearVelocity = collision.finalV1;
                bodyB->linearVelocity = collision.finalV2;
            }
        }
    }
}