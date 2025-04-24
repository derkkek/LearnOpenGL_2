#pragma once
#include "Shader.h"
#include "Renderer.h"
#include "iostream"

class RenderableObject
{
public:
	RenderableObject(Renderer& renderer, const std::string& vertex_path, const std::string& fragment_path);
	virtual ~RenderableObject() = default; // it's virtual because of to trigger derived objects' destructors.

	virtual void Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos) = 0;

protected:
	Shader shader;

	unsigned int VAO, VBO, EBO;

	unsigned int textureID;
};

