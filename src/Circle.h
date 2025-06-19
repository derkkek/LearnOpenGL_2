#pragma once
#include "Rigidbody.h"
#include <vector>
#include "RenderableObject.h"
#include "TextureLoader.h"
#include "MeshData.h"
#include "CircleCollider.h"
class Circle : public Rigidbody, public RenderableObject
{
public:
	Circle(float radius, int vCount, glm::vec3 position, UniformGrid* grid,const std::string &texture_path = "resource/textures/awesomeface.png");
	~Circle() = default;

	const int GetVertexCount() const override;
	
	const glm::mat4 GetModel() override;
	
	glm::vec3 color;
	//float CalcMomentOfInertia() override;
	//float CalcTorque() override;
	//float CalcAngularAcc() override;


private:
	int vCount;	
	float momentOfInertia;

	void BuildCircle();

	void UpdateModel();
};
