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
    ///yellow bricks in first row:
    for (int i = 0; i < 5; i++) {
        SDL_Rect brickRect = { 50 + i * 100, 80, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 1)); //true visibility and 1 hit for yellow bricks
    }

    ///gray bricks in second row:
    for (int i = 5; i < 10; i++) {
        SDL_Rect brickRect = { 100 + (i - 5) * 100, 130, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 3)); //true visibility and 2 hits for gary bricks
    }
}

void Bricks::drawBricks(SDL_Renderer* renderer) {
    for (int i = 0; i < brickPos.size(); i++) {
        if (brickPos[i].isVisible) {    //if visibility is true
            SDL_Rect brickRect = brickPos[i].rect;
            if (brickPos[i].hitCount == 1) {    //yellow brick if the hit count is 1
                TextureManager::Instance()->drawTexture("brickY", brickRect.x, brickRect.y, brickRect.w, brickRect.h, renderer);
            }
            else if (brickPos[i].hitCount == 2) {   //broken gray brick if the hit count is 2
                TextureManager::Instance()->drawTexture("brickGBroken", brickRect.x, brickRect.y, brickRect.w, brickRect.h, renderer);
            }
            else if (brickPos[i].hitCount == 3) {   //gray brick if the hit count is 3
                TextureManager::Instance()->drawTexture("brickG", brickRect.x, brickRect.y, brickRect.w, brickRect.h, renderer);
            }
        }
    }
}

bool Bricks::checkCollision(double x, double y, double& ys, double& xs, int w, int h) {
    for (int i = 0; i < brickPos.size(); i++) { //all of the bricks
        if (brickPos[i].isVisible && y + h > brickPos[i].rect.y && y < brickPos[i].rect.y + brickPos[i].rect.h
            && x + w > brickPos[i].rect.x && x < brickPos[i].rect.x + brickPos[i].rect.w) {
           
            ys = -ys;
            bricksSound = Mix_LoadWAV("music/bricks.mp3");
            Mix_PlayChannel(-1, bricksSound, 0);

            if (brickPos[i].hitCount == 1) { //yellow bricks
                brickPos[i].isVisible = false;
                points += 1;
            }
            if (brickPos[i].hitCount == 2) { //broken gray bricks
                brickPos[i].isVisible = false;
                points += 1;
               
            }
            if (brickPos[i].hitCount == 3) { //gray bricks
                brickPos[i].hitCount = 2;
                points += 1;
                xs = -xs;
            }

        }
    }
    return false;
}

bool Bricks::getAllBricksHit() const
{
    for (int i = 0; i < brickPos.size(); i++) {  //all bricks in vector
        if (brickPos[i].isVisible) {  //check if the brick is visible
            return false;  //if not every bricks is hiiden
        }
    }
    return true;    //if there are no more bricks 
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




