#include "TextureManager.h"
#include "Renderer.h"

#include <SDL2/SDL_image.h>
#include <iostream>

namespace BE
{

TextureManager TextureManager::m_instance;

TextureManager &TextureManager::getInstance()
{
	return m_instance;
}

void *TextureManager::loadTexture(const std::string &path)
{
	auto ptr = m_textues.find(path);
	if (ptr == m_textues.end())
	{
		SDL_Surface *surface = IMG_Load(path.c_str());
		if (!surface)
		{
			return nullptr;
		}

		SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer::getInstance(), surface);
		if (!texture)
		{
			return nullptr;
		}

		m_textues[path] = texture;

		return texture;
	}

	return ptr->second;
}

void TextureManager::clear()
{
}

}