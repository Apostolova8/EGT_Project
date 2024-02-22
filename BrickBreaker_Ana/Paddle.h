#pragma once
#include "SDL.h"

class Paddle 
{
public:
	Paddle(SDL_Renderer* renderer);

	Paddle();

	void movePaddle(int x, int y);

	bool stopMovingPaddle = true; //paddle has to stop moving when it gets to the walls

	void setPaddleXPos(int);
	int getPaddleXPos();

	void setPaddleYPos(int);
	int getPaddleYPos() const;

	const int getPaddleWidth() const;

	const int getPaddleHeight() const;

private:
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	
	int paddleXPos = 225; //x-position of paddle (left edge)
	int paddleYPos = 300; //y-position of paddle (top edge)
	const int paddleWidth = 120;	//width
	const int paddleHeight = 30;	//height
};

