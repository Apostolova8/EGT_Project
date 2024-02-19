#pragma once
#include <SDL.h>

class Game
{
public:
	Game();
	~Game();
	bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool isRunning();
	void movePaddle(int x, int y);
	void moveBall(int x, int y);

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	bool running;
	bool startButton = false;	//is the start button clicked
	int currentFrame;
	int xPos = 225; //x-position of paddle
	int yPos = 330; //y-position of paddle
	bool stopMoving = true; //paddle has to stop moving when it gets to the walls
	int xPos2 = 275; //x-position of ball
	int yPos2 = 320; //y-position of ball
};

