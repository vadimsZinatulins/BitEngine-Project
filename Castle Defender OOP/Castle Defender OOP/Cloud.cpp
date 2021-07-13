#include "Cloud.h"

#include <BitEngine/Time.h>
#include <BitEngine/Renderer.h>
#include <SDL2/SDL.h>

Cloud::Cloud(float x, float y, float velocity, const char *path) :
	m_x(x),
	m_y(y),
	m_velocity(velocity)
{
	m_texture.load(path);
}

Cloud::~Cloud()
{
}

void Cloud::update()
{
	m_x += m_velocity * BE::Time::getInstance().getDeltaTime();
}

void Cloud::render()
{
	SDL_Rect dstRect{ (int)m_x, (int)m_y, (int)m_width, (int)m_height };
	SDL_RenderCopy(BE::Renderer::getInstance(), m_texture, nullptr, &dstRect);
}
