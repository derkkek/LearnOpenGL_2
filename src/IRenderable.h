#ifndef IRENDERABLE_H
#define IRENDERABLE_H

#include "glm/glm.hpp"

class IRenderable
{

public:

	virtual ~IRenderable() = default;

	virtual const glm::mat4 getModelMatrix() const = 0;
	
	virtual void Draw() = 0;

};



#endif // !IRENDERABLE_H

