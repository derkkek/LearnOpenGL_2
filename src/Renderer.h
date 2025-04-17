#ifndef RENDERER_H
#define RENDERER_H

#include "IRenderable.h"
#include "Shader.h"
#include <vector>

class Renderer {
public:
    // Render a single object using the provided shader.
    void renderObject(IRenderable* object, Camera& camera, float SCR_WIDTH, float SCR_HEIGHT) {
        // Bind the shader (if necessary) and set uniforms.

        // Then let the object handle its own draw calls.
        object->Draw();

    }

    // Optionally, render a list of objects.
    void renderScene(std::vector<IRenderable*>& sceneObjects, Camera& camera, float SCR_WIDTH, float SCR_HEIGHT) {
        for (IRenderable* obj : sceneObjects) {
            renderObject(obj, camera, SCR_WIDTH, SCR_HEIGHT);
        }
    }
};

#endif // RENDERER_H
