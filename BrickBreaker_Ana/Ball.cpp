#include "Ball.h"
#include <iostream>
using namespace std;
#include "Game.h"
#include "Paddle.h"
#include "TextureManager.h"

Ball::Ball(SDL_Renderer* renderer)
{

}

Ball::Ball()
{
	std::cout << "ball ok" << endl;
}

void Ball::ballSpeed()
{
    double xSpeedV = 0.08; //decrease velocity of ball
    double ySpeedV = 0.08;

    ballXPos += ballXSpeed * xSpeedV; //update x-position along with x-speed
    ballYPos += ballYSpeed * ySpeedV;; //update y-position along with y-speed
}

void Ball::ballBouncing()
{
        ballSpeed();

        if (ballXPos < 25 || ballXPos + ballWidth >= 575) { //if the ball hits left or right edge of window
            ballXSpeed = -ballXSpeed; //reverse direction horizontally
        }
       
        if (ballYPos < 0 || ballYPos + ballHeight >= 350) { //if the ball hits top of the window or bottom edge of the paddle) 
            ballYSpeed = -ballYSpeed; //reverse direction vertically
        }
}

void Ball::ballTouchPaddle()
{
    ballSpeed();
                     //   x    y    w    h       
    SDL_Rect paddleR = { 225, 300, 120, 30 }; //x, y coordinates and size of the paddle
    
    //check if the ball bottom edge is touching top/right/left edge of the paddle
    if (ballYPos + ballHeight >= paddleR.y && ballYPos < paddleR.y + paddleR.h &&
        ballXPos + ballWidth >= paddleR.x && ballXPos <= paddleR.x + paddleR.w) {        
        ballYSpeed = -ballYSpeed;
        ballYPos = paddleR.y - ballHeight; //adjust ball position
    }
}

void Ball::checkCollision()
{   

}

void Ball::ballUpdate() //all ball functions in one
{
    ballBouncing();
    ballTouchPaddle();
    //checkCollision();
}

void Ball::setBallXPos(double ballXPos)
{
    this->ballXPos = ballXPos;
}

double Ball::getBallXPos()
{
    return ballXPos;
}

void Ball::setBallYPos(double ballYPos)
{
    this->ballYPos = ballYPos;
}

double Ball::getBallYPos()
{
    return ballYPos;
}

const int Ball::getBallWidth() const
{
    return ballWidth;
}

const int Ball::getBallHeight() const
{
    return ballHeight;
}

void Ball::setBallXSpeed(double ballXSpeed)
{
    this->ballXSpeed = ballXSpeed;
}

double Ball::getBallXSpeed()
{
    return ballXSpeed;
}

void Ball::setBallYSpeed(double ballYSpeed)
{
    this->ballYSpeed = ballYSpeed;
}

double Ball::getBallYSpeed()
{
    return ballYSpeed;
}
