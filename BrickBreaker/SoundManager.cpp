#include "SoundManager.h"
#include <iostream>

using namespace std;

SoundManager::SoundManager() {
	Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 4096);
	//Herz       
}

bool SoundManager::load(const char* fileName, string id, int type) {
	//type1 -> music
	//type2 -> sound effect (sfx)
	if (type == 1) {	//music
		Mix_Music* music = Mix_LoadMUS(fileName);
		if (music == 0) {
			cout << "Could not load music" << Mix_GetError() << endl;
			return false;
		}
		s_mMusic[id] = music;
		return true;
	}
	else {
		if (type == 0) {	//sfx
			Mix_Chunk* chunk = Mix_LoadWAV(fileName);
			if (chunk == 0) {
				cout << "Could not load sfx" << Mix_GetError() << endl;
				return false;
			}
			s_mSfxs[id] = chunk;
			return true;
		}
	}
}

void SoundManager::playMusic(string id, int loop, int ms) {
	Mix_FadeInMusic(s_mMusic[id], loop, ms);
}

void SoundManager::playSound(string id, int loop, int ms) {
	Mix_FadeInChannel(-1, s_mSfxs[id], loop, ms);
}

SoundManager* SoundManager::s_mInstance = 0;
