#include "Renderer.h"
#include "MeshData.h"
void Renderer::SetupMeshes()
{
	ResourceManager::LoadShader("resource/shaders/6.1.cubemaps.v", "resource/shaders/6.1.cubemaps.f", nullptr, "textured_cubes");
	ResourceManager::LoadShader("resource/shaders/6.1.skybox.v", "resource/shaders/6.1.skybox.f", nullptr, "skybox");

	ShaderStable cubeShader = ResourceManager::GetShader("textured_cubes");
	
	shader = cubeShader;
	for (RenderableObject* obj : sceneObjects)
	{
		obj->SetupBuffer();
	}
	cubeShader.SetInteger("texture1", 0);
	glActiveTexture(GL_TEXTURE0);
}

void Renderer::UpdateInstanceMatrices()
{
    for (size_t i = 0; i < sceneObjects.size(); i++)
    {
        modelMatrices[i] = sceneObjects[i]->GetModel();
    }
}

void Renderer::UpdateInstanceBuffer()
{
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sceneObjects.size() * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
}

/*Renders Cube not variety of objects!!!*/
void Renderer::RenderCube(RenderableObject* object, Camera& camera)
{
	ShaderStable cubeShader = ResourceManager::GetShader("textured_cubes");
	
	object->GetModel();

	glm::mat4 model = object->GetModel();

	cubeShader.SetMatrix4("model", model);

	glBindTexture(GL_TEXTURE_2D, object->GetTexId());
    glBindVertexArray(object->GetVao());
    glDrawArrays(GL_TRIANGLES, 0, object->GetVertexCount());
    glBindVertexArray(0);
}

void Renderer::RenderCircle(RenderableObject* object, Camera& camera)
{
	glBindVertexArray(object->GetVao());


	ShaderStable circleShader = ResourceManager::GetShader("textured_cubes");

	object->GetModel();

	glm::mat4 model = object->GetModel();

	circleShader.SetMatrix4("model", model);
	glBindTexture(GL_TEXTURE_2D, object->GetTexId());

	MeshData meshdata = object->SendMeshData();
	
	//circleShader.SetVector3f("color", meshdata.color);

	glDrawElementsInstanced(GL_TRIANGLES, meshdata.indices.size(), GL_UNSIGNED_INT, 0, 1000);

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

void Renderer::SetupInstancing(RenderableObject* instance)
{
    modelMatrices = new glm::mat4[sceneObjects.size()];
    glGenBuffers(1, &instanceVBO);

    if (sceneObjects.empty())
        return;

	instanceObject = instance; //sceneObjects[0];
	glBindVertexArray(instanceObject->GetVao());// since we need only one VAO bind it and keep the state.
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);

    std::size_t vec4Size = sizeof(glm::vec4);
    for (unsigned int i = 0; i < 4; i++) {
        glEnableVertexAttribArray(3 + i);
        glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * vec4Size));
        glVertexAttribDivisor(3 + i, 1);
    }

	// Use the first object as the "template" for VAO, texture, mesh, etc.
	//instanceObject = sceneObjects[0];
	instanceMesh = instanceObject->SendMeshData();
	//glBindVertexArray(instanceObject->GetVao()); 
	shader.Use();
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0); 
}

void Renderer::RenderScene(Camera& camera)
{
    ForwardCubeCommonConfig(camera);
	UpdateInstanceBuffer();
	//glBindVertexArray(instanceObject->GetVao());
    glDrawElementsInstanced(GL_TRIANGLES, instanceMesh.indices.size(), GL_UNSIGNED_INT, 0, sceneObjects.size());

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
	//ShaderStable cubeShader = ResourceManager::GetShader("textured_cubes");
	//shader.Use();
	shader.SetMatrix4("view", camera.GetViewMatrix());
	shader.SetMatrix4("projection", camera.GetProjectionMatrix());
	shader.SetVector3f("viewPos", camera.Position);
}

Renderer::Renderer()
{
	SetupMeshes();
}

Renderer::~Renderer()
{
	for (RenderableObject* obj : sceneObjects) // currently we assume all renderable objects belong to renderer so this is error prone. Use smart pointers isntead
	{
		delete obj;
		obj = nullptr;
	}
}



