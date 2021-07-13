#include "Castle.h"

#include <BitEngine/Renderer.h>
#include <SDL2/SDL.h>

Castle::Castle()
{
	m_texture.load("Res/castle.png");
}

Castle::~Castle()
{
}

void Castle::update()
{
}

void Castle::render()
{
	SDL_Rect dstRect{ (int)m_x, (int)m_y, (int)m_width, (int)m_height };
	SDL_RenderCopy(BE::Renderer::getInstance(), m_texture, nullptr, &dstRect);
}
