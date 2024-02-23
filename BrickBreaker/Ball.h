#pragma once
#include "SDL.h"
#include "SDL_image.h"

class Ball
{
public:
	Ball();

	bool checkCollision( int x, int y, int w, int h);

    bool collissionWalls();

    bool ballSpeed();

    int getBallXPos() const;

    void setBallXPos(int ballXPos);

    int getBallYPos() const;

    void setBallYPos(int ballYPos);

    int getBallWidth() const;

    void setBallWidth(int ballWidth);

    int getBallHeight() const;

    void setBallHeight(int ballHeight);

    int getBallXSpeed() const;

    void setBallXSpeed(int ballXSpeed);

    int getBallYSpeed() const;

    void setBallYSpeed(int ballYSpeed);

private:
	int ballXPos = 275; //x-position of ball (left edge)
	int ballYPos = 330; //y-position of ball (top edge)
	int ballWidth = 20; //ball width
	int ballHeight = 20; //ball height
	int ballXSpeed = 0; //velocity of the ball
	int ballYSpeed = 0;
};

