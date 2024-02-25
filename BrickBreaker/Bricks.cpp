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
    for (int i = 0; i < 3; i++) {
        SDL_Rect brickRect = { 50 + i * 100, 50, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 1)); //true visibility and 1 hit for yellow bricks
    }

    //gray bricks in second row:
    for (int i = 3; i < 5; i++) {
        SDL_Rect brickRect = { 300 + (i - 3) * 70, 150, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 2)); //true visibility and 2 hits for gray bricks
    }

    ///yellow bricks in third row:
    for (int i = 5; i < 7; i++) {
        SDL_Rect brickRect = { 120 + (i-6) * 100, 200, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 1)); //true visibility and 1 hit for yellow bricks
    }

    //gray bricks in fourth row:
    for (int i = 7; i < 8; i++) {
        SDL_Rect brickRect = { 60 + (i - 7) * 50, 120, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 2)); //true visibility and 2 hits for gray bricks
    }

    //yellow bricks in fifth row:
    for (int i = 8; i < 9; i++) {
        SDL_Rect brickRect = { 390 + (i - 7) * 50, 200, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 1)); //true visibility and 2 hits for gray bricks
    }

    //gray bricks in sixth row:
    for (int i = 9; i < 11; i++) {
        SDL_Rect brickRect = { 420 + (i - 9) * 70, 80, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 2)); //true visibility and 2 hits for gray bricks
    }

    //yellow bricks in seventh row:
    for (int i = 11; i < 12; i++) {
        SDL_Rect brickRect = { 250 + (i - 9) * 70, 20, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 1)); //true visibility and 2 hits for gray bricks
    }

    //gray bricks in eighth row:
    for (int i = 11; i < 12; i++) {
        SDL_Rect brickRect = { 70 + (i - 9) * 70, 170, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 2)); //true visibility and 2 hits for gray bricks
    }

}

void Bricks::drawBricks(SDL_Renderer* renderer) {
    for (int i = 0; i < brickPos.size(); i++) {
        if (brickPos[i].isVisible) {    //if visibility is true
            SDL_Rect brickRect = brickPos[i].rect;
            if (brickPos[i].hitCount == 1) {    //draw yellow brick if the hit count is 1
                TextureManager::Instance()->drawTexture("brickY", brickRect.x, brickRect.y, brickRect.w, brickRect.h, renderer);
            }
            if (brickPos[i].hitCount == 2) {   //draw gray brick if the hit count is 2
                TextureManager::Instance()->drawTexture("brickG", brickRect.x, brickRect.y, brickRect.w, brickRect.h, renderer);
            }
        }
    }
}

bool Bricks::checkCollision(double x, double y, double& ys, double& xs, int w, int h) {
    for (int i = 0; i < brickPos.size(); i++) { //for all of the bricks
        if (brickPos[i].isVisible) {    //if bricks are visible
            if (y + h > brickPos[i].rect.y && x + w > brickPos[i].rect.x    //check collision with ball
                && x < brickPos[i].rect.x + brickPos[i].rect.w && y < brickPos[i].rect.y + brickPos[i].rect.h) {

                if (brickPos[i].hitCount == 2) { //gray brick
                    ys = -ys;
                    xs = -xs;
                    brickPos[i].hitCount -= 1; //turn gray brick into yellow
                    points += 1;
                    cout << "hit gray brick\n";
                }
                else if (brickPos[i].hitCount == 1) { //yellow brick
                    ys = -ys;
                    points += 1;
                    brickPos[i].isVisible = false;
                    cout << "hit yellow brick\n";
                }
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




