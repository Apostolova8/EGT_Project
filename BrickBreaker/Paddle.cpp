#include "Paddle.h"
#include "SDL.h"
#include "TextureManager.h"

Paddle::Paddle()
{
}

void Paddle::drawPaddle(SDL_Renderer* renderer)
{
    SDL_Rect paddleRect = { (int)paddleXPos, (int)paddleYPos, paddleWidth, paddleHeight };
    TextureManager::Instance()->drawTexture("paddle", paddleRect.x, paddleRect.y, paddleRect.w, paddleRect.h, renderer);
}

int Paddle::getPaddleXPos() const {
    return paddleXPos;
}

void Paddle::setPaddleXPos(int paddleXPos) {
    Paddle::paddleXPos = paddleXPos;
}

int Paddle::getPaddleYPos() const {
    return paddleYPos;
}

void Paddle::setPaddleYPos(int paddleYPos) {
    Paddle::paddleYPos = paddleYPos;
}

int Paddle::getPaddleWidth() const {
    return paddleWidth;
}

void Paddle::setPaddleWidth(int paddleWidth) {
    Paddle::paddleWidth = paddleWidth;
}

int Paddle::getPaddleHeight() const {
    return paddleHeight;
}

void Paddle::setPaddleHeight(int paddleHeight) {
    Paddle::paddleHeight = paddleHeight;
}
