#include "Ground.h"

#include <BitEngine/Renderer.h>
#include <SDL2/SDL.h>

Ground::Ground()
{
	m_texture.load("Res/ground.png");
}

Ground::~Ground()
{
}

void Ground::update()
{
}

void Ground::render()
{
	SDL_Rect dstRect{ (int)m_x, (int)m_y, (int)m_width, (int)m_height };
	SDL_RenderCopy(BE::Renderer::getInstance(), m_texture, nullptr, &dstRect);
}
