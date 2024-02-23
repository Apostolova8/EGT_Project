#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Ball.h"
#include "Paddle.h"

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

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	bool running;
	int currentFrame;

	bool startButton = false; //is the start button clicked

	bool stopMoving = true;

	//background:
	int backgroundXPos = 0; //x-position of background (left edge)
	int backgroundYPos = 0; //y-position of background (top edge)
	int backgroundWidth = 600; //background width
	int backgroundHeight = 400; //background height

	//left wall:
	int leftWallXPos = 0; //x-position of left wall (left edge)
	int leftWallYPos = 0; //y-position of left wall (top edge)
	int leftWallWidth = 25; //left wall width
	int leftWallHeight = 400; //left wall height

	//right wall:
	int rightWallXPos = 575; //x-position of left wall (left edge)
	int rightWallYPos = 1; //y-position of left wall (top edge)
	int rightWallWidth = 25; //left wall width
	int rightWallHeight = 400; //left wall height
	
	Ball ball;

	Paddle paddle;

	int lives = 2;
};
