#include "TextureRenderSystem.h"

#include <BitEngine/Archetype.h>
#include <BitEngine/Renderer.h>
#include <SDL2/SDL.h>

void TextureRenderSystem::update(const std::vector<BE::ArchetypePtr> &archtypes) {}

void TextureRenderSystem::render(const std::vector<BE::ArchetypePtr> &archtypes)
{
	for (auto const archetype : archtypes)
	{
		Texture *textures = archetype->getComponentArray<Texture>();
		Position *positions = archetype->getComponentArray<Position>();
		Dimension *dimensions = archetype->getComponentArray<Dimension>();

		for (std::size_t i = 0; i < archetype->count(); i++)
		{
			SDL_Rect dstRect{ (int)positions[i].x, (int)positions[i].y, (int)dimensions[i].width, dimensions[i].height };
			SDL_RenderCopy(BE::Renderer::getInstance(), textures[i].texture, nullptr, &dstRect);
		}
	}
}
