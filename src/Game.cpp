#include "Game.h"

SpriteRenderer* renderer;

Game::Game(unsigned int witdh, unsigned int height)
	:gameState(GAME_MENU), Keys(), Width(witdh), Height(height)
{
}

Game::~Game()
{
	delete renderer;
}

void Game::Init()
{
	ResourceManager::LoadShader("resource/shaders/sprite.v", "resource/shaders/sprite.f", nullptr, "sprite");
      
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // load textures
    ResourceManager::LoadTexture("resource/textures/awesomeface.png", true, "face");
}

void Game::Render()
{
    renderer->DrawSprite(ResourceManager::GetTexture("face") , glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
