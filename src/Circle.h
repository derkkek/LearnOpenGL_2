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
	Circle(float radius, int vCount, glm::vec3 position, const std::string &texture_path = "resource/textures/awesomeface.png");
	~Circle() = default;

	const int GetVertexCount() const override;
	
	const glm::mat4 GetModel() override;
	
	//float CalcMomentOfInertia() override;
	//float CalcTorque() override;
	//float CalcAngularAcc() override;


private:
	int vCount;	
	float momentOfInertia;

	void BuildCircle();

	void UpdateModel();
};
