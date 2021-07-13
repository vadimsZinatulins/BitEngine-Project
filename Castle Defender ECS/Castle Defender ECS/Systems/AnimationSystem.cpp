#include "AnimationSystem.h"

#include <BitEngine/Archetype.h>
#include <BitEngine/Time.h>
#include <BitEngine/Renderer.h>
#include <BitEngine/ECS.h>
#include <SDL2/SDL.h>

void AnimationSystem::update(const std::vector<BE::ArchetypePtr> &archtypes)
{
	float dt = BE::Time::getInstance().getDeltaTime();

	for (auto const archetype : archtypes)
	{
		Animations *animations = archetype->getComponentArray<Animations>();

		for (std::size_t i = 0; i < archetype->count(); i++)
		{
			Animation &currentAnimation = animations[i].animations[animations[i].currentAnimation];
			if (currentAnimation.hasEnded())
			{
				if (currentAnimation.nextAnimation == -1)
				{
					ecs->deleteEntity(archetype->getEntityByIndex(i));
				}
				else
				{
					animations[i].currentAnimation = currentAnimation.nextAnimation;
					animations[i].animations[currentAnimation.nextAnimation].reset();
				}
			}
			else
			{
				currentAnimation.duration += dt;
				currentAnimation.currentFrame = (int)(currentAnimation.duration / currentAnimation.durationPerFrame);
				if (currentAnimation.currentFrame > currentAnimation.frames.size() - 1)
				{
					currentAnimation.currentFrame = 0;
				}
			}
		}
	}
}

void AnimationSystem::render(const std::vector<BE::ArchetypePtr> &archtypes)
{
	for (auto const archetype : archtypes)
	{
		Texture *textures = archetype->getComponentArray<Texture>();
		Animations *animations = archetype->getComponentArray<Animations>();
		Position *positions = archetype->getComponentArray<Position>();
		AnimationDimension *dimensions = archetype->getComponentArray<AnimationDimension>();

		for (std::size_t i = 0; i < archetype->count(); i++)
		{
			Animation &currentAnimation = animations[i].animations[animations[i].currentAnimation];
			Frame animationFrame = currentAnimation.frames[currentAnimation.currentFrame];

			SDL_Rect srcRect{ (int)animationFrame.x, (int)animationFrame.y, (int)animationFrame.width, (int)animationFrame.height };
			SDL_Rect dstRect{ (int)positions[i].x, (int)positions[i].y, (int)dimensions[i].width, dimensions[i].height };

			SDL_RenderCopy(BE::Renderer::getInstance(), textures[i].texture, &srcRect, &dstRect);
		}
	}
}
