#pragma once
#include "Game.h"
#include <string>
#include <map>

using namespace std;

class TextureManager {
public:
	bool loadTexture(const char* fileName, string id, SDL_Renderer* ren);
	void drawTexture(string id, double x, double y, int width, int height, SDL_Renderer* ren,
		SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawOneFrameFromTexture(string id, double x, double y, int width, int height,
		int currentRow, int currentFrame, SDL_Renderer* ren,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	static TextureManager* Instance() {
		if (instance == 0) {
			instance = new TextureManager();
			return instance;
		}
		return instance;
	}
private:
	map<string, SDL_Texture*> textureMap;
	TextureManager() {}
	static TextureManager* instance;

};