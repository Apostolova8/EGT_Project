#pragma once
#include "SDL.h"
#include <vector>
#include "TextureManager.h"

class Bricks
{
public: 
	Bricks();

	void loadBricksPositions();
    
	void drawBricks(SDL_Renderer* renderer);

    bool checkCollision(double x, double y, double& ys, double& xs, int w, int h);

	int getBrickHeight() const;

	void setBrickHeight(int brickHeight);

	int getBrickWidth() const;

	void setBrickWidth(int brickWidth);

	int getPoints();

	bool getAllBricksHit() const; //are all bricks hitted

	void savePointsToFile(); //store points

	Mix_Chunk* bricksSound;

private:
	int brickHeight = 30;
	int brickWidth = 50;
	int points = 0;
	bool pointsSaved = false; //to store played points only one time
	int allBricks; //all bricks hit

	struct Brick {	//make a struct to store visibility and hitting count of bricks
		SDL_Rect rect;	//rect for drawing
		bool isVisible;	//bool for visibility
		int hitCount = 0;	//int for track hit count of different types of bricks

		Brick(SDL_Rect rect, bool isVisible, int hitCount) : rect(rect), isVisible(isVisible), hitCount(hitCount) {}
	};
	std::vector<Brick> brickPos; //vector for holding bricks positions
};

