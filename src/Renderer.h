#pragma once
#include "Camera.h"
#include "ShaderStable.h"
#include "Skybox.h"
#include "RenderableObject.h"
#include "ResourceManager.h"
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>


class Renderer 
{
public:
    std::vector<RenderableObject*> sceneObjects;
    RenderableObject* skybox;
    ShaderStable shader;

    unsigned int instanceVBO;
    glm::mat4* modelMatrices;
    RenderableObject* instanceObject;
    MeshData instanceMesh;

    Renderer();
    ~Renderer();
    void SetupMeshes();
    void UpdateInstanceMatrices();
    void UpdateInstanceBuffer();

    // Render a single object using the provided shader.
    void RenderCube(RenderableObject* object, Camera& camera);
    void RenderCircle(RenderableObject* object, Camera& camera);
    void RenderSkybox(RenderableObject* skybox, Camera& camera);

    void SetupInstancing();

    // Optionally, render a list of objects.
    void RenderScene(Camera& camera);
    void AddScene(RenderableObject* object);
    void AddSkybox(RenderableObject* skybox);
    void ForwardCubeCommonConfig(Camera& camera);
private:

};


