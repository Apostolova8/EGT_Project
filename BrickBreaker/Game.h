#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "SDL_ttf.h"
#include "SDL.h"

enum GameState {  //game set
	START,
	PLAY,
	GAME_OVER
};

class Game
{
public:
	Game();
	~Game();
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool isRunning();
	void movePaddle(int x, int y);
	bool ttf_init();

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;

	//lives:
	SDL_Texture* textTextureFont1;
	SDL_Rect dRectFont1;
	//points:
	SDL_Texture* textTextureFont2;
	SDL_Rect dRectFont2;
	//game over:
	//SDL_Texture* textTextureFont3;
	//SDL_Rect dRectFont3;

	bool running;

	bool startButton = false; //is the start button clicked

	bool stopMoving = true;

	//objects
	Ball ball;
	Paddle paddle;
	GameState gameState;

	int lives;
	int points;

};
