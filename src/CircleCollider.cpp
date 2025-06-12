#include "CircleCollider.h"

CircleCollider::CircleCollider(glm::vec3 pos, float radius)
    :position(pos), radius(radius)
{
}

bool CircleCollider::CheckCollision(CircleCollider& circle_collider)
{
    return glm::distance(this->position, circle_collider.position) <= (this->radius + circle_collider.radius);
}
