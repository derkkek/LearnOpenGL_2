#pragma once
#include "IRenderable.h"
#include "glad/glad.h"
#include "TextureLoader.h"
#include "Shader.h"

class Cube :public IRenderable
{
public:
	Cube(const std::string& vertex_source, const std::string& fragment_source);
	~Cube() = default;

	virtual void Draw() override;
	
	virtual const glm::mat4 getModelMatrix() const;
	Shader shader;


private:
    static const float vertices[180];
	unsigned int VAO, VBO;
	unsigned int textureID;

	unsigned int shaderID;
	glm::mat4 model = glm::mat4(1.0f);

	void SetupBuffer();
	void AssignTexture(const std::string& path = "resource/textures/container.jpg");

};

