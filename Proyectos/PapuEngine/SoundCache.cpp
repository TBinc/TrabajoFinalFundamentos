#include "SoundCache.h"

Sound* SoundCache::getSound(std::string soundPath)
{
	auto mit = _soundMap.find(soundPath);
	if (mit == _soundMap.end()) {
		Sound * sound = new Sound(soundPath);
		_soundMap[soundPath] = sound;
	}
	return _soundMap[soundPath];
}

SoundCache::SoundCache()
{
}


SoundCache::~SoundCache()
{
}
