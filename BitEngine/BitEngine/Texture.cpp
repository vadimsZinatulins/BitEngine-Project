#include "Texture.h"
#include "TextureManager.h"
namespace BE
{

void Texture::load(const std::string &path)
{
	m_texture = (SDL_Texture *)TextureManager::getInstance().loadTexture(path);
}

Texture::operator SDL_Texture *() const
{
	return m_texture;
}

}