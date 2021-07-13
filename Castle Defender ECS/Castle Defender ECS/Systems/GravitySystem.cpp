#include "GravitySystem.h"

#include <BitEngine/Archetype.h>
#include <BitEngine/Time.h>

void GravitySystem::update(const std::vector<BE::ArchetypePtr> &archtypes)
{
	float dt = BE::Time::getInstance().getDeltaTime();

	for (auto const archetype : archtypes)
	{
		Velocity *velocities= archetype->getComponentArray<Velocity>();
		Gravity *forces = archetype->getComponentArray<Gravity>();

		for (std::size_t i = 0; i < archetype->count(); i++)
		{
			velocities[i].dy -= forces[i].force * dt;
		}
	}
}

void GravitySystem::render(const std::vector<BE::ArchetypePtr> &archtypes)
{
}
