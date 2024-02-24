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
    //yellow bricks in first row:
    for (int i = 0; i < 5; i++) {
        SDL_Rect brickRect = { 50 + i * 100, 50, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 1)); //true visability and 1 hit for yellow bricks
    }

    //gray bricks in second row:
    for (int i = 5; i < 10; i++) {
        SDL_Rect brickRect = { 100 + (i - 5) * 100, 100, brickWidth, brickHeight };
        brickPos.push_back(Brick(brickRect, true, 2)); //true visability and 2 hits for yellow bricks
    }
}

void Bricks::drawBricks(SDL_Renderer* renderer) {
    for (int i = 0; i < brickPos.size(); i++) {
        if (brickPos[i].isVisible) {    //if visability is true
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

bool Bricks::checkCollision(double x, double y, int w, int h) {

    for (int i = 0; i < brickPos.size(); i++) { //for all of the bricks
        if (brickPos[i].isVisible) {    //if bricks are visible
            if (y + h > brickPos[i].rect.y && x + w > brickPos[i].rect.x    //check collision with ball
                && x < brickPos[i].rect.x + brickPos[i].rect.w && y < brickPos[i].rect.y + brickPos[i].rect.h) {

                if (brickPos[i].hitCount == 2) { //gray brick
                    brickPos[i].hitCount--; //turn gray brick into yellow
                    points += 1;
                    cout << "hit gray brick\n";
                }
                else if (brickPos[i].hitCount == 0) { //gray brick
                    brickPos[i].isVisible = false; //turn gray brick into yellow
                    cout << "hit gray brick\n";
                }
                //else if (brickPos[i].hitCount == 0) { 
                //    brickPos[i].isVisible == false;
                //    cout << "hit gray brick\n";
                //}
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

int Bricks::getPoints()
{
    return points;
}
