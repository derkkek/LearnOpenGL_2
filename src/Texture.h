
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "stb_image.h"
#include <iostream>

#pragma once
class Texture
{
public:
	Texture(const char* texturePath);
	void Bind();
	void Unbind();
	~Texture();
	unsigned int ID;

private:

};


