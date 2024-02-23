#pragma once
#include "SDL.h"

class Screen
{
public:
	Screen();

	void drawAll(SDL_Renderer* renderer);

	int getBackgroundXPos() const;

	int getBackgroundYPos() const;

	int getBackgroundWidth() const;

	int getBackgroundHeight() const;

	int getLeftWallXPos() const;

	int getLeftWallYPos() const;

	int getLeftWallWidth() const;

	int getLeftWallHeight() const;

	int getRightWallXPos() const;

	int getRightWallYPos() const;

	int getRightWallWidth() const;

	int getRightWallHeight() const;

	int getLivesXPos() const;

	int getLivesYPos() const;

	int getLivesWidth() const;

	int getLivesHeight() const;

private:
	//background:
	int backgroundXPos = 0; //x-position of background (left edge)
	int backgroundYPos = 0; //y-position of background (top edge)
	int backgroundWidth = 600; //background width
	int backgroundHeight = 400; //background height

	//left wall:
	int leftWallXPos = 0; //x-position of left wall (left edge)
	int leftWallYPos = 0; //y-position of left wall (top edge)
	int leftWallWidth = 25; //left wall width
	int leftWallHeight = 400; //left wall height

	//right wall:
	int rightWallXPos = 575; //x-position of left wall (left edge)
	int rightWallYPos = 1; //y-position of left wall (top edge)
	int rightWallWidth = 25; //left wall width
	int rightWallHeight = 400; //left wall height

	//lives:
	int livesXPos = 490; //x-position of heart (left edge)
	int livesYPos = 8; //y-position of left heart (top edge)
	int livesWidth = 30; //left wall heart
	int livesHeight = 30; //left wall heart
};

