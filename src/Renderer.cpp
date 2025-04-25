#include "Renderer.h"


void Renderer::RenderObject(RenderableObject* object, Camera& camera)
{
	object->Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix(), camera.Position);
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

