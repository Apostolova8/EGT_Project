#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"
#include "Bricks.h"
#include "Screen.h"

using namespace std;

Bricks* bricks = new Bricks();
Screen* screen = new Screen();

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
	cout << "SDL init success\n";

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		//Create window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != 0) {	// window init success
			cout << "Window creation success\n";
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer != 0) // renderer init success
			{
				cout << "Renderer creation success\n";
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

				//load textures:
				TextureManager::Instance()->loadTexture("images/startButton.jpg", "startButton", renderer);
				TextureManager::Instance()->loadTexture("images/background.jpg", "background", renderer);
				TextureManager::Instance()->loadTexture("images/paddle.jpg", "paddle", renderer);
				TextureManager::Instance()->loadTexture("images/wall.jpg", "wall", renderer);
				TextureManager::Instance()->loadTexture("images/ball.jpg", "ball", renderer);
				TextureManager::Instance()->loadTexture("images/brickG.jpg", "brickG", renderer);
				TextureManager::Instance()->loadTexture("images/brickY.jpg", "brickY", renderer);
				TextureManager::Instance()->loadTexture("images/lives.jpg", "lives", renderer);

				//load brick positions:
				bricks->loadBricksPositions();
			}

			if (!ttf_init()) {
				cout << "Failed to initialize TTF\n";
				return false;
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

	//switch in game process:
	switch (gameState) {
	case START:	//case start -> see start buton
		TextureManager::Instance()->drawTexture("startButton", 150, 150, 300, 120, renderer);	//start button
		break;
	case PLAY:	//case play -> render all textures by their objects, after clicked start button
		if (startButton == true) {
			screen->drawAll(renderer);
			ball.drawBall(renderer);
			paddle.drawPaddle(renderer);
			bricks->drawBricks(renderer);
			SDL_RenderCopy(renderer, textTextureFont1, NULL, &dRectFont1);
			SDL_RenderCopy(renderer, textTextureFont2, NULL, &dRectFont2);
		}
		break;
	case GAME_OVER:	//if lives = 0, game over
		if (ball.getLives() <= 0) {
			SDL_RenderCopy(renderer, textTextureFont3, NULL, &dRectFont3);
			SDL_RenderCopy(renderer, textTextureFont4, NULL, &dRectFont4);
			ball.setBallXSpeed(0);
			ball.setBallYSpeed(0);
			//running = false;
		}
		break;
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
				gameState = PLAY;
				ball.setBallYSpeed(0.9);
				ball.setBallXSpeed(0.9);
			}
			else
			{
				if (mouseX > 150 && mouseX < 450 && mouseY > 150 && mouseY < 270) {
					//check if the mouse click is on the start button
					startButton = true;
					gameState = PLAY;
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
			break;
		}
		if (event.button.button == SDL_BUTTON_LEFT) {	//left mouse click on screen
			switch (gameState) {
			case START:
				if (startButton == true) {	//if start button is clicked game state is PLAY, if not - START
					gameState = PLAY;
				}
				break;
			case PLAY:	// -//- load textures
				break;
			case GAME_OVER:	//if game ends, set the state to start, set 2 lives, load all bricks and get ball x and y position
				gameState = START;
				ball.setLives(2);
				bricks->loadBricksPositions();
				SDL_RenderCopy(renderer, textTextureFont1, NULL, &dRectFont1);
				SDL_RenderCopy(renderer, textTextureFont2, NULL, &dRectFont2);
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

bool Game::ttf_init() //for text
{
	if (TTF_Init() == -1) {
		return false;
	}

	TTF_Font* font1 = TTF_OpenFont("text/Arcade.ttf", 50);
	TTF_Font* font2 = TTF_OpenFont("text/Arcade.ttf", 50);
	TTF_Font* font3 = TTF_OpenFont("text/Arcade.ttf", 100);
	TTF_Font* font4 = TTF_OpenFont("text/Arcade.ttf", 25);

	if (font1 == NULL || font2 == NULL || font3 == NULL || font4 == NULL) {
		return false;
	}

	SDL_Surface* tempLivesText = NULL;
	SDL_Surface* tempScoreText = NULL;
	SDL_Surface* tempGOText = NULL;
	SDL_Surface* tempRestartText = NULL;

	tempLivesText = TTF_RenderText_Blended(font1, to_string(ball.getLives()).c_str(), { 255, 255, 255, 255 });
	tempScoreText = TTF_RenderText_Blended(font2, to_string(bricks->getPoints()).c_str(), { 255, 255, 255, 255 });
	
	std::string gameOverText = "Game Over"; 
	tempGOText = TTF_RenderText_Blended(font3, gameOverText.c_str(), { 255, 255, 255, 255 });

	std::string gameRestartText = "Click for new game.";
	tempRestartText = TTF_RenderText_Blended(font4, gameRestartText.c_str(), { 255, 255, 255, 255 });

	textTextureFont1 = SDL_CreateTextureFromSurface(renderer, tempLivesText);
	textTextureFont2 = SDL_CreateTextureFromSurface(renderer, tempScoreText);
	textTextureFont3 = SDL_CreateTextureFromSurface(renderer, tempGOText);
	textTextureFont4 = SDL_CreateTextureFromSurface(renderer, tempRestartText);

	int tw, th;
	SDL_QueryTexture(textTextureFont1, 0, 0, &tw, &th);
	dRectFont1 = { 540, 6, tw, th };
	SDL_QueryTexture(textTextureFont2, 0, 0, &tw, &th);
	dRectFont2 = { 300, 8, tw, th };
	SDL_QueryTexture(textTextureFont3, 0, 0, &tw, &th);
	dRectFont3 = { 90, 150, tw, th };
	SDL_QueryTexture(textTextureFont3, 0, 0, &tw, &th);
	dRectFont4 = { 90, 250, tw, th };

	SDL_FreeSurface(tempLivesText);
	TTF_CloseFont(font1);
	SDL_FreeSurface(tempScoreText);
	TTF_CloseFont(font2);
	SDL_FreeSurface(tempGOText); 
	TTF_CloseFont(font3);
	SDL_FreeSurface(tempRestartText);
	TTF_CloseFont(font4);

	return true;
}

void Game::update() {

	//update ball position with speed:
	ball.ballSpeed();

	//ball collision with paddle:
	ball.checkCollision(paddle.getPaddleXPos(), paddle.getPaddleYPos(), paddle.getPaddleWidth(), paddle.getPaddleHeight());

	//ball collision with walls:
	ball.collissionWalls();

	//ball collision with bricks:
	bricks->checkCollision(ball.getBallXPos(), ball.getBallYPos(), ball.getBallWidth(), ball.getBallHeight());

	//update game state:
	switch (gameState) {
	case START:
		break;
	case PLAY:
		if (ball.getLives() <= 0) {	//if lives = 0; game state = game over
			gameState = GAME_OVER;
		}
		break;
	case GAME_OVER:
		break;
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

Game::Game() : gameState(START), lives(2) {
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;
}

Game::~Game()
{
}
