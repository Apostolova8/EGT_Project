#pragma once
#include "SDL.h"
#include <vector>
#include "TextureManager.h"

class Bricks
{
public: 
	Bricks();

	void loadBricks();
    
	void drawBricks(SDL_Renderer* renderer);

    bool checkCollision(int x, int y, int w, int h);

	int getBrickHeight() const;

	void setBrickHeight(int brickHeight);

	int getBrickWidth() const;

	void setBrickWidth(int brickWidth);

private:
	int brickHeight = 50;
	int brickWidth = 50;

	std::vector<SDL_Rect> brickPos; //hold bricks positions
	bool brickV[10]; //which brick is visible
};

