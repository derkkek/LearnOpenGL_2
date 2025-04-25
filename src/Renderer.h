#pragma once
#include "Camera.h"
#include "Shader.h"
#include "RenderableObject.h"
#include <vector>


class Renderer 
{
public:
    std::vector<RenderableObject*> sceneObjects;

    Renderer() = default;
    ~Renderer();

    // Render a single object using the provided shader.
    void RenderObject(RenderableObject* object, Camera& camera);

    // Optionally, render a list of objects.
    void RenderScene(Camera& camera);
    void AddScene(RenderableObject* object);
private:

};


