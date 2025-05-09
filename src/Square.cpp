#include "Square.h"

Square::Square()
{
	SetupBuffer();
	AssignTexture();
}

const int Square::GetVertexCount() const
{
	return 3 * 2;
}

void Square::SetupBuffer()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this ->VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), this->vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(this->VAO);


}

void Square::AssignTexture(const std::string& path)
{
	this->textureID = TextureLoader::loadTexture(path.c_str());

}
