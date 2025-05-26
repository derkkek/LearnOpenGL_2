#include "NSquared.h"

ColliderPairList& NSquared::ComputePairs(void)
{
    pairs.clear();

    // outer loop
    auto end = aabbs.end();
    for (auto i = aabbs.begin(); i != end; ++i)
    {

        // inner loop
        auto jStart = i;
        for (auto j = ++jStart; j != end; ++j)
        {
            AABB* aabbA = *i;
            AABB* aabbB = *j;
            Collider* colliderA = aabbA->getCollider();
            Collider* colliderB = aabbB->getCollider();
            Rigidbody* bodyA = colliderA->Body();
            Rigidbody* bodyB = colliderB->Body();

            // skip same-body collision
            if (bodyA == bodyB)
                continue;

            // add collider pair
            if (aabbA->Collides(aabbB))
                pairs.push_back(
                    std::make_pair(aabbA->getCollider(), aabbB->getCollider()));

        } // end of inner loop
    } // end of outer loop

    return pairs;
}
