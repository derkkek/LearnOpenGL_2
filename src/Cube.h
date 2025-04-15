#pragma once
#include "IRenderable.h"
#include "glad/glad.h"
#include "TextureLoader.h"

class Cube :public IRenderable
{
public:
	Cube();
	~Cube() = default;

	virtual void Draw() const;
	
	virtual const glm::mat4 getModelMatrix() const;


private:
    static const float vertices[180];
	unsigned int VAO, VBO;
	unsigned int texture;
	glm::mat4 model = glm::mat4(1.0f);

	void SetupBuffer();
	void AssignTexture(const std::string& path = "resource/textures/container.jpg");
	void BindTexture() const;

};

