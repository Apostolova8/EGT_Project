#include "Screen.h"
#include "TextureManager.h"
#include "Game.h"

Screen::Screen(SDL_Renderer* renderer)
{
}

Screen::Screen()
{
    std::cout << "screen ok" << std::endl;
}

double Screen::getBackgroundXPos() const {
    return backgroundXPos;
}

void Screen::setBackgroundXPos(double backgroundXPos) {
    this->backgroundXPos = backgroundXPos;
}

double Screen::getBackgroundYPos() const {
    return backgroundYPos;
}

void Screen::setBackgroundYPos(double backgroundYPos) {
    this->backgroundYPos = backgroundYPos;
}

int Screen::getBackgroundWidth() const {
    return backgroundWidth;
}

void Screen::setBackgroundWidth(int backgroundWidth) {
    this->backgroundWidth = backgroundWidth;
}

int Screen::getBackgroundHeight() const {
    return backgroundHeight;
}

void Screen::setBackgroundHeight(int backgroundHeight) {
    this->backgroundHeight = backgroundHeight;
}

double Screen::getLeftWallXPos() const {
    return leftWallXPos;
}

void Screen::setLeftWallXPos(double leftWallXPos) {
    this->leftWallXPos = leftWallXPos;
}

double Screen::getLeftWallYPos() const {
    return leftWallYPos;
}

void Screen::setLeftWallYPos(double leftWallYPos) {
    this->leftWallYPos = leftWallYPos;
}

int Screen::getLeftWallWidth() const {
    return leftWallWidth;
}

void Screen::setLeftWallWidth(int leftWallWidth) {
    this->leftWallWidth = leftWallWidth;
}

int Screen::getLeftWallHeight() const {
    return leftWallHeight;
}

void Screen::setLeftWallHeight(int leftWallHeight) {
    this->leftWallHeight = leftWallHeight;
}

double Screen::getRightWallXPos() const {
    return rightWallXPos;
}

void Screen::setRightWallXPos(double rightWallXPos) {
    this->rightWallXPos = rightWallXPos;
}

double Screen::getRightWallYPos() const {
    return rightWallYPos;
}

void Screen::setRightWallYPos(double rightWallYPos) {
    this->rightWallYPos = rightWallYPos;
}

int Screen::getRightWallWidth() const {
    return rightWallWidth;
}

void Screen::setRightWallWidth(int rightWallWidth) {
    this->rightWallWidth = rightWallWidth;
}

int Screen::getRightWallHeight() const {
    return rightWallHeight;
}

void Screen::setRightWallHeight(int rightWallHeight) {
    this->rightWallHeight = rightWallHeight;
}