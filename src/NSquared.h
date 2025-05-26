#pragma once
#include "Broadphase.h"
#include "Rigidbody.h"
#include "AABB.h"
class NSquared : public Broadphase
{
public:

    virtual void Add(AABB* aabb)
    {
        aabbs.push_back(aabb);
    }

    virtual void Update(void)
    {
        // do nothing
    }

    virtual ColliderPairList& ComputePairs(void);
    virtual Collider* Pick(const glm::vec3& point) const;
    virtual void Query(const AABB& aabb, ColliderList& output) const;
    virtual RayCastResult RayCast(const Ray3& ray) const;

private:

    std::vector<AABB*> aabbs;
    ColliderPairList pairs;
};