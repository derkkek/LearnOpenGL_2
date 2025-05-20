#include "Rigidbody.h"
#include <iostream>
#include <GLFW/glfw3.h>

Rigidbody::Rigidbody(glm::vec3 position, float area)
	:position(position)
{

}


void Rigidbody::UpdateGlobalCentroidFromPosition()
{
	globalCentroid = orientation * localCentroid + position;
}

void Rigidbody::UpdatePositionFromGlobalCentroid()
{
	position = orientation * -localCentroid + globalCentroid;
}

void Rigidbody::AddCollider(Collider& collider)  
{  
   // add collider to collider list  
   colliders.push_back(collider);  

   // reset local centroid & mass  
   localCentroid = glm::vec3(0.0f);  
   mass = 0.0f;  

   // compute local centroid & mass  
   for (Collider& collider : colliders)  
   {  
       // accumulate mass  
       mass += collider.mass;  

       // accumulate weighted contribution  
       localCentroid += collider.mass * collider.localCentroid;  
   }  

   // compute inverse mass  
   inverseMass = 1.0f / mass;

   // compute final local centroid  
   localCentroid *= inverseMass;  

   // compute local inertia tensor  
   glm::mat3 localInertiaTensor(0.0f);  
   for (Collider& collider : colliders)  
   {  
       const glm::vec3 r = localCentroid - collider.localCentroid;  
       const float rDotR = glm::dot(r, r);  
       const glm::mat3 rOutR = glm::outerProduct(r, r);  

       // accumulate local inertia tensor contribution,  
       // using Parallel Axis Theorem  
       localInertiaTensor += collider.localInertiaTensor + collider.mass * (rDotR * glm::mat3(1.0f) - rOutR);  
   }  

   // compute inverse inertia tensor  
   localInverseInertiaTensor = glm::inverse(localInertiaTensor);  
}

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

