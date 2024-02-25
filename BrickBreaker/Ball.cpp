#include "Ball.h"
#include "Game.h"
#include "TextureManager.h"

Ball::Ball()
{
}

bool Ball::ballSpeed()
{
    ballYPos += ballYSpeed;
    ballXPos += ballXSpeed;
    return false;
}

void Ball::drawBall(SDL_Renderer* renderer)
{
    SDL_Rect ballRect = { (int)ballXPos, (int)ballYPos, ballWidth, ballHeight };
    TextureManager::Instance()->drawTexture("ball", ballRect.x, ballRect.y, ballRect.w, ballRect.h, renderer);
}

bool Ball::checkCollision(double x, double y, int w, int h)
{
	if (ballYPos + ballHeight > y && ballXPos + ballWidth > x && ballXPos < x + w && ballYPos < y + h) 
    {
        ballYSpeed = -ballYSpeed;
		return true;
    }
    if (ballYPos > 340) {
            lives--; //take 1 life
            SDL_Delay(100);
            cout << "-1 life\n";
            ballXPos = x + 60; //reset ball position to bounce from the middle of paddle
            ballYPos = y - 20;
        }
	return false;
}

bool Ball::collisionWalls()
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

double Ball::getBallXPos() const {
    return ballXPos;
}

void Ball::setBallXPos(double ballXPos) {
    Ball::ballXPos = ballXPos;
}

double Ball::getBallYPos() const {
    return ballYPos;
}

void Ball::setBallYPos(double ballYPos) {
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

double Ball::getBallXSpeed() const {
    return ballXSpeed;
}

void Ball::setBallXSpeed(double ballXSpeed) {
    Ball::ballXSpeed = ballXSpeed;
}

double Ball::getBallYSpeed() const {
    return ballYSpeed;
}

void Ball::setBallYSpeed(double ballYSpeed) {
    Ball::ballYSpeed = ballYSpeed;
}

void Ball::setLives(int lives)
{
    Ball::lives = lives;
}

int Ball::getLives()
{
    return lives;
}



