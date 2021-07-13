#include "SkySystem.h"

#include <BitEngine/Archetype.h>
#include <BitEngine/Renderer.h>
#include <BitEngine/Time.h>
#include <SDL2/SDL.h>

void SkySystem::update(const std::vector<BE::ArchetypePtr> &archtypes)
{
	float speed = 50.0f;
	float dt = BE::Time::getInstance().getDeltaTime();

	for (auto const archetype : archtypes)
	{
		Position *positions = archetype->getComponentArray<Position>();

		for (std::size_t i = 0; i < archetype->count(); i++)
		{
			if (positions[i].x > 0)
			{
				positions[i].x -= speed * dt;
			}
		}
	}
}

void SkySystem::render(const std::vector<BE::ArchetypePtr> &archtypes)
{
	for (auto const archetype : archtypes)
	{
		Position *positions = archetype->getComponentArray<Position>();
		Texture *textures = archetype->getComponentArray<Texture>();

		for (std::size_t i = 0; i < archetype->count(); i++)
		{
			SDL_Rect srcRect{ (int)positions[i].x, (int)positions[i].y, 800, 600 };
			SDL_Rect dstRect{ 0, 0, 800, 600 };
			SDL_RenderCopy(BE::Renderer::getInstance(), textures[i].texture, &srcRect, &dstRect);
		}
	}
}