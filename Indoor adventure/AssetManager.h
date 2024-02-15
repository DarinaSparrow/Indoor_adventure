#pragma once
#include "header.h"
#include <map>


// Класс менеджера ресурсов
// Реализован на основе Singleton - у данного класса может быть всего один объект 
class AssetManager
{
private:
	map<string, Texture> m_textures;
	map<string, SoundBuffer> m_sound_buffers;
	map<string, Font> m_fonts;

	static AssetManager* sInstance;
public:
	AssetManager();

	static Texture& get_texture(string const& filename);
	static SoundBuffer& get_sound_buffer(string const& filename);
	static Font& get_font(string const& filename);
};

