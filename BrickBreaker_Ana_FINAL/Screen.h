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

	int getStartButtonXPos() const;

	void setStartButtonXPos(int startButtonXPos);

	int getStartButtonYPos() const;

	void setStartButtonYPos(int startButtonYPos);

	int getStartButtonWidth() const;

	void setStartButtonWidth(int startButtonWidth);

	int getStartButtonHeight() const;

	void setStartButtonHeight(int startButtonHeight);

	int getStartBackgroundXPos() const;

	void setStartBackgroundXPos(int startBackgroundXPos);

	int getStartBackgroundYPos() const;

	void setStartBackgroundYPos(int startBackgroundYPos);

	int getStartBackgroundWidth() const;

	void setStartBackgroundWidth(int startBackgroundWidth);

	int getStartBackgroundHeight() const;

	void setStartBackgroundHeight(int startBackgroundHeight);

	int getEgtxPos() const;

	void setEgtxPos(int egtxPos);

	int getEgtyPos() const;

	void setEgtyPos(int egtyPos);

	int getEgtWidth() const;

	void setEgtWidth(int egtWidth);

	int getEgtHeight() const;

	void setEgtHeight(int egtHeight);

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
	int rightWallXPos = 575; //x-position of right wall (left edge)
	int rightWallYPos = 0; //y-position of right wall (top edge)
	int rightWallWidth = 25; //right wall width
	int rightWallHeight = 400; //right wall height

	//lives:
	int livesXPos = 490; //x-position of heart (left edge)
	int livesYPos = 7; //y-position of heart (top edge)
	int livesWidth = 40; //heart width
	int livesHeight = 40; //heart height

	//start button:
	int startButtonXPos = 150; //x-position of start button (left edge)
	int startButtonYPos = 150; //y-position of start button (top edge)
	int startButtonWidth = 300; //left wall start button
	int startButtonHeight = 120; //left wall start button

	//start background:
	int startBackgroundXPos = 0; //x-position of start background (left edge)
	int startBackgroundYPos = 0; //y-position of start background (top edge)
	int startBackgroundWidth = 600; //left wall start background
	int startBackgroundHeight = 400; //left wall start background

	//egt logo:
	int EGTXPos = 530; //x-position of egt logo (left edge)
	int EGTYPos = 10; //y-position of egt logo (top edge)
	int EGTWidth = 60; //left wall egt logo
	int EGTHeight = 60; //left wall egt logo
};

