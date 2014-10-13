#include "music.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include <cassert>
#include <iostream>

namespace Music {

static int sound_volume_ = SDL_MIX_MAXVOLUME / 5;
static int music_volume_ = SDL_MIX_MAXVOLUME / 5;
static Mix_Music* music_ = NULL;
static std::map<std::string, Sound> chunks_;

void setMusicVolume(int volume)
{
	music_volume_ = volume;
	Mix_VolumeMusic(volume);
}

void setSoundVolume(int volume)
{
	sound_volume_ = volume;
}

static void printMixError(const std::string& msg)
{
	std::cout << msg << ": " << Mix_GetError() << std::endl;
}

static void freeMusic()
{
	printf("freeing music_=%p\n", music_);
	if (music_) {
		Mix_FreeMusic(music_);
		music_ = NULL;
	}
}

void cleanup()
{
	Mix_CloseAudio();
	freeMusic();
}

bool initialize()
{
	int rc = Mix_Init(~0);
	if (rc <= 0) {
		printMixError("Mix_Init");
		return false;
	}

	rc = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
	if (rc == -1) {
		printMixError("Mix_OpenAudio");
		return false;
	}

	return true;
}

bool playMusic(const std::string& filename)
{
	freeMusic();
	printf("playing music %s\n", filename.c_str());
	music_ = Mix_LoadMUS(filename.c_str());
	if (!music_) {
		printMixError("Mix_LoadMUS");
		return false;
	}
	int rc = Mix_PlayMusic(music_, 1);
	if (rc == -1) {
		printMixError("Mix_PlayMusic");
		return false;
	}
	return true;
}

std::shared_ptr<Mix_Chunk> loadSound(const std::string& filename)
{
	auto it = chunks_.find(filename);
	if (it != chunks_.end())
		return it->second;

	auto chunk = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(filename.c_str()));
	if (!chunk) {
		printMixError("Mix_LoadMUS");
		return NULL;
	}
	chunks_[filename] = chunk;
	return chunk;
}

void playSound(const std::shared_ptr<Mix_Chunk>& chunk)
{
	Mix_VolumeChunk(chunk.get(), sound_volume_);
	Mix_PlayChannel(-1, chunk.get(), 0);
}

}
