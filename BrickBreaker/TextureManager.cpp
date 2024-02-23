#include "TextureManager.h"
#include "SDL_image.h"


bool TextureManager::loadTexture(const char* fileName, string id,
	SDL_Renderer* ren) {
	SDL_Surface* tempSurface = IMG_Load(fileName);

	if (tempSurface == 0) {
		return false;	//something went wrong
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
	SDL_FreeSurface(tempSurface);

	if (tex != 0) {
		textureMap[id] = tex;
		return true;
	}

	return false;
}

void TextureManager::drawTexture(std::string id,
	double x, double y,
	int width, int height,
	SDL_Renderer* ren,
	SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = (int)x;
	destRect.y = (int)y;
	SDL_RenderCopyEx(ren, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawOneFrameFromTexture(string id, double x, double y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* ren, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = height;
	srcRect.h = destRect.h = height;
	destRect.x = (int)x;
	destRect.y = (int)y;

	SDL_RenderCopyEx(ren, textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
TextureManager * TextureManager::instance = 0; 