#include "Rigidbody.h"
#include "UniformGrid.h"

#include <iostream>
#include <GLFW/glfw3.h>	

Rigidbody::Rigidbody(glm::vec3 position, float area, float radius, UniformGrid* grid)
	:position(position), radius(radius), localCentroid(0.0f), globalCentroid(position), forceAccumulator(0.0f),
    torqueAccumulator(0.0f), localInertiaTensor(glm::mat3(1.0f)), 
    localInverseInertiaTensor(glm::mat3(1.0f)), globalInverseInertiaTensor(glm::mat3(1.0f)), 
    linearVelocity(0.0f), angularVelocity(1.0f)/*it shouldn't be 1. debugging purposes.*/, inverseMass(1.0f), mass(radius * 8.0f), orientation(glm::mat3(1.0f))
    
{
    grid->add(this);
}

Rigidbody::~Rigidbody()
{
}


bool Rigidbody::CheckCollision(Rigidbody* rb)
{
    float distanceX = (rb->globalCentroid.x - this->globalCentroid.x);
    float distanceY = (rb->globalCentroid.y - this->globalCentroid.y);
    float distance = distanceX * distanceX + distanceY * distanceY;
       //glm::distance(this->globalCentroid, rb->globalCentroid);
    float totalRadius = this->radius + rb->radius;

    return distance <= totalRadius * totalRadius;
}

Collision Rigidbody::ResolveCollision(Rigidbody* rb)
{
    Collision collision;

    collision.normal = rb->globalCentroid - this->globalCentroid;

    glm::vec3 unitNormal = collision.normal / (glm::sqrt(collision.normal.x * collision.normal.x + collision.normal.y * collision.normal.y));

    glm::vec3 unitTangent = glm::vec3(-unitNormal.y, unitNormal.x, 0.0f);

    float v1n = glm::dot(unitNormal, this->linearVelocity);
    float v1t = glm::dot(unitTangent, this->linearVelocity);

    float v2n = glm::dot(unitNormal, rb->linearVelocity);
    float v2t = glm::dot(unitTangent, rb->linearVelocity);

    float v1n_tilda = (v1n * (this->mass - rb->mass) + 2.0f * rb->mass * v2n) / (this->mass + rb->mass);
    float v2n_tilda = (v2n * (rb->mass - this->mass) + 2.0f * this->mass * v1n) / (this->mass + rb->mass);

    glm::vec3 V1 = unitNormal * v1n_tilda;
    glm::vec3 V1_tilda = unitTangent * v1t;

    glm::vec3 V2 = unitNormal * v2n_tilda;
    glm::vec3 V2_tilda = unitTangent * v2t;

    collision.finalV1 = V1 + V1_tilda;
    collision.finalV2 = V2 + V2_tilda;

    // Assume: A and B are pointers to Rigidbody, and collision.normal is normalized and points from A to B
    float penetration = (this->radius + rb->radius) - glm::length(rb->globalCentroid - this->globalCentroid);

    if (penetration > 0.0f) 
    {
        float totalInvMass = this->inverseMass + rb->inverseMass;
        // Avoid division by zero
        if (totalInvMass == 0.0f) return collision;

        // Move each object away from the other by their share of the overlap
        glm::vec3 correction = (penetration / totalInvMass) * 0.8f * unitNormal; // 0.8f is a bias to avoid oscillation
        this->globalCentroid -= correction * this->inverseMass;
        rb->globalCentroid += correction * rb->inverseMass;
        this->UpdatePositionFromGlobalCentroid();
        rb->UpdatePositionFromGlobalCentroid();
    }

    return collision;
}

void Rigidbody::UpdateGlobalCentroidFromPosition()
{
	globalCentroid = orientation * localCentroid + position;
}

void Rigidbody::UpdatePositionFromGlobalCentroid()
{
	position = orientation * -localCentroid + globalCentroid;
}

void Rigidbody::UpdateOrientation()
{
    // orthonormalize orientation matrix
    glm::quat q = glm::toQuat(orientation);
    q = glm::normalize(q);
    orientation = glm::toMat3(q);// ToMatrix() ?

    // compute inverse orientation matrix
    inverseOrientation = glm::transpose(orientation);
}

//void Rigidbody::AddCollider(Collider& collider)  
//{  
//   // add collider to collider list  
//   colliders.push_back(collider);  
//
//   // reset local centroid & mass  
//   localCentroid = glm::vec3(0.0f);  
//   mass = 0.0f;  
//
//   // compute local centroid & mass  
//   for (Collider& collider : colliders)  
//   {  
//       // accumulate mass  
//       mass += collider.mass;  
//
//       // accumulate weighted contribution  
//       localCentroid += collider.mass * collider.localCentroid;  
//   }  
//
//   // compute inverse mass  
//   inverseMass = 1.0f / mass;
//
//   // compute final local centroid  
//   localCentroid *= inverseMass;  
//
//   // compute local inertia tensor  
//   glm::mat3 localInertiaTensor(0.0f);  
//   for (Collider& collider : colliders)  
//   {  
//       const glm::vec3 r = localCentroid - collider.localCentroid;  
//       const float rDotR = glm::dot(r, r);  
//       const glm::mat3 rOutR = glm::outerProduct(r, r);  
//
//       // accumulate local inertia tensor contribution,  
//       // using Parallel Axis Theorem  
//       localInertiaTensor += collider.localInertiaTensor + collider.mass * (rDotR * glm::mat3(1.0f) - rOutR);  
//   }  
//
//   // compute inverse inertia tensor  
//   localInverseInertiaTensor = glm::inverse(localInertiaTensor);  
//}

const glm::vec3 Rigidbody::LocalToGlobal(const glm::vec3& p) const
{
    return orientation * p + position;
}

const glm::vec3 Rigidbody::GlobalToLocal(const glm::vec3& p) const
{
    return inverseOrientation * (p - position);;
}

const glm::vec3 Rigidbody::LocalToGlobalVec(const glm::vec3& v) const
{
    return orientation * v;
}

const glm::vec3 Rigidbody::GlobalToLocalVec(const glm::vec3& v) const
{
    return inverseOrientation * v;
}

void Rigidbody::ApplyForce(const glm::vec3& f, const glm::vec3& at)
{
	forceAccumulator += f;
	torqueAccumulator += glm::cross(at - globalCentroid, f);
}

glm::mat3 Rigidbody::RotationMatrix(const glm::vec3& axis, float angle)
{
    if (glm::length(axis) < 1e-6f) // Avoid division by zero
        return glm::mat3(1.0f); // Return identity matrix for zero axis

    return glm::mat3(glm::rotate(glm::mat4(1.0f), angle, axis));
}

void Rigidbody::SIEulerIntegration(float dt)
{

}

