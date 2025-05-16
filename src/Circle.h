#pragma once
#include "Rigidbody.h"
#include <vector>
#include "RenderableObject.h"
#include "TextureLoader.h"
#include "MeshData.h"
class Circle : public RenderableObject
{
public:
	Circle(float radius, int vCount, glm::vec3 position, const std::string &texture_path = "resource/textures/awesomeface.png");
	~Circle() = default;

	const int GetVertexCount() const override;
	
	const glm::mat4 GetModel() override;
	
	Rigidbody* rigidbody;

private:
	float radius;
	int vCount;	

	void BuildCircle();

	void UpdateModel();
};
