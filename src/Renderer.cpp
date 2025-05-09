#include "Renderer.h"
void Renderer::Init(Camera& camera)
{
	ResourceManager::LoadShader("resource/shaders/6.1.cubemaps.v", "resource/shaders/6.1.cubemaps.f", nullptr, "textured_cubes");
	ResourceManager::LoadShader("resource/shaders/6.1.skybox.v", "resource/shaders/6.1.skybox.f", nullptr, "skybox");

	ShaderStable cubeShader = ResourceManager::GetShader("textured_cubes");
	cubeShader.Use();
	cubeShader.SetMatrix4("view", camera.GetViewMatrix());
	cubeShader.SetMatrix4("projection", camera.GetProjectionMatrix());
	cubeShader.SetVector3f("viewPos", camera.Position);
	cubeShader.SetInteger("texture1", 0);
	glActiveTexture(GL_TEXTURE0);
}

/*Renders Cube not variety of objects!!!*/
void Renderer::RenderObject(RenderableObject* object, Camera& camera)
{
	ShaderStable cubeShader = ResourceManager::GetShader("textured_cubes");

	cubeShader.SetMatrix4("model", object->GetModel());

	glBindTexture(GL_TEXTURE_2D, object->GetTexId());
    glBindVertexArray(object->GetVao());
    glDrawArrays(GL_TRIANGLES, 0, object->GetVertexCount());
    glBindVertexArray(0);
}

void Renderer::RenderSkybox(RenderableObject* skybox, Camera& camera)
{
	ShaderStable skyboxShader = ResourceManager::GetShader("skybox");
	skyboxShader.Use();
	skyboxShader.SetInteger("skybox", 0);

	//// draw skybox as last
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	glm::mat4 manipulatedView = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
	skyboxShader.SetMatrix4("view", manipulatedView);
	skyboxShader.SetMatrix4("projection", camera.GetProjectionMatrix());
	//// skybox cube
	glBindVertexArray(skybox->GetVao());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->GetTexId());
	glDrawArrays(GL_TRIANGLES, 0, skybox->GetVertexCount());
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}

void Renderer::RenderScene(Camera& camera)
{
	ForwardCubeCommonConfig(camera);

	for (RenderableObject* obj : sceneObjects)
	{
		RenderObject(obj, camera);
	}

	RenderSkybox(skybox, camera);
}

void Renderer::AddScene(RenderableObject* object)
{
	this->sceneObjects.push_back(object);
}

void Renderer::AddSkybox(RenderableObject* skybox)
{
	this->skybox = skybox;
}

void Renderer::ForwardCubeCommonConfig(Camera& camera)
{
	ShaderStable cubeShader = ResourceManager::GetShader("textured_cubes");
	cubeShader.Use();
	cubeShader.SetMatrix4("view", camera.GetViewMatrix());
	cubeShader.SetMatrix4("projection", camera.GetProjectionMatrix());
	cubeShader.SetVector3f("viewPos", camera.Position);
}

Renderer::~Renderer()
{
	for (RenderableObject* obj : sceneObjects) // currently we assume all renderable objects belong to renderer so this is error prone. Use smart pointers isntead
	{
		delete obj;
		obj = nullptr;
	}
}



