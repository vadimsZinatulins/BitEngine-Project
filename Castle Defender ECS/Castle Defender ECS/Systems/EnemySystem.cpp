#include "EnemySystem.h"

#include <BitEngine/Archetype.h>
#include <BitEngine/ECS.h>
#include <cmath>

std::vector<Position> EnemySystem::explosionsToProcess;

EnemySystem::EnemySystem()
{
	explosionsToProcess.clear();
}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::update(const std::vector<BE::ArchetypePtr> &archtypes)
{
	for (auto const archetype : archtypes)
	{
		Position *positions = archetype->getComponentArray<Position>();
		Animations *animations = archetype->getComponentArray<Animations>();

		for (std::size_t i = 0; i < archetype->count(); i++)
		{
			for (auto grenadePosition : explosionsToProcess)
			{

				if (positions[i].x > grenadePosition.x - 150 && positions[i].x < grenadePosition.x + 150)
				{
					ecs->deleteEntity(archetype->getEntityByIndex(i));
				}
			}

			if (positions[i].x >= 575)
			{
				positions[i].x = 575;
				animations[i].currentAnimation = 1;
				ecs->removeComponents<Velocity>(archetype->getEntityByIndex(i));
			}
		}
	}

	explosionsToProcess.clear();
}

void EnemySystem::render(const std::vector<BE::ArchetypePtr> &archtypes)
{
}
