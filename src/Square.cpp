#include "Square.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Square::Square(glm::vec3 position)
	:rigidbody(position)
{
	SetupBuffer();
	AssignTexture();
	this->model = glm::translate(this->model, this->rigidbody.position); // Assign the result
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

void Square::UpdateModel()
{
	this->model = glm::mat4(1.0f);
	this->model = glm::translate(this->model, this->rigidbody.position);
	
}
