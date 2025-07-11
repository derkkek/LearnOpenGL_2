#pragma once
#include "ShaderStable.h"
#include "Texture.h"
class SpriteRenderer
{
public:
	SpriteRenderer(ShaderStable& shader);
	~SpriteRenderer() = default;

	void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
private:
	/* Render state */
	ShaderStable shader;
	unsigned int quadVAO;
	/* Initializes and configures the quad's buffer and vertex attributes */
	void InitRenderData();
};

