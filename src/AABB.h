#pragma once  
#include "Collider.h"  

class AABB  
{  
public:  
    AABB(Collider* collider) : collider(collider) {}  

    Collider* getCollider() const  
    {  
        return collider;  
    }
    bool Collides(AABB* aabb);

private:
	float minX, minY, maxX, maxY;
    Collider* collider;  
};