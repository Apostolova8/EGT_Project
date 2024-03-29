#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"
#include "Bricks.h"
#include "Ball.h"
#include "Screen.h"
#include "SoundManager.h"

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

				Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
				Mix_Music* backgroundMusic = Mix_LoadMUS("music/backgroundMusic.mp3");
				Mix_PlayMusic(backgroundMusic, -1);
				startButtonSound = Mix_LoadWAV("music/startButton.mp3");
				wallsSound = Mix_LoadWAV("music/walls.mp3");
				winSound = Mix_LoadWAV("music/win.mp3");
				gameOverSound = Mix_LoadWAV("music/gameOver.mp3");

				//load textures:
				TextureManager::Instance()->loadTexture("images/startButton.jpg", "startButton", renderer);
				TextureManager::Instance()->loadTexture("images/background.jpg", "background", renderer);
				TextureManager::Instance()->loadTexture("images/paddle.png", "paddle", renderer);
				TextureManager::Instance()->loadTexture("images/wall.jpg", "wall", renderer);
				TextureManager::Instance()->loadTexture("images/ball.jpg", "ball", renderer);
				TextureManager::Instance()->loadTexture("images/brickG.jpg", "brickG", renderer);
				TextureManager::Instance()->loadTexture("images/brickY.jpg", "brickY", renderer);
				TextureManager::Instance()->loadTexture("images/brickGBroken.jpg", "brickGBroken", renderer);
				TextureManager::Instance()->loadTexture("images/lives.jpg", "lives", renderer);
				TextureManager::Instance()->loadTexture("images/EGT.png", "EGT", renderer);
				TextureManager::Instance()->loadTexture("images/start.jpg", "start", renderer);

				//load brick positions:
				bricks->loadBricksPositions(); //load bricks positions
				SoundManager::Instance()->playMusic("backgroundMusic", 0, 5000);

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
	SDL_SetRenderDrawColor(renderer, 245, 222, 179, 255);
	SDL_RenderClear(renderer);

	TextureManager::Instance()->drawTexture("start", 0, 0, 600, 400, renderer);
	TextureManager::Instance()->drawTexture("startButton", 150, 150, 300, 120, renderer);	//draw start button
	TextureManager::Instance()->drawTexture("EGT", 530, 10, 60, 60, renderer);

		if (startButton == true) {	//if start button is clicked, draw everything on screen
			screen->drawAll(renderer);
			ball.drawBall(renderer);
			paddle.drawPaddle(renderer);
			bricks->drawBricks(renderer);
			SDL_RenderCopy(renderer, textTextureFont1, NULL, &dRectFont1);	//lives
			SDL_RenderCopy(renderer, textTextureFont2, NULL, &dRectFont2);	//scores
		}
		if (ball.getLives() == 0) {	//if lives = 0;
			bricks->savePointsToFile(); //save score
			SDL_RenderCopy(renderer, textTextureFont3, NULL, &dRectFont3);	//game over text
			Mix_PlayChannel(-1, gameOverSound, 0); //game over sound
			SDL_Delay(2000); //delay between game over sound and close audio
			Mix_CloseAudio(); //stop background music if game is over
		}
		if (bricks->getAllBricksHit()) {
			bricks->savePointsToFile();
			SDL_RenderCopy(renderer, textTextureFont4, NULL, &dRectFont4); 
			Mix_PlayChannel(-1, winSound, 0);
			SDL_Delay(2000);
			Mix_CloseAudio();
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
				ball.setBallYSpeed(0.5);
				ball.setBallXSpeed(0.5);
			}
			else
			{
				if (mouseX > 150 && mouseX < 450 && mouseY > 150 && mouseY < 270) {
					//check if the mouse click is on the start button
					Mix_PlayChannel(-1, startButtonSound, 0);
					startButton = true;
				}
			}
			break;
		case SDL_KEYDOWN:	//move paddle
			switch (event.key.keysym.sym) {
			case SDLK_LEFT:
				if (paddle.getPaddleXPos() == 15) {
					paddle.stopMovingPaddle = false;	//stop moving paddle when x-position of paddle reaches 15 (to the left wall)
					Mix_PlayChannel(-1, wallsSound, 0);
				}
				else {
					paddle.setPaddleXPos(paddle.getPaddleXPos() - 30); //left moving
				}
				break;
			case SDLK_RIGHT:
				if (paddle.getPaddleXPos() == 465) {
					paddle.stopMovingPaddle = false;	//stop moving paddle when x-position of paddle reaches 465 (to the right wall)
					Mix_PlayChannel(-1, wallsSound, 0);
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
	}
}

void Game::movePaddle(int x, int y)
{
	paddle.setPaddleXPos(paddle.getPaddleXPos() + x);
	paddle.setPaddleYPos(paddle.getPaddleXPos() + y);
}

bool Game::ttf_init() //for text
{
	int tw, th;

	if (TTF_Init() == -1) {
		return false;
	}

	//TEXT FOR LIVES:
	TTF_Font* font1 = TTF_OpenFont("text/Arcade.ttf", 60);
	if (font1 == NULL) {
		return false;
	}
	SDL_Surface* tempLivesText = NULL;
	tempLivesText = TTF_RenderText_Blended(font1, to_string(ball.getLives()).c_str(), { 128, 0, 0, 255 });
	textTextureFont1 = SDL_CreateTextureFromSurface(renderer, tempLivesText);
	SDL_QueryTexture(textTextureFont1, 0, 0, &tw, &th);
	dRectFont1 = { 540, 6, tw, th };
	SDL_FreeSurface(tempLivesText);
	TTF_CloseFont(font1);

	//TEXT FOR POINTS
	TTF_Font* font2 = TTF_OpenFont("text/Arcade.ttf", 80);
	if (font2 == NULL) {
		return false;
	}
	SDL_Surface* tempScoreText = NULL;
	tempScoreText = TTF_RenderText_Blended(font2, to_string(bricks->getPoints()).c_str(), {47, 79, 79, 255 });
	textTextureFont2 = SDL_CreateTextureFromSurface(renderer, tempScoreText);
	SDL_QueryTexture(textTextureFont2, 0, 0, &tw, &th);
	dRectFont2 = { 300, 8, tw, th };
	SDL_FreeSurface(tempScoreText);
	TTF_CloseFont(font2);

	//TEXT FOR GAME OVER
	TTF_Font* font3 = TTF_OpenFont("text/Arcade.ttf", 100);
	if (font3 == NULL) {
		return false;
	}
	SDL_Surface* tempGOText = NULL;
	std::string gameOverText = "GAME OVER";
	tempGOText = TTF_RenderText_Blended(font3, gameOverText.c_str(), { 51, 0, 0, 255 });
	textTextureFont3 = SDL_CreateTextureFromSurface(renderer, tempGOText);
	SDL_QueryTexture(textTextureFont3, 0, 0, &tw, &th);
	dRectFont3 = { 80, 150, tw, th };
	SDL_FreeSurface(tempGOText);
	TTF_CloseFont(font3);

	//TEXT FOR WIN
	TTF_Font* font4 = TTF_OpenFont("text/Arcade.ttf", 100);
	if (font4 == NULL) {
		return false;
	}
	SDL_Surface* tempWinText = NULL;
	std::string gameWinText = "YOU WIN";
	tempWinText = TTF_RenderText_Blended(font4, gameWinText.c_str(), { 51, 0, 0, 255 });
	textTextureFont4 = SDL_CreateTextureFromSurface(renderer, tempWinText);
	SDL_QueryTexture(textTextureFont4, 0, 0, &tw, &th);
	dRectFont4 = { 100, 150, tw, th };
	SDL_FreeSurface(tempWinText);
	TTF_CloseFont(font4);

	return true;
}

void Game::update() {

	//update ball position with speed:
	ball.ballSpeed();

	//ball collision with paddle:
	ball.checkCollision(paddle.getPaddleXPos(), paddle.getPaddleYPos(), paddle.getPaddleWidth(), paddle.getPaddleHeight());

	//ball collision with walls:
	ball.collisionWalls();

	double xSpeed = ball.getBallXSpeed();	//make new variables for ball's speed to manipulate the existing values of ball's speed
	double ySpeed = ball.getBallYSpeed();

	//ball collision with bricks:
	bricks->checkCollision(ball.getBallXPos(), ball.getBallYPos(), ySpeed, xSpeed, ball.getBallWidth(), ball.getBallHeight());

	//update the ball's speed with modified speed
	ball.setBallYSpeed(ySpeed);	//set ball's speed value to the new variable which is reversing speed when it hits brick 
	ball.setBallXSpeed(xSpeed);

	if (ball.getLives() == 0) {	//if lives = 0, reset ball speed and position, and paddle position
		ball.setBallXPos(275);
		ball.setBallYPos(330);
		ball.setBallXSpeed(0);
		ball.setBallYSpeed(0);
		paddle.setPaddleXPos(225);
		paddle.setPaddleYPos(340);
	}
	else if (bricks->getAllBricksHit()) {
		ball.setBallXPos(275);
		ball.setBallYPos(330);
		ball.setBallXSpeed(0);
		ball.setBallYSpeed(0);
		paddle.setPaddleXPos(225);
		paddle.setPaddleYPos(340);
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
