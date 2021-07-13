#include "MovementSystem.h"

#include <BitEngine/Archetype.h>
#include <BitEngine/Time.h>

void MovementSystem::update(const std::vector<BE::ArchetypePtr> &archtypes)
{
	float dt = BE::Time::getInstance().getDeltaTime();

	for (auto const archetype : archtypes)
	{
		Position *positions = archetype->getComponentArray<Position>();
		Velocity *velocities = archetype->getComponentArray<Velocity>();

		for (std::size_t i = 0; i < archetype->count(); i++)
		{
			positions[i].x += velocities[i].dx * dt;
			positions[i].y += velocities[i].dy * dt;
		}
	}
}

void MovementSystem::render(const std::vector<BE::ArchetypePtr> &archtypes)
{
}
