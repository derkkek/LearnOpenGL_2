#include "RenderableObject.h"

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

glm::mat4 RenderableObject::GetModel()
{
	return this->model;
}
