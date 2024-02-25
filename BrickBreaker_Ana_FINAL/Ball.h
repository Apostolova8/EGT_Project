#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Screen.h"

class Ball
{
public:
	Ball();

	bool checkCollision(double x, double y, int w, int h);

    bool collisionWalls();

    bool ballSpeed();

    void drawBall(SDL_Renderer* renderer);

    double getBallXPos() const;

    void setBallXPos(double ballXPos);

    double getBallYPos() const;

    void setBallYPos(double ballYPos);

    int getBallWidth() const;

    void setBallWidth(int ballWidth);

    int getBallHeight() const;

    void setBallHeight(int ballHeight);

    double getBallXSpeed() const;

    void setBallXSpeed(double ballXSpeed);

    double getBallYSpeed() const;

    void setBallYSpeed(double ballYSpeed);

    void setLives(int lives);

    int getLives();

private:
	double ballXPos = 275; //x-position of ball (left edge)
	double ballYPos = 320; //y-position of ball (top edge)
	int ballWidth = 20; //ball width
	int ballHeight = 20; //ball height
    double ballXSpeed = 0; //velocity of the ball horizontally
	double ballYSpeed = 0; //velocity of the ball vertically

    int lives = 2;

    Screen walls;
};

