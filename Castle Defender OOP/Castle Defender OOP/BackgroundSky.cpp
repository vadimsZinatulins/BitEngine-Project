#include "BackgroundSky.h"

#include <BitEngine/Time.h>
#include <BitEngine/Renderer.h>
#include <SDL2/SDL.h>

BackgroundSky::BackgroundSky()
{
	m_texture.load("Res/background_sky.png");
}

BackgroundSky::~BackgroundSky()
{
}

void BackgroundSky::update()
{
	if (m_x > 0)
	{
		m_x -= m_speed * BE::Time::getInstance().getDeltaTime();
	}
}

void BackgroundSky::render()
{
	SDL_Rect srcRect{ (int)m_x, (int)m_y, 800, 600 };
	SDL_Rect dstRect{ 0, 0, 800, 600 };

	SDL_RenderCopy(BE::Renderer::getInstance(), m_texture, &srcRect, &dstRect);
}
