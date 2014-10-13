#pragma once

#include <string>
#include <map>
#include <memory>

#include <SDL_mixer.h>

namespace Music {

typedef std::shared_ptr<Mix_Chunk> Sound;

bool initialize();
void cleanup();

bool playMusic(const std::string& filename);
std::shared_ptr<Mix_Chunk> loadSound(const std::string& filename);
void playSound(const std::shared_ptr<Mix_Chunk>& chunk);

void setMusicVolume(int volume);
void setSoundVolume(int volume);

}
