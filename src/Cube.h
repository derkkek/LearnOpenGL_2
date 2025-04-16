#pragma once
#include "IRenderable.h"
#include "glad/glad.h"
#include "TextureLoader.h"
#include "Shader.h"

class Cube :public IRenderable
{
public:
	Cube(std::string& vertex_source, std::string& fragment_source);
	~Cube() = default;

	virtual void Draw();
	
	virtual const glm::mat4 getModelMatrix() const;


private:
    static const float vertices[180];
	unsigned int VAO, VBO;
	unsigned int textureID;

	Shader shader;
	unsigned int shaderID;
	glm::mat4 model = glm::mat4(1.0f);

	void SetupBuffer();
	void AssignTexture(const std::string& path = "resource/textures/container.jpg");

};

