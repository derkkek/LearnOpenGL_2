#ifndef RENDERER_H
#define RENDERER_H

#include "IRenderable.h"
#include "Shader.h"
#include <vector>

class Renderer {
public:
    // Render a single object using the provided shader.
    void renderObject(const IRenderable* object, Shader& shader) {
        // Bind the shader (if necessary) and set uniforms.
        // For example, set the "model" matrix uniform:
        shader.setMat4("model", object->getModelMatrix());
        // Then let the object handle its own draw calls.
        object->Draw();
    }

    // Optionally, render a list of objects.
    void renderScene(const std::vector<IRenderable*>& sceneObjects, Shader& shader) {
        for (const IRenderable* obj : sceneObjects) {
            renderObject(obj, shader);
        }
    }
};

#endif // RENDERER_H
