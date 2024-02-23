#include "Bricks.h"
#include "TextureManager.h"
#include "Game.h"
#include "SDL.h"
#include "Ball.h"
#include "Game.h"

Bricks::Bricks()
{
}

void Bricks::loadBricksPositions() {

    for (int i = 0; i < 5; i++) { //create 5 bricks
        SDL_Rect brickRect = { 50 + i * 100, 50, brickWidth, brickHeight }; //first brick x pos, spacing, x-pos of whole row
        brickPos.push_back(brickRect); //add bricks positions to the vector
        brickV[i] = true;        //bricks are visible when they are created

    }

    for (int i = 5; i < 10; i++) {
        SDL_Rect brickRect = { 100 + (i - 5) * 100, 100, brickWidth, brickHeight };
        brickPos.push_back(brickRect);
        brickV[i] = true;
    }
}

void Bricks::drawBricks(SDL_Renderer* renderer) {
    for (int i = 0; i < 5; i++) { // iterate over the elements in vector
        if (brickV[i]) { // if the brick is visible (brickV = true)
            SDL_Rect brickRect = brickPos[i]; // create rect which contains the brick "elements"
            TextureManager::Instance()->drawTexture("brickY", brickRect.x, brickRect.y, brickRect.w, brickRect.h, renderer);
        }
    }
    for (int i = 5; i < 10; i++) { // iterate over the elements in vector
        if (brickV[i]) { // if the brick is visible (brickV = true)
            SDL_Rect brickRect = brickPos[i]; // create rect which contains the brick "elements"
            TextureManager::Instance()->drawTexture("brickG", brickRect.x, brickRect.y, brickRect.w, brickRect.h, renderer);
        }
    }
}

bool Bricks::checkCollision(double ballX, double ballY, int ballW, int ballH) {
    for (int i = 0; i < brickPos.size(); i++) {	//every brick in vector
        if (brickV[i])
        {
            if (ballY + ballH > brickPos[i].y && ballX + ballW > brickPos[i].x
                && ballX < brickPos[i].x + brickPos[i].w && ballY < brickPos[i].y + brickPos[i].h) {

                brickV[i] = false;	//hide the brick, because it was hit by ball
                cout << "ball hit brick" << endl;
            }
        }
    }
    return false;
}

int Bricks::getBrickHeight() const {
    return brickHeight;
}

void Bricks::setBrickHeight(int brickHeight) {
    Bricks::brickHeight = brickHeight;
}

int Bricks::getBrickWidth() const {
    return brickWidth;
}

void Bricks::setBrickWidth(int brickWidth) {
    Bricks::brickWidth = brickWidth;
}
