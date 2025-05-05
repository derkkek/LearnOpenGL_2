#include "Game.h"

SpriteRenderer* renderer;
GameObject* player;

// Initial velocity of the Ball
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// Radius of the ball object
const float BALL_RADIUS = 12.5f;


BallObject* ball;
Game::Game(unsigned int witdh, unsigned int height)
	:gameState(GAME_ACTIVE), Keys(), Width(witdh), Height(height)
{
}

Game::~Game()
{
	delete renderer;
    delete player;
    delete ball;
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
    ResourceManager::LoadTexture("resource/textures/background.jpg", false, "background");
    ResourceManager::LoadTexture("resource/textures/awesomeface.png", true, "ball");
    ResourceManager::LoadTexture("resource/textures/block.png", false, "block");
    ResourceManager::LoadTexture("resource/textures/block_solid.png", false, "block_solid");
    ResourceManager::LoadTexture("resource/textures/paddle.png", true, "paddle");
    // load levels
    GameLevel one; one.Load("resource/levels/one.lvl", this->Width, this->Height / 2);
    GameLevel two; two.Load("resource/levels/two.lvl", this->Width, this->Height / 2);
    GameLevel three; three.Load("resource/levels/three.lvl", this->Width, this->Height / 2);
    GameLevel four; four.Load("resource/levels/four.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;
    // configure game objects
    glm::vec2 playerPos = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

    glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x / 2.0f -
        BALL_RADIUS, -BALL_RADIUS * 2.0f);
    ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
        ResourceManager::GetTexture("ball"));
}

void Game::ProcessInput(float dt)
{
    if (this->gameState == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        // move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (player->Position.x >= 0.0f)
            {
                player->Position.x -= velocity;
                if (ball->Stuck)
                    ball->Position.x -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (player->Position.x <= this->Width - player->Size.x)
            {
                player->Position.x += velocity;
                if (ball->Stuck)
                    ball->Position.x += velocity;
            }
        }
        if (this->Keys[GLFW_KEY_SPACE])
            ball->Stuck = false;
    }
}
void Game::Update(float dt)
{
    ball->Move(dt, Width);
    DoCollisions();
}

void Game::Render()
{
    if (this->gameState == GAME_ACTIVE)
    {
        // draw background
        renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
        // draw level
        this->Levels[this->Level].Draw(*renderer);
        // draw player
        player->Draw(*renderer);
        ball->Draw(*renderer);
    }
}

bool Game::CheckCollision(GameObject& one, GameObject& two)
{
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;

    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;

    return collisionX && collisionY;
}

bool Game::CheckCollision(BallObject& one, GameObject& two)
{
    // get center point circle first
    glm::vec2 center(one.Position + one.Radius);
    // calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x,
        two.Position.y + aabb_half_extents.y);
    // get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents,
        aabb_half_extents);
    // add clamped value to AABB_center and get the value closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // vector between center circle and closest point AABB
    difference = closest - center;
    return glm::length(difference) < one.Radius;
}

void Game::DoCollisions()
{
    for (GameObject& box : Levels[Level].Bricks)
    {
        if (!box.Destroyed)
        {
            if (CheckCollision(*ball, box))
            {
                if (!box.IsSolid)
                {
                    box.Destroyed = true;
                }
            }
        }
    }
}

