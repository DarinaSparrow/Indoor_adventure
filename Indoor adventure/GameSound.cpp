#include "GameSound.h"

void GameSound::play(int index)
{
	if (game_sounds[index].getStatus() == Sound::Status::Stopped) game_sounds[index].play();
}

void GameSound::stop(int index)
{
	if (game_sounds[index].getStatus() == Sound::Status::Playing) game_sounds[index].stop();
}

void GameSound::all_stop()
{
	for (int i = 0; i < num_of_sounds; ++i){
		if (game_sounds[i].getStatus() == Sound::Status::Playing) game_sounds[i].stop();
	}
}