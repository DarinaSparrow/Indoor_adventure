#pragma once
#include "Header.h"
#include "AssetManager.h"
#include <array>


class GameSound
{
private:
	static const int num_of_sounds = 5;
	array<Sound, num_of_sounds> game_sounds;

public:
	GameSound() {
		array<string, num_of_sounds> name_files{ };
		for (int i = 0; i < num_of_sounds; ++i) {
			game_sounds[i].setBuffer(AssetManager::get_sound_buffer(name_files[i]));
		}

		game_sounds[0].setLoop(true);
	}

	void play(int index);
	void stop(int index);
	void all_stop();
};

