#pragma once
#include "Shader.h"
#include "iostream"
#include "glm/glm.hpp"
#include <vector>
#include "MeshData.h"

class RenderableObject
{
public:
	RenderableObject(const std::string& texture_path);
	virtual ~RenderableObject() {} // it's virtual because of to trigger derived objects' destructors.

	virtual const int GetVertexCount() const = 0;
	virtual const glm::mat4 GetModel() = 0;
	unsigned int GetVao();
	unsigned int GetTexId();
	
	void SetupBuffer();
	void AssignTexture(const std::string &path);
	MeshData SendMeshData();

protected:

	unsigned int VAO, VBO, EBO;

	MeshData mesh;
	glm::mat4 model = glm::mat4(1.0f);

	unsigned int textureID;
};

