#include "RenderableObject.h"
#include "ResourceManager.h"
#include "TextureLoader.h"
#include "Rigidbody.h"


class Square : public RenderableObject
{
public:
	Square(glm::vec3 position = glm::vec3(0.0f, 5.0f, 0.0f));
	~Square() = default;
    const int GetVertexCount() const override;
    const glm::mat4 GetModel() override;

    Rigidbody* rigidbody;
    void UpdateModel();

private:
    void SetupBuffer();
    void AssignTexture(const std::string& path = "resource/textures/block.png");

    float vertices[4 * 6] = {
        // pos (centered)      // tex
        -0.5f,  0.5f,         0.0f, 1.0f,   // Top-left
         0.5f, -0.5f,         1.0f, 0.0f,   // Bottom-right
        -0.5f, -0.5f,         0.0f, 0.0f,   // Bottom-left

        -0.5f,  0.5f,         0.0f, 1.0f,   // Top-left
         0.5f,  0.5f,         1.0f, 1.0f,   // Top-right
         0.5f, -0.5f,         1.0f, 0.0f    // Bottom-right
    };
};
