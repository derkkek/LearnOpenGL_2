#pragma once
#include "Shader.h"
#include "iostream"

class RenderableObject
{
public:
	RenderableObject(const std::string& vertex_path, const std::string& fragment_path);
	~RenderableObject() = default;

protected:
	Shader shader;

	unsigned int VAO, VBO, EBO;

	unsigned int textureID;
};

