#pragma once
#include "Rigidbody.h"
#include <vector>
#include "RenderableObject.h"
#include "TextureLoader.h"
class Circle : public RenderableObject
{
public:
	Circle(float radius, int vCount, glm::vec3 position);
	const int GetVertexCount() const override;
	const glm::mat4 GetModel() override;
	~Circle() = default;
	Rigidbody* rigidbody;

private:


	struct Vertex {
		glm::vec3 position;
		glm::vec2 texCoord;
	};

	float radius;
	int vCount;
	int triangleCount;

	std::vector<Vertex> vertices;


	void BuildCircle();
	void SetupBuffer();
	void AssignTexture();

	void UpdateModel();
};
