#include "Bricks.h"
#include "TextureManager.h"
#include "Game.h"
#include "SDL.h"
#include "Ball.h"
#include <fstream> 

Bricks::Bricks()
{
}

void Bricks::loadBricksPositions() {
    int spacingBetweenBricks = 100;

    //yellow bricks in first row:
    int brickYellowXPos = 50;
    int brickYellowYPos = 80;

    for (int bricks = 0; bricks < 5; bricks++) {
        SDL_Rect brickRect = { brickYellowXPos + bricks * spacingBetweenBricks, brickYellowYPos, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 1)); //true visibility and 1 hit for yellow bricks
    }

    //gray bricks in second row:
    int brickGrayXPos = 100;
    int brickGrayYPos = 130;

    for (int bricks = 5; bricks < 10; bricks++) {
        SDL_Rect brickRect = { brickGrayXPos + (bricks - 5) * spacingBetweenBricks, brickGrayYPos, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 3)); //true visibility and 2 hits for gray bricks
    }
}

void Bricks::drawBricks(SDL_Renderer* renderer) {
    for (int bricks = 0; bricks < brickPos.size(); bricks++) {
        if (brickPos[bricks].isVisible) {    //if visibility is true

            SDL_Rect brickRect = brickPos[bricks].rect;

            switch (brickPos[bricks].hitCount) {
            case 1: //yellow brick if the hit count is 1
                TextureManager::Instance()->drawTexture("brickY", brickRect.x, brickRect.y, brickRect.w, brickRect.h, renderer);
                break;
            case 2: //broken gray brick if the hit count is 2
                TextureManager::Instance()->drawTexture("brickGBroken", brickRect.x, brickRect.y, brickRect.w, brickRect.h, renderer);
                break;
            case 3: //gray brick if the hit count is 3
                TextureManager::Instance()->drawTexture("brickG", brickRect.x, brickRect.y, brickRect.w, brickRect.h, renderer);
                break;
            default:
                break;
            }
        }
    }
}

bool Bricks::checkCollision(double x, double y, double& ys, double& xs, int w, int h) {
    for (int bricks = 0; bricks < brickPos.size(); bricks++) { //all of the bricks
        if (brickPos[bricks].isVisible && y + h > brickPos[bricks].rect.y && y < brickPos[bricks].rect.y + brickPos[bricks].rect.h
            && x + w > brickPos[bricks].rect.x && x < brickPos[bricks].rect.x + brickPos[bricks].rect.w) {

            ys = -ys;
            bricksSound = Mix_LoadWAV("music/bricks.mp3");
            Mix_PlayChannel(-1, bricksSound, 0);

            switch (brickPos[bricks].hitCount) {
            case 1:  //yellow bricks
                brickPos[bricks].isVisible = false;
                points += 1;
            case 2: //broken gray bricks
                brickPos[bricks].isVisible = false;
                points += 1;
                break;
            case 3: //gray bricks
                brickPos[bricks].hitCount = 2; 
                points += 1;
                xs = -xs;
                break;
            default:
                break;
            }
        }
    }
    return false;
}

bool Bricks::getAllBricksHit() const
{
    for (int bricks = 0; bricks < brickPos.size(); bricks++) {  //all bricks in vector
        if (brickPos[bricks].isVisible) {  //check if the brick is visible
            return false;  //if not every bricks is hidden
        }
    }
    return true;   //if there are no more bricks on the screen
}

void Bricks::savePointsToFile() {
    if (!pointsSaved) {
        std::ofstream file("points.txt", std::ios::app); //open the file
        if (file.is_open()) {   //if the file is open
            file << points << std::endl;    //write played points in it
            file.close();   //close file
            pointsSaved = true; //ensure that the points were stored only once
        }
    }
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

int Bricks::getPoints()
{
    return points;
}



