#pragma once
enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{

public:

	Game(unsigned int witdh, unsigned int height);
	~Game();
	GameState gameState;

	bool Keys[1024];
	unsigned int Width, Height;
	// initialize game state (load all shaders/textures
	void Init();

	/*Game Loop*/

	void ProcessInput(float dt);
	void Update(float dt);
	void Render();

private:
};
