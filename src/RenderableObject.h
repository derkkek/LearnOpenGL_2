#pragma once
#include "Shader.h"
#include "iostream"

class RenderableObject
{
public:
	RenderableObject(const std::string& vertex_path, const std::string& fragment_path);
	~RenderableObject() = default;

	virtual void Draw(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos) = 0;

protected:
	Shader shader;

	unsigned int VAO, VBO, EBO;

	unsigned int textureID;
};

