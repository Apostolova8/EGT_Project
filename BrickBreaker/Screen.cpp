#include "Screen.h"
#include "TextureManager.h"

Screen::Screen()
{
}

void Screen::drawAll(SDL_Renderer* renderer)
{
    SDL_Rect backgroundRect = { (int)backgroundXPos, (int)backgroundYPos, backgroundWidth, backgroundHeight };
    TextureManager::Instance()->drawTexture("background", backgroundRect.x, backgroundRect.y, backgroundRect.w, backgroundRect.h, renderer);

    SDL_Rect leftWallRect = { (int)leftWallXPos, (int)leftWallYPos, leftWallWidth, leftWallHeight };
    TextureManager::Instance()->drawTexture("wall", leftWallRect.x, leftWallRect.y, leftWallRect.w, leftWallRect.h, renderer);

    SDL_Rect rightWallRect = { (int)rightWallXPos, (int)rightWallYPos, rightWallWidth, rightWallHeight };
    TextureManager::Instance()->drawTexture("wall", rightWallRect.x, rightWallRect.y, rightWallRect.w, rightWallRect.h, renderer);

    SDL_Rect livesRect = { (int)livesXPos, (int)livesYPos, livesWidth, livesHeight };
    TextureManager::Instance()->drawTexture("lives", livesRect.x, livesRect.y, livesRect.w, livesRect.h, renderer);
}

int Screen::getBackgroundXPos() const {
    return backgroundXPos;
}

int Screen::getBackgroundYPos() const {
    return backgroundYPos;
}

int Screen::getBackgroundWidth() const {
    return backgroundWidth;
}

int Screen::getBackgroundHeight() const {
    return backgroundHeight;
}

int Screen::getLeftWallXPos() const {
    return leftWallXPos;
}

int Screen::getLeftWallYPos() const {
    return leftWallYPos;
}

int Screen::getLeftWallWidth() const {
    return leftWallWidth;
}

int Screen::getLeftWallHeight() const {
    return leftWallHeight;
}

int Screen::getRightWallXPos() const {
    return rightWallXPos;
}

int Screen::getRightWallYPos() const {
    return rightWallYPos;
}

int Screen::getRightWallWidth() const {
    return rightWallWidth;
}

int Screen::getRightWallHeight() const {
    return rightWallHeight;
}

int Screen::getLivesXPos() const {
    return livesXPos;
}

int Screen::getLivesYPos() const {
    return livesYPos;
}

int Screen::getLivesWidth() const {
    return livesWidth;
}

int Screen::getLivesHeight() const {
    return livesHeight;
}