/*
 * Implementation file for the coarse collision detector.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

#include "Broad.h"
#include <iostream>

BoundingSphere::BoundingSphere(const glm::vec3& centre, float radius)
    : centre(centre), radius(radius) {}

BoundingSphere::BoundingSphere(const BoundingSphere& one, const BoundingSphere& two)
{
    glm::vec3 centreOffset = two.centre - one.centre;
    float distanceSquared = glm::dot(centreOffset, centreOffset);
    float radiusDiff = two.radius - one.radius;

    // Check if the larger sphere encloses the small one
    if (radiusDiff * radiusDiff >= distanceSquared)
    {
        if (one.radius > two.radius)
        {
            centre = one.centre;
            radius = one.radius;
        }
        else
        {
            centre = two.centre;
            radius = two.radius;
        }
    }
    // Otherwise we need to work with partially overlapping spheres
    else
    {
        float distance = glm::sqrt(distanceSquared);
        radius = (distance + one.radius + two.radius) * 0.5f;

        // The new centre is based on one's centre, moved towards
        // two's centre by an amount proportional to the spheres' radii.
        centre = one.centre;
        if (distance > 0.0f)
        {
            centre += centreOffset * ((radius - one.radius) / distance);
        }
    }
}

bool BoundingSphere::overlaps(const BoundingSphere* other) const
{
    float dx = centre.x - other->centre.x;
    float dy = centre.y - other->centre.y;
    float dz = centre.z - other->centre.z; // Add z-component
    float distanceSquared = dx * dx + dy * dy + dz * dz; // Update distance calculation
    float radiusSum = radius + other->radius;
    bool result = distanceSquared < radiusSum * radiusSum;
    //std::cout << "overlaps: (" << centre.x << "," << centre.y << "," << centre.z << ") r=" << radius
    //          << " vs (" << other->centre.x << "," << other->centre.y << "," << other->centre.z << ") r=" << other->radius
    //          << " => " << result << std::endl;
    return result;
}

float BoundingSphere::getGrowth(const BoundingSphere& other) const
{
    BoundingSphere newSphere(*this, other);

    // We return a value proportional to the change in surface
    // area of the sphere.
    return newSphere.radius * newSphere.radius - radius * radius;
}