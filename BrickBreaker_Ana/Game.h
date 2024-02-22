#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "Screen.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"

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
	bool ttf_init();
	void ballBouncing();

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;

	SDL_Texture* textTextureLives;
	SDL_Rect dRectLives;
	
	bool running;
	int currentFrame;

	bool startButton = false;	//is the start button clicked

	Ball ball;

	Paddle paddle;

	//Screen screen;
};
