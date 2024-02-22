#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>

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

	bool startButton = false; //is the start button clicked

	bool stopMoving = true;	//stop moving paddle next to the wall

	int ballXPos = 275; //x-position of ball (left edge)
	int ballYPos = 330; //y-position of ball (top edge)
	int ballWidth = 20; //ball width
	int ballHeight = 20; //ball height
	int ballXSpeed = 1; //velocity of the ball
	int ballYSpeed = -1;

	int paddleXPos = 225; //x-position of paddle (left edge)
	int paddleYPos = 340; //y-position of paddle (top edge)
	int paddleWidth = 120;	//width
	int paddleHeight = 30;	//height

	int backgroundXPos = 0; //x-position of background (left edge)
	int backgroundYPos = 0; //y-position of background (top edge)
	int backgroundWidth = 600; //background width
	int backgroundHeight = 400; //background height

	int leftWallXPos = 0; //x-position of left wall (left edge)
	int leftWallYPos = 0; //y-position of left wall (top edge)
	int leftWallWidth = 25; //left wall width
	int leftWallHeight = 400; //left wall height

	int rightWallXPos = 575; //x-position of left wall (left edge)
	int rightWallYPos = 1; //y-position of left wall (top edge)
	int rightWallWidth = 25; //left wall width
	int rightWallHeight = 400; //left wall height

	std::vector<SDL_Rect> brickPos; //hold bricks positions
	bool brickV[10]; //which brick is visible
	int brickHeight = 50;
	int brickWidth = 50; 

	int lives = 2;
};