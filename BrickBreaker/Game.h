#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL_mixer.h"

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

	Mix_Chunk* startButtonSound;
	Mix_Chunk* wallsSound;
	Mix_Chunk* winSound;
	Mix_Chunk* gameOverSound;
	Mix_Music* backgroundMusic = nullptr;

	//lives:
	SDL_Texture* textTextureFont1;
	SDL_Rect dRectFont1;
	//points:
	SDL_Texture* textTextureFont2;
	SDL_Rect dRectFont2;
	//game over:
	SDL_Texture* textTextureFont3;
	SDL_Rect dRectFont3;
	//win:
	SDL_Texture* textTextureFont4;
	SDL_Rect dRectFont4;

	bool running;

	bool startButton = false; //is the start button clicked

	bool stopMoving = true;	//if paddle is next to wall

	//objects
	Ball ball;
	Paddle paddle;

	int lives;
	int points;

};
