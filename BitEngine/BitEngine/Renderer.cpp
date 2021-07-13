#include "Renderer.h"

#include <SDL2/SDL.h>

namespace BE
{

Renderer Renderer::m_instance;

Renderer &Renderer::getInstance()
{
	return m_instance;
}

Renderer::operator SDL_Renderer *() const
{
	return m_renderer;
}

void Renderer::init(SDL_Window *window)
{
	m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(m_renderer, 0xff, 0xff, 0xff, 0xff);
}

void Renderer::quit()
{
	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

}