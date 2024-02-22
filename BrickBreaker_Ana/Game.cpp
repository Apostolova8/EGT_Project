#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Screen.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_ttf.h"

using namespace std;

Screen* screen = new Screen();

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
				TextureManager::Instance()->loadTexture("images/paddle.jpg", "paddle", renderer);
				TextureManager::Instance()->loadTexture("images/ball.jpg", "ball", renderer);
				TextureManager::Instance()->loadTexture("images/wall.jpg", "wall", renderer);
				TextureManager::Instance()->loadTexture("images/background.jpg", "background", renderer);
				TextureManager::Instance()->loadTexture("images/brickG.jpg", "grayBrick", renderer);
				TextureManager::Instance()->loadTexture("images/brickY.jpg", "yellowBrick", renderer);
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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	int ww, wh;
	SDL_GetWindowSize(window, &ww, &wh);

	TextureManager::Instance()->drawTexture("startButton", 150, 150, 300, 120, renderer);	//start button
													    // xPos yPos  w    h


	if (startButton == true) {	//if the start button is clicked (is true), show the background
		TextureManager::Instance()->drawTexture("background", screen->getBackgroundXPos(), screen->getBackgroundYPos(), screen->getBackgroundWidth(), screen->getBackgroundHeight(), renderer);	//background
		TextureManager::Instance()->drawTexture("paddle", paddle.getPaddleXPos(), paddle.getPaddleYPos(), paddle.getPaddleWidth(), paddle.getPaddleHeight(), renderer); //paddle
		TextureManager::Instance()->drawTexture("wall", screen->getLeftWallXPos(), screen->getLeftWallYPos(), screen->getLeftWallWidth(), screen->getLeftWallHeight(), renderer); //left wall
		TextureManager::Instance()->drawTexture("wall", screen->getRightWallXPos(), screen->getRightWallYPos(), screen->getRightWallWidth(), screen->getRightWallHeight(), renderer); //right wall
		TextureManager::Instance()->drawTexture("ball", ball.getBallXPos(), ball.getBallYPos(), ball.getBallHeight(), ball.getBallWidth(), renderer); //ball
		//TextureManager::Instance()->drawTexture("grayBrick", ball.getBallXPos(), ball.getBallYPos(), ball.getBallHeight(), ball.getBallWidth(), renderer); //ball
		//TextureManager::Instance()->drawTexture("yellowBrick", ball.getBallXPos(), ball.getBallYPos(), ball.getBallHeight(), ball.getBallWidth(), renderer); //ball

		SDL_RenderCopy(renderer, textTextureLives, NULL, &dRectLives);

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
			if (mouseX > 150 && mouseX < 450 && mouseY > 150 && mouseY < 270) {	//check if the mouse click is on the start button 
				//150x->left corner; 450x->left corner+width(300); 150y->right corner; 270y->right corner+height(120)
				startButton = true;
			}
			break;
		case SDL_KEYDOWN:	//move paddle
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				if (paddle.getPaddleXPos() == 15) {
					paddle.stopMovingPaddle = false;	//stop moving paddle when x-position of paddle reaches 15 (to the left wall)
				}
				else {
					paddle.setPaddleXPos(paddle.getPaddleXPos() - 15); //left moving
				}
				break;
			case SDLK_RIGHT:
				if (paddle.getPaddleXPos() == 465) {
					paddle.stopMovingPaddle = false;	//stop moving paddle when x-position of paddle reaches 465 (to the right wall)
				}
				else {
					paddle.setPaddleXPos(paddle.getPaddleXPos() + 15); //right moving
				}
				break;
			default:
				break;

			}
		}
	}
}

void Game::update() {
	ball.ballUpdate();
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

bool Game::ttf_init()
{
	if (TTF_Init() == -1) {
		return false;
	}
	TTF_Font* lives = TTF_OpenFont("text/Arcade.ttf", 25);

	if (lives == NULL) {
		return false;
	}

	SDL_Surface* tempSurfaceText = NULL;

	tempSurfaceText = TTF_RenderText_Blended(lives, "x2", { 255,255,204,255 });	//font, text, color
	textTextureLives = SDL_CreateTextureFromSurface(renderer, tempSurfaceText);

	int tw, th;
	SDL_QueryTexture(textTextureLives, 0, 0, &tw, &th);
	dRectLives = { 600 - tw - 25, 25, tw, th};

	SDL_FreeSurface(tempSurfaceText);
	TTF_CloseFont(lives);

	return true;
}


Game::Game() {
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;
}

Game::~Game()
{
}



