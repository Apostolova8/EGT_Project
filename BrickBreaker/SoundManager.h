#pragma once
#include <iostream>
#include <map>
#include "Game.h"
#include "SDL_mixer.h"

using namespace std;

class SoundManager {

public:
	static SoundManager* Instance() {
		if (s_mInstance == 0) {
			s_mInstance = new SoundManager();
			return s_mInstance;
		}
		return s_mInstance;
	}

	bool load(const char* fileName, string id, int type);
	void playSound(string id, int loop, int ms = 0);
	void playMusic(string id, int loop, int ms = 0);

private:
	static SoundManager* s_mInstance;
	map<string, Mix_Chunk*> s_mSfxs;
	map<string, Mix_Music*> s_mMusic;
	//mix_chunk is for sounds, mix_musix is for music
	SoundManager();
	~SoundManager();
};