#include "RenderableObject.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

RenderableObject::RenderableObject()
{

}

unsigned int RenderableObject::GetVao()
{
	return this->VAO;
}

unsigned int RenderableObject::GetTexId()
{
	return this->textureID;
}
