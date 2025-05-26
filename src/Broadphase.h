#pragma once  
#include <utility> // Include for std::pair  
#include <list>    // Include for std::list  
#include <vector>  // Include for std::vector  
#include <glm/glm.hpp> // Include for glm::vec3
#include "Collider.h"
#include "AABB.h"

typedef std::pair<Collider*, Collider*> ColliderPair;  
typedef std::list<ColliderPair> ColliderPairList;  
struct Ray3
{
    glm::vec3 pos;
    glm::vec3 dir;
};
struct RayCastResult
{
    bool hit;
    Collider* collider;
    glm::vec3 position;
    glm::vec3 normal;
};
class Broadphase  
{  
public:  

    // adds a new AABB to the broadphase  
    virtual void Add(AABB* aabb) = 0;  

    // updates broadphase to react to changes to AABB  
    virtual void Update(void) = 0;  

    // returns a list of possibly colliding colliders  
    virtual const ColliderPairList& ComputePairs(void) = 0;  

    // returns a collider that collides with a point  
    // returns null if no such collider exists  
    virtual Collider* Pick(const glm::vec3& point) const = 0;  

    // returns a list of colliders whose AABBs collide   
    // with a query AABB  
    typedef std::vector<Collider*> ColliderList;  
    virtual void Query(const AABB& aabb, ColliderList& output) const = 0;  

    // result contains the first collider the ray hits  
    // result contains null if no collider is hit  
    virtual RayCastResult RayCast(const Ray3& ray) const = 0;  
};