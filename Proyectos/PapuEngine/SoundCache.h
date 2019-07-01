#pragma once
#include "Sound.h"
#include <map>
#include <string>

class SoundCache
{
private:
	std::map<std::string, Sound*> _soundMap;
public:
	Sound* getSound(std::string soundPath);
	SoundCache();
	~SoundCache();
};

