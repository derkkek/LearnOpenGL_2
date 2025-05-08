#include "Renderer.h"
void Renderer::Init(ShaderStable& shader, Camera& camera)
{
    this->shader = shader;//ResourceManager::LoadShader("resource/shaders/6.1.cubemaps.v", "resource/shaders/6.1.cubemaps.f", nullptr, "textured_cubes");
    this->shader.Use();

	shader.SetMatrix4("view", camera.GetViewMatrix());
	shader.SetMatrix4("projection", camera.GetProjectionMatrix());
	shader.SetVector3f("viewPos", camera.Position);
	shader.SetInteger("texture1", 0);
	glActiveTexture(GL_TEXTURE0);
}

void Renderer::RenderObject(RenderableObject* object, Camera& camera)
{
	//object->Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), camera.Position);

    shader.SetMatrix4("model", object->GetModel());
	glBindTexture(GL_TEXTURE_2D, object->GetTexId());

	shader.SetMatrix4("view", camera.GetViewMatrix());
	shader.SetMatrix4("projection", camera.GetProjectionMatrix());
	shader.SetVector3f("viewPos", camera.Position);

    glBindVertexArray(object->GetVao());
    glDrawArrays(GL_TRIANGLES, 0, object->GetVertexCount());
    glBindVertexArray(0);
}

void Renderer::RenderScene(Camera& camera)
{
	for (RenderableObject* obj : sceneObjects)
	{
		RenderObject(obj, camera);
	}
}

void Renderer::AddScene(RenderableObject* object)
{
	this->sceneObjects.push_back(object);
}

Renderer::~Renderer()
{
	for (RenderableObject* obj : sceneObjects) // currently we assume all renderable objects belong to renderer so this is error prone. Use smart pointers isntead
	{
		delete obj;
		obj = nullptr;
	}
}



