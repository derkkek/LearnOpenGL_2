#include "RenderableObject.h"
#include "ResourceManager.h"
#include "TextureLoader.h"

class Square : public RenderableObject
{
public:
	Square();
	~Square() = default;
    const int GetVertexCount() const override;

private:
    void SetupBuffer();
    void AssignTexture(const std::string& path = "resource/textures/block.png");


    float vertices[4 * 6] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
};
