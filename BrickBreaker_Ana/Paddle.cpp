#include "Paddle.h"
#include <iostream>
#include "SDL_image.h"
#include "Game.h"
#include "TextureManager.h"

Paddle::Paddle(SDL_Renderer* renderer)
{

}

Paddle::Paddle()
{
	std::cout << "paddle ok" << std::endl;
}

void Paddle::movePaddle(int x, int y)
{
    paddleXPos += x;
    paddleYPos += y;
}

void Paddle::setPaddleXPos(int paddleXPos)
{
    this->paddleXPos = paddleXPos;
}

int Paddle::getPaddleXPos()
{
    return paddleXPos;
}

void Paddle::setPaddleYPos(int paddleYPos)
{
    Paddle::paddleYPos = paddleYPos;
}

int Paddle::getPaddleYPos() const
{
    return paddleYPos;
}

const int Paddle::getPaddleWidth() const
{
    return paddleWidth;
}

const int Paddle::getPaddleHeight() const
{
    return paddleHeight;
}