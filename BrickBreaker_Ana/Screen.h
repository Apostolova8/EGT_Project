#pragma once
#include "TextureManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

class Screen
{
public:
	Screen(SDL_Renderer* renderer);

	Screen();

    double getBackgroundXPos() const;

    void setBackgroundXPos(double backgroundXPos);

    double getBackgroundYPos() const;

    void setBackgroundYPos(double backgroundYPos);

    int getBackgroundWidth() const;

    void setBackgroundWidth(int backgroundWidth);

    int getBackgroundHeight() const;

    void setBackgroundHeight(int backgroundHeight);

    double getLeftWallXPos() const;

    void setLeftWallXPos(double leftWallXPos);

    double getLeftWallYPos() const;

    void setLeftWallYPos(double leftWallYPos);

    int getLeftWallWidth() const;

    void setLeftWallWidth(int leftWallWidth);

    int getLeftWallHeight() const;

    void setLeftWallHeight(int leftWallHeight);

    double getRightWallXPos() const;

    void setRightWallXPos(double rightWallXPos);

    double getRightWallYPos() const;

    void setRightWallYPos(double rightWallYPos);

    int getRightWallWidth() const;

    void setRightWallWidth(int rightWallWidth);

    int getRightWallHeight() const;

    void setRightWallHeight(int rightWallHeight);

private:
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;

	double backgroundXPos = 0; //x-position of background (left edge)
	double backgroundYPos = 0; //y-position of background (top edge)
	int backgroundWidth = 600; //background width
	int backgroundHeight = 400; //background height

	double leftWallXPos = 1; //x-position of left wall (left edge)
	double leftWallYPos = 1; //y-position of left wall (top edge)
	int leftWallWidth = 25; //left wall width
	int leftWallHeight = 400; //left wall height

	double rightWallXPos = 575; //x-position of left wall (left edge)
	double rightWallYPos = 1; //y-position of left wall (top edge)
	int rightWallWidth = 25; //left wall width
	int rightWallHeight = 400; //left wall height
};

