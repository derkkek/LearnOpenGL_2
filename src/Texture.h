
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "stb_image.h"
#include <iostream>

#pragma once
class Texture
{
public:
	Texture(const char* texturePath, GLenum target, GLint mipMapLevel, GLint internalFormat, GLenum format);
	void Bind();
	void ActivateTexture(GLenum textureUnit);
	void Unbind();
	~Texture();
	unsigned int ID;

private:

};


