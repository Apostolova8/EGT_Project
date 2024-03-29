#pragma once
#include "SDL.h"

class Paddle
{
public:
	Paddle();

	bool stopMovingPaddle = true;

	void drawPaddle(SDL_Renderer* renderer);

	int getPaddleXPos() const;

	void setPaddleXPos(int paddleXPos);

	int getPaddleYPos() const;

	void setPaddleYPos(int paddleYPos);

	int getPaddleWidth() const;

	void setPaddleWidth(int paddleWidth);

	int getPaddleHeight() const;

	void setPaddleHeight(int paddleHeight);

private:
	int paddleXPos = 225; //x-position of paddle (left edge)
	int paddleYPos = 340; //y-position of paddle (top edge)
	int paddleWidth = 120;	//width
	int paddleHeight = 20;	//height
};

