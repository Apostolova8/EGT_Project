#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"

using namespace std;

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

				TextureManager::Instance()->loadTexture("images/startButton.jpg", "startButton", renderer);
				TextureManager::Instance()->loadTexture("images/background.jpg", "background", renderer);
				TextureManager::Instance()->loadTexture("images/paddle.jpg", "paddle", renderer);
				TextureManager::Instance()->loadTexture("images/wall.jpg", "wall", renderer);
				TextureManager::Instance()->loadTexture("images/ball.jpg", "ball", renderer);
				TextureManager::Instance()->loadTexture("images/brickG.jpg", "brickG", renderer);
				TextureManager::Instance()->loadTexture("images/brickY.jpg", "brickY", renderer);

				//load brick positions:
				for (int i = 0; i < 5; i++) { //create 5 bricks
					SDL_Rect brickRect = { 50 + i * 100, 50, brickWidth, brickHeight };
									//brick first x position + spacing, brick's row y position
					brickPos.push_back(brickRect);	//add bricks positions to the vector
					brickV[i] = true; //bricks are visible when they are created
				}

				for (int i = 5; i < 10; i++) {
					SDL_Rect brickRect = { 100 + (i - 5) * 100, 100, brickWidth, brickHeight };
					brickPos.push_back(brickRect);
					brickV[i] = true; 
				}
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

	return true;
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);

	TextureManager::Instance()->drawTexture("startButton", 150, 150, 300, 120, renderer);	//start button
	//TextureManager::Instance()->drawOneFrameFromTexture("1", 0, 0, 130, 130, 2, currentFrame, renderer);

	if (startButton == true) {	//if the start button is clicked (is true), show the background
		TextureManager::Instance()->drawTexture("background", backgroundXPos, backgroundYPos, backgroundWidth, backgroundHeight, renderer);	//background
		TextureManager::Instance()->drawTexture("paddle", paddleXPos, paddleYPos, paddleWidth, paddleHeight, renderer); //paddle
		TextureManager::Instance()->drawTexture("wall", leftWallXPos, leftWallYPos, leftWallWidth, leftWallHeight, renderer); //left wall
		TextureManager::Instance()->drawTexture("wall", rightWallXPos, rightWallYPos, rightWallWidth, rightWallHeight, renderer); //right wall
		TextureManager::Instance()->drawTexture("ball", ballXPos, ballYPos, ballWidth, ballHeight, renderer); //ball

		//draw bricks:
		for (int i = 0; i < brickPos.size(); i++) { //iterate over the elements in vector
			if (brickV[i]) { //if the brick is visible (brickV = true)
				SDL_Rect brickRect = brickPos[i]; //create rect which contains the brick "elements"
				TextureManager::Instance()->drawTexture("brickY", brickRect.x, brickRect.y, brickRect.w, brickRect.h, renderer);
			}
		}
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
			paddleXPos = mouseX - paddleWidth / 2;
			if (mouseX > 150 && mouseX < 450 && mouseY > 150 && mouseY < 270) {
				// Check if the mouse click is on the start button
				startButton = true;
			}
			break;
		case SDL_KEYDOWN:	//move paddle
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				if (paddleXPos == 15) {
					stopMoving = false;	//stop moving paddle when x-position of paddle reaches 15 (to the left wall)
				}
				else {
					paddleXPos -= 15; //left moving
				}
				break;
			case SDLK_RIGHT:
				if (paddleXPos == 465) {
					stopMoving = false;	//stop moving paddle when x-position of paddle reaches 465 (to the right wall)
				}
				else {
					paddleXPos += 15; //right moving
				}
				break;
			default:
				break;
			}
		}
	}
}

void Game::movePaddle(int x, int y)
{
	paddleXPos += x;
	paddleYPos += y;
}

void Game::update() {

	ballXPos += ballXSpeed;
	ballYPos += ballYSpeed;

	//cout << "Ball X Position: " << ballXPos << endl;
	//cout << "Ball Y Position: " << ballYPos << endl;

	//collision with walls
	if (ballXPos < 25 || ballXPos + ballWidth >= 575) { //if the ball hits left or right edge of walls
		ballXSpeed = -ballXSpeed; //reverse direction horizontally
	}
	cout << "ball hits left/right wall" << endl;
	if (ballYPos < 0 || ballYPos + ballHeight >= 330) { //if the ball hits top of the window 
		ballYSpeed = -ballYSpeed; //reverse direction vertically
	}
	cout << "ball hits top of the screen" << endl;

	//collision with paddle
	if (ballYPos + ballHeight > paddleYPos) { //if bottom edge of the ball touches top edge of the paddle
		ballYPos = -ballYSpeed;
		//ballYPos = paddleYPos - ballHeight; //collision detection between the ball and the paddle
		cout << "ball touched paddle" << endl;
	}

	//ball falls
	if (ballYPos > 400) {
		ballXPos = 275; // Reset to starting X position
		ballYPos = 330; // Reset to starting Y position
		ballXSpeed = 0.5; // Reset X speed
		ballYSpeed = 0.5; // Reset Y speed
		cout << "ball fell off the screen" << endl;
	}

	//collision with bricks
	for (int i = 0; i < brickPos.size(); i++) {	//every brick in vector
		if (brickV[i] && ballXPos + ballWidth > brickPos[i].x &&	//right edge of the ball is to the left edge of the brick
			ballXPos < brickPos[i].x + brickPos[i].w &&				//left edge of the ball is to the right edge of the brick
			ballYPos + ballHeight > brickPos[i].y &&				//bottom edge of the ball is below the top edge of the brick
			ballYPos < brickPos[i].y + brickPos[i].h) {				//top edge of the ball is above the bottom edge of the brick

			brickV[i] = false;	//hide the brick, because it was hit by ball

			ballYSpeed = -ballYSpeed;	//reverse speed
			cout << "ball hit brick" << endl;
		}
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