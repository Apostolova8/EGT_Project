#include <iostream>
#include "SDL.h"
#include "Game.h"

Game* game = NULL;
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 400;

int main(int argc, char* argv[]) {

	game = new Game();
	game->init("My new window", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
		WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

	game->ttf_init(); //for win and game over
	while (game->isRunning()) {
		game->handleEvents();
		game->update();
		game->render();
		game->ttf_init(); //for lives and points
	}
	game->clean();


	return 0;
}