#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Paddle.h"

class Ball 
{
public:
	Ball(SDL_Renderer* renderer);

	Ball();

	void ballSpeed();

	void ballBouncing();

	void ballTouchPaddle();
	
	void checkCollision();

	void ballUpdate();

	void setBallXPos(double);
	double getBallXPos();

	void setBallYPos(double);
	double getBallYPos();

	const int getBallWidth() const;

	const int getBallHeight() const;

	void setBallXSpeed(double);
	double getBallXSpeed();

	void setBallYSpeed(double);
	double getBallYSpeed();

private:
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	
	//bool startBouncing = false; //ball starts to bounce after the user click on the screen
	double ballXPos = 275; //x-position of ball (left edge)
	double ballYPos = 330; //y-position of ball (top edge)
	const int ballWidth = 20; //ball width
	const int ballHeight = 20; //ball height
	double ballXSpeed = 1; //velocity of the ball by x-position
	double ballYSpeed = 1; //velocity of the ball by y-position
};

