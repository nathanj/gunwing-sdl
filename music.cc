#include "music.h"

#include <chrono>
#include <cassert>
#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>

namespace Music
{

static int sound_volume_ = SDL_MIX_MAXVOLUME / 5;
static int music_volume_ = SDL_MIX_MAXVOLUME / 5;
static Mix_Music* music_ = NULL;
static std::map<std::string, Sound> chunks_;
static std::vector<Sound> sound_queue_;

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

bool playMusic(const std::string& filename, std::chrono::milliseconds fade)
{
        freeMusic();
        printf("playing music %s\n", filename.c_str());
        music_ = Mix_LoadMUS(filename.c_str());
        if (!music_) {
                printMixError("Mix_LoadMUS");
                return false;
        }
        if (fade.count() == 0) {
                int rc = Mix_PlayMusic(music_, 1);
                if (rc == -1) {
                        printMixError("Mix_PlayMusic");
                        return false;
                }
        } else {
                int rc = Mix_FadeInMusic(music_, -1, fade.count());
                if (rc == -1) {
                        printMixError("Mix_FadeInMusic");
                        return false;
                }
        }
        return true;
}

bool stopMusic(std::chrono::milliseconds fade)
{
        int rc = Mix_FadeOutMusic(fade.count());
        if (rc == 0) {
                printMixError("Mix_FadeOutMusic");
                return false;
        }
        return true;
}

Sound loadSound(const std::string& filename)
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

void update()
{
        for (auto& s : sound_queue_)
                playSound(s);
        sound_queue_.clear();
}

void queueSound(const Sound& chunk)
{
        for (auto& s : sound_queue_)
                if (s.get() == chunk.get())
                        return;
        sound_queue_.push_back(chunk);
}

void playSound(const Sound& chunk)
{
        Mix_VolumeChunk(chunk.get(), sound_volume_);
        Mix_PlayChannel(-1, chunk.get(), 0);
}
}
