#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "SDL_ttf.h"
#include "SDL.h"

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
	TTF_Font* font;

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

	//lives:
	int livesXPos = 490; //x-position of heart (left edge)
	int livesYPos = 8; //y-position of left heart (top edge)
	int livesWidth = 30; //left wall heart
	int livesHeight = 30; //left wall heart

	int lives; // Number of lives

	//objects
	Ball ball;
	Paddle paddle;

};