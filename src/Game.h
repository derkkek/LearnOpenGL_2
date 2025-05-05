#pragma once
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "game_level.h"
#include "5.1.ball_object_collisions.h"
#include <GLFW/glfw3.h>

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(100.0f, 20.0f);
// Initial velocity of the player paddle
const float PLAYER_VELOCITY(500.0f);
class Game
{

public:

	Game(unsigned int witdh, unsigned int height);
	~Game();
	GameState gameState;

	bool Keys[1024];
	unsigned int Width, Height;
	std::vector<GameLevel>  Levels;
	unsigned int            Level;
	// initialize game state (load all shaders/textures
	void Init();

	/*Game Loop*/

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
	bool CheckCollision(GameObject& one, GameObject& two);
	void DoCollisions();


private:
};
