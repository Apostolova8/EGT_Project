#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"

using namespace std;

int c = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
	cout << "SDL init success\n";

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		// Create window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != 0) {	// window init success
			cout << "Window creation success\n";
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer != 0) // renderer init success
			{
				cout << "Renderer creation success\n";
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				
				TextureManager::Instance()->loadTexture("images/startButton.jpg", "1", renderer);
				TextureManager::Instance()->loadTexture("images/background.jpg", "2", renderer);
				TextureManager::Instance()->loadTexture("images/paddle.jpg", "3", renderer);
				TextureManager::Instance()->loadTexture("images/wall.jpg", "4", renderer);
				TextureManager::Instance()->loadTexture("images/ball.jpg", "5", renderer);
			}

			else {
				cout << "Renderer init failed\n";
				return false;
			}

		}
		else {
			cout << "Window init failed\n";
			return false;
		}
	}
	else {
		cout << "SDL init failed\n";
		return false;
	}
	cout << "Init success\n";
	running = true;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);

	TextureManager::Instance()->drawTexture("1", 150, 150, 300, 120, renderer);	//start button
	//TextureManager::Instance()->drawOneFrameFromTexture("1", 0, 0, 130, 130, 2, currentFrame, renderer);

	if (startButton == true) {	//if the start button is clicked (is true), show the background
		TextureManager::Instance()->drawTexture("2", 0, 0, 600, 400, renderer);	//background
		TextureManager::Instance()->drawTexture("3", xPos, yPos, 120, 30, renderer); //paddle
		TextureManager::Instance()->drawTexture("4", 1, 1, 25, 400, renderer); //left wall
		TextureManager::Instance()->drawTexture("4", 575, 1, 25, 400, renderer); //right wall
		TextureManager::Instance()->drawTexture("5", xPos2, yPos2, 20, 20, renderer); //ball
	}


	SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_MOUSEBUTTONDOWN:	//click start button
			int mouseX;
			int mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			if (mouseX > 150 && mouseX < 450 && mouseY > 150 && mouseY < 270) {	//ckeck if the mouse click is on the start button 
				//150x->left corner; 450x->left corner+width(300); 150y->right corner; 270y->right corner+height(120)
				startButton = true;
			}
		case SDL_KEYDOWN:	//move paddle
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				if (xPos == 15) {
					stopMoving = false;	//stop moving paddle when x-position of paddle reaches 15 (to the left wall)
				}
				else {
					xPos -= 5; //left moving
				}
				break;
			case SDLK_RIGHT:
				if (xPos == 465) {
					stopMoving = false;	//stop moving paddle when x-position of paddle reaches 465 (to the right wall)
				}
				else {
					xPos += 5; //right moving
				}
				break;
			default:
				break;
			}
		}
	}
}

void Game::movePaddle(int x, int y) {
	xPos += x;
	yPos += y;
}

void Game::update() {
	int lives = 2;

	double xSpeedC = 0.055; //decrease velocity of ball
	double ySpeedC = 0.055;

	xPos2 += xSpeed * xSpeedC; //update x-position along with x-speed
	yPos2 += ySpeed * ySpeedC; //update y-position along with y-speed

	//Ball bouncing:
	if (xPos2 < 25 || xPos2 + width >= 575) { //if the ball hits left or right edge of window
		xSpeed = -xSpeed; //reverse direction horizontally
	}
	if (yPos2 < 0 || yPos2 + height >= 350) { //if the ball hits top of the window or bottom edge of the paddle)
		ySpeed = -ySpeed; //reverse direction vertically
	}

	//Ball touches the paddle:
	SDL_Rect paddleS = { 225, 330, 120, 30 }; //x, y coordinates and size of the paddle
	if (yPos2 + height >= paddleS.y && xPos2 > xPos && xPos2 > xPos + width) {
	//if bottom edge of the ball touches top edge of the paddle; left -//- and right -//-
		ySpeed = -ySpeed;
		yPos2 = paddleS.y - height; //collision detection between the ball and the paddle
	}

	//Reset ball position to the initially position if it falls off the bottom
	if (yPos2 + height >= 350) { //ball falls
		xPos2 = xPos + 50; 
		yPos2 = yPos;
		xSpeed = 0;
		ySpeed = 0;
		lives -= 1;
	}
}

void Game::clean() {
	cout << "Cleaning class\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

bool Game::isRunning() {
	return Game::running;
}

Game::Game() {
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;
}

Game::~Game()
{
}




