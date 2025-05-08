#pragma once
#include "Shader.h"
#include "iostream"
#include "glm/glm.hpp"

class RenderableObject
{
public:
	RenderableObject();
	virtual ~RenderableObject() = default; // it's virtual because of to trigger derived objects' destructors.

	virtual void Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos) = 0;
	virtual const int GetVertexCount() const = 0;

	unsigned int GetVao();
	unsigned int GetTexId();
	glm::mat4 GetModel();
protected:

	unsigned int VAO, VBO, EBO;

	glm::mat4 model = glm::mat4(1.0f);

	unsigned int textureID;
};

