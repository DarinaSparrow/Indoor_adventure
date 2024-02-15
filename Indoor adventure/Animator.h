#pragma once
#include "header.h"
#include "AssetManager.h"
#include <vector>
#include <list>


// Класс для реализации анимаций, реализующая анимацию на уровне переходов кадров
class Animator
{
public:
	// Структура, реализующая анимацию на уровне визуализации каждого самостоятельного кадра
	struct Animation
	{
		string m_name;
		string m_texture_name;
		vector<IntRect> m_frames;
		Time m_duration;
		bool m_loop;

		Animation(string const& name, string const& textureName,
			Time const& duration, bool looping) :m_name(name), m_texture_name(textureName),
			m_duration(duration), m_loop(looping) {}

		void AddFrames(Vector2i const& start_from, Vector2i const& frame_size, unsigned int frames, unsigned int traccia) {
			Vector2i current = start_from;
			for (unsigned int t = 0; t < traccia; t++) {
				for (unsigned int i = 0; i < frames; i++) {
					m_frames.push_back(IntRect(current.x, current.y, frame_size.x, frame_size.y));
					current.x += frame_size.x;
				}
				current.y += frame_size.y;
				current.x = start_from.x;
			}
		}
	};

	explicit Animator(Sprite& sprite);

	Animator::Animation& create_animation(string const& name,
		string const& texture_name, Time const& duration, bool loop = false);

	void update(Time const& dt);

	bool switch_animation(string const& name);

	string get_current_animation_name() const;

	void restart();

	bool get_end_anim() const
	{
		return end_anim;
	}
private:
	Animator::Animation* find_animation(string const& name);

	void switch_animation(Animator::Animation* animation);

	Sprite& m_sprite;
	Time m_current_time;
	list<Animator::Animation> m_animations;
	Animator::Animation* m_current_animation;
	bool end_anim = false;
};
