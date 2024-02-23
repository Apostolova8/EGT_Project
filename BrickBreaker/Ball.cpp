#include "Ball.h"
#include "Game.h"

Ball::Ball()
{
}

bool Ball::checkCollision(int x, int y, int w, int h)
{
	if (ballYPos + ballHeight > y && ballXPos + ballWidth > x && ballXPos < x + w && ballYPos < y + h) 
    {
        ballYSpeed = -ballYSpeed;
		return true;
	}

	return false;
}

bool Ball::collissionWalls()
{
    if (ballXPos < 25 || ballXPos + ballWidth >= 575) { //if the ball hits left or right edge of walls
        ballXSpeed = -ballXSpeed; //reverse direction horizontally
    }
    //cout << "ball hits left/right wall" << endl;
    if (ballYPos < 0 || ballYPos + ballHeight >= 400) { //if the ball hits top of the window 
        ballYSpeed = -ballYSpeed; //reverse direction vertically
    }
    //cout << "ball hits top of the screen" << endl;
    return false;
}

bool Ball::ballSpeed()
{
    ballXPos += ballXSpeed;
    ballYPos += ballYSpeed;
    return false;
}

int Ball::getBallXPos() const {
    return ballXPos;
}

void Ball::setBallXPos(int ballXPos) {
    Ball::ballXPos = ballXPos;
}

int Ball::getBallYPos() const {
    return ballYPos;
}

void Ball::setBallYPos(int ballYPos) {
    Ball::ballYPos = ballYPos;
}

int Ball::getBallWidth() const {
    return ballWidth;
}

void Ball::setBallWidth(int ballWidth) {
    Ball::ballWidth = ballWidth;
}

int Ball::getBallHeight() const {
    return ballHeight;
}

void Ball::setBallHeight(int ballHeight) {
    Ball::ballHeight = ballHeight;
}

int Ball::getBallXSpeed() const {
    return ballXSpeed;
}

void Ball::setBallXSpeed(int ballXSpeed) {
    Ball::ballXSpeed = ballXSpeed;
}

int Ball::getBallYSpeed() const {
    return ballYSpeed;
}

void Ball::setBallYSpeed(int ballYSpeed) {
    Ball::ballYSpeed = ballYSpeed;
}
