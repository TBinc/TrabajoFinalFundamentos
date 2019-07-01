#pragma once
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <string>

class Sound
{
private:
	Mix_Chunk * Chunk = nullptr;
public:
	Mix_Chunk * getSound() { return Chunk; }
	void playSound();
	Sound(std::string path);
	~Sound();
};

