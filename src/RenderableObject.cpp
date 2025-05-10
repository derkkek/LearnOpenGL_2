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

glm::mat4 RenderableObject::GetModel()
{
	std::cout << "MODEL IN RENDERABLE OBJECT: \n\n\n" << glm::to_string(model) << "\n\n\n";
	return this->model;
}
