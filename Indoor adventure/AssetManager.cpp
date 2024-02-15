#include "AssetManager.h"


AssetManager* AssetManager::sInstance = nullptr;


AssetManager::AssetManager()
{
	if (sInstance == nullptr) 	sInstance = this;
}


Texture& AssetManager::get_texture(string const& filename)
{
	auto& tex_map = sInstance->m_textures;
	auto pairFound = tex_map.find(filename);

	if (pairFound != tex_map.end()) {
		return pairFound->second;
	}
	else {
		auto& texture = tex_map[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}


SoundBuffer& AssetManager::get_sound_buffer(string const& filename)
{
	auto& sound_buf_map = sInstance->m_sound_buffers;
	auto pairFound = sound_buf_map.find(filename);

	if (pairFound != sound_buf_map.end()) {
		return pairFound->second;
	}
	else {
		auto& sound_buf = sound_buf_map[filename];
		sound_buf.loadFromFile(filename);
		return sound_buf;
	}
}


Font& AssetManager::get_font(string const& filename)
{
	auto& font_map = sInstance->m_fonts;
	auto pairFound = font_map.find(filename);

	if (pairFound != font_map.end()) {
		return pairFound->second;
	}
	else {
		auto& font = font_map[filename];
		font.loadFromFile(filename);
		return font;
	}
}
