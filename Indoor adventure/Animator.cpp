#include "Animator.h"


Animator::Animator(Sprite& sprite) : m_current_animation(nullptr), 
									m_sprite(sprite){}


Animator::Animation& Animator::create_animation(string const& name, string const& texture_name, Time const& duration, bool loop)
{
	m_animations.emplace_back(name, texture_name, duration, loop);

	if (m_current_animation == nullptr) switch_animation(&m_animations.back());

	return m_animations.back();
}


void Animator::switch_animation(Animator::Animation* animation)
{
	if (animation != nullptr) {
		m_sprite.setTexture(AssetManager::get_texture(animation->m_texture_name));
	}

	m_current_animation = animation;
	m_current_time = Time::Zero;
}


bool Animator::switch_animation(string const& name)
{
	auto animation = find_animation(name);
	if (animation != nullptr) {
		switch_animation(animation);
		return true;
	}
	return false;
}


Animator::Animation* Animator::find_animation(string const& name)
{
	for (auto it = m_animations.begin(); it != m_animations.end(); ++it) {
		if (it->m_name == name) return &*it;
	}

	return nullptr;
}


string Animator::get_current_animation_name() const
{
	if (m_current_animation != nullptr) return m_current_animation->m_name;
	return "";
}


void Animator::restart()
{
	m_current_time = Time::Zero;
	end_anim = false;
}


void Animator::update(Time const& dt)
{
	if (m_current_animation == nullptr) return;

	m_current_time += dt;

	float scaled_time = (m_current_time.asSeconds() / m_current_animation->m_duration.asSeconds());
	auto num_of_frames = static_cast<int>(m_current_animation->m_frames.size());
	auto current_frame = static_cast<int>(scaled_time * num_of_frames);

	if (m_current_animation->m_loop) current_frame %= num_of_frames;
	else if (current_frame >= num_of_frames) {
		current_frame = num_of_frames - 1;
		end_anim = true;
	}

	m_sprite.setTextureRect(m_current_animation->m_frames[current_frame]);
}