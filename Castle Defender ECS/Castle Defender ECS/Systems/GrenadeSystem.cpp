#include "GrenadeSystem.h"
#include "../Components/Texture.h"
#include "../Components/AnimationDimension.h"
#include "../Components/Animations.h"
#include "EnemySystem.h"

#include <BitEngine/Archetype.h>
#include <BitEngine/ECS.h>

void GrenadeSystem::update(const std::vector<BE::ArchetypePtr> &archtypes)
{
	for (auto const archetype : archtypes)
	{
		Position *positions = archetype->getComponentArray<Position>();

		for (std::size_t i = 0; i < archetype->count(); i++)
		{
			if (positions[i].y >= 500)
			{
				Animations explosionAnimation;

				Animation mainAnimation;
				mainAnimation.frames.push_back({ 0, 0, 200, 100 });
				mainAnimation.frames.push_back({ 200, 0, 200, 100 });
				mainAnimation.frames.push_back({ 400, 0, 200, 100 });
				mainAnimation.frames.push_back({ 600, 0, 200, 100 });
				mainAnimation.frames.push_back({ 800, 0, 200, 100 });
				mainAnimation.frames.push_back({ 1000, 0, 200, 100 });
				mainAnimation.durationPerFrame = 0.05f;
				mainAnimation.nextAnimation = -1;

				explosionAnimation.animations.push_back(mainAnimation);
				explosionAnimation.currentAnimation = 0;

				EnemySystem::explosionsToProcess.push_back(positions[i]);

				ecs->newEntity<Position, Texture, Animations, AnimationDimension>({ positions[i].x - 100, positions[i].y - 50 }, "Res/explosion_sprite.png", explosionAnimation, { 200.0f, 100.0f });
				ecs->deleteEntity(archetype->getEntityByIndex(i));
			}
		}
	}
}

void GrenadeSystem::render(const std::vector<BE::ArchetypePtr> &archtypes)
{
}
