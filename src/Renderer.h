#ifndef RENDERER_H
#define RENDERER_H

#include "IRenderable.h"
#include "Shader.h"
#include <vector>

class Renderer {
public:
    // Render a single object using the provided shader.
    void renderObject(const IRenderable* object, Shader& shader, Camera& camera, float SCR_WIDTH, float SCR_HEIGHT) {
        // Bind the shader (if necessary) and set uniforms.

        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("view", view);
        shader.setMat4("model", object->getModelMatrix());

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), SCR_WIDTH / SCR_HEIGHT, 0.1f, 500.0f);
        shader.setMat4("projection", projection);
        shader.setVec3("Color", object->getObjectColor());
        shader.setVec3("viewPos", camera.Position);

        // For example, set the "model" matrix uniform:
        shader.setMat4("model", object->getModelMatrix());
        // Then let the object handle its own draw calls.
        object->Draw();
    }

    // Optionally, render a list of objects.
    void renderScene(const std::vector<IRenderable*>& sceneObjects, Shader& shader, Camera& camera, float SCR_WIDTH, float SCR_HEIGHT) {
        for (const IRenderable* obj : sceneObjects) {
            renderObject(obj, shader, camera, SCR_WIDTH, SCR_HEIGHT);
        }
    }
};

#endif // RENDERER_H
