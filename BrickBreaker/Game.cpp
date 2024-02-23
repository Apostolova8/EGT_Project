#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"
#include "Bricks.h"

using namespace std;

Bricks* bricks = new Bricks();

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
				TextureManager::Instance()->loadTexture("images/lives.jpg", "lives", renderer);
				TextureManager::Instance()->loadTexture("images/gameOver.jpg", "gameOver", renderer);


				//load brick positions:
				bricks->loadBricksPositions();
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

	if (startButton == true) {	//if the start button is clicked (is true), show the background
		TextureManager::Instance()->drawTexture("background", backgroundXPos, backgroundYPos, backgroundWidth, backgroundHeight, renderer);	//background
		TextureManager::Instance()->drawTexture("paddle", paddle.getPaddleXPos(), paddle.getPaddleYPos(), paddle.getPaddleWidth(), paddle.getPaddleHeight(), renderer); //paddle
		TextureManager::Instance()->drawTexture("wall", leftWallXPos, leftWallYPos, leftWallWidth, leftWallHeight, renderer); //left wall
		TextureManager::Instance()->drawTexture("wall", rightWallXPos, rightWallYPos, rightWallWidth, rightWallHeight, renderer); //right wall
		TextureManager::Instance()->drawTexture("ball", ball.getBallXPos(), ball.getBallYPos(), ball.getBallWidth(), ball.getBallHeight(), renderer); //ball
		TextureManager::Instance()->drawTexture("lives", livesXPos, livesYPos, livesWidth, livesHeight, renderer); //lives

		//draw bricks:
		bricks->drawBricks(renderer);

		SDL_RenderCopy(renderer, textTextureFont1, NULL, &dRectFont1);

		if (ball.getLives() == 0) {
			TextureManager::Instance()->drawTexture("gameOver", 0, 0, ww, wh, renderer); //lives
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
		case SDL_MOUSEBUTTONDOWN:
			int mouseX;
			int mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			if (startButton == true) {	//ball start bouncing if user click on the screen if start button is clicked
				ball.setBallYSpeed(0.25);
				ball.setBallXSpeed(0.25);
			}
			else
			{
				if (mouseX > 150 && mouseX < 450 && mouseY > 150 && mouseY < 270) {
					//check if the mouse click is on the start button
					startButton = true;
				}
			}
			break;
		case SDL_KEYDOWN:	//move paddle
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				if (paddle.getPaddleXPos() == 15) {
					paddle.stopMovingPaddle = false;	//stop moving paddle when x-position of paddle reaches 15 (to the left wall)
				}
				else {
					paddle.setPaddleXPos(paddle.getPaddleXPos() - 30); //left moving
				}
				break;
			case SDLK_RIGHT:
				if (paddle.getPaddleXPos() == 465) {
					paddle.stopMovingPaddle = false;	//stop moving paddle when x-position of paddle reaches 465 (to the right wall)
				}
				else {
					paddle.setPaddleXPos(paddle.getPaddleXPos() + 30); //right moving
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
	paddle.setPaddleXPos(paddle.getPaddleXPos() + x);
	paddle.setPaddleYPos(paddle.getPaddleXPos() + y);
}

bool Game::ttf_init()
{
	if (TTF_Init() == -1) {
		return false;
	}
	TTF_Font* font1 = TTF_OpenFont("text/Arcade.ttf", 35);

	if (font1 == NULL) {
		return false;
	}

	SDL_Surface* tempLivesText = NULL;

	tempLivesText = TTF_RenderText_Blended(font1, to_string(ball.getLives()).c_str(), { 255,255,255,255 });
	//tempSurfaceText = TTF_RenderText_Blended(font1, "x", { 255,255,255,255 });

	textTextureFont1 = SDL_CreateTextureFromSurface(renderer, tempLivesText);

	int tw, th, tt, ww;
	SDL_QueryTexture(textTextureFont1, 0, 0, &tw, &th);
	dRectFont1 = { 530, 8, tw, th };

	SDL_FreeSurface(tempLivesText);
	TTF_CloseFont(font1);
}

void Game::update() {

	//update ball position with speed:
	ball.ballSpeed();	

	//ball collision with paddle:
	ball.checkCollision(paddle.getPaddleXPos(),paddle.getPaddleYPos(), paddle.getPaddleWidth(), paddle.getPaddleHeight());

	//ball collision with walls:
	ball.collissionWalls();

	//ball collision with bricks:
	bricks->checkCollision(ball.getBallXPos(), ball.getBallYPos(), ball.getBallWidth(), ball.getBallHeight());
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
