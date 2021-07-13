#ifndef __BE_ECS_H__
#define __BE_ECS_H__

#include <memory>
#include <unordered_map>
#include <vector>

#include "Utils/Globals.h"
#include "Entity.h"
#include "System.h"
#include "Archetype.h"

namespace BE
{

class ECS
{
public:
	ECS() = default;
	~ECS() = default;

	template<typename ...Components>
	EntityPtr newEntity(Components ...components)
	{
		Signature signature = genSignature<Components...>();
		ArchetypePtr archetype = findArchetype<Components...>(signature);
		EntityPtr entity = std::make_shared<Entity>();
		entity->signature = signature;
		archetype->trackEntity(entity, components...);

		return entity;
	}

	void deleteEntity(EntityPtr entity)
	{
		auto ptr = m_archetypes.find(entity->signature);
		if (ptr != m_archetypes.end())
		{
			ptr->second->untrackEntity(entity);
		}
	}

	template<typename ...Components>
	void addComponents(EntityPtr entity, Components ...components)
	{
		// Gen signature of the target targetArchetype
		Signature signature = entity->signature;
		(..., signature.set(Utils::componentTypeId<Components>(), true));

		// Retrieve the current targetArchetype of the entity
		ArchetypePtr currArchetype = m_archetypes[entity->signature];

		// Retrieve the target targetArchetype
		auto ptr = m_archetypes.find(signature);
		// Check if target targetArchetype does not exist
		if (ptr == m_archetypes.end())
		{
			// Create a type copy of the old entity's current targetArchetype
			ArchetypePtr targetArchetype = Archetype::newArchetype(currArchetype);
			// For each unexistent component array in new targetArchetype, create this new component array.
			// This is done by checking if the current entity's signature contains a specific component, if it does not exists it means 
			// that the newly created targetArchetype also does not contain an array of this component
			(..., (!entity->signature[Utils::componentTypeId<Components>()] ? (targetArchetype->m_components[Utils::componentTypeId<Components>()] = new ComponentArray<Components>()) : nullptr));

			// Save the new targetArchetype
			m_archetypes.insert({ signature, targetArchetype });

			// Pass ownership of entity from current targetArchetype to new targetArchetype
			currArchetype->passOwnership(entity, targetArchetype);

			// Set the value of new components
			targetArchetype->setComonents(entity, components...);

			// Assign this new targetArchetype for each interested system
			for (auto &pair : m_systems)
			{
				if ((pair.first->signature & signature) == pair.first->signature)
				{
					pair.second.push_back(targetArchetype);
				}
			}
		}
		else
		{
			// Pass ownership of entity from current targetArchetype to new targetArchetype
			currArchetype->passOwnership(entity, ptr->second);

			// Set the value of new components
			ptr->second->setComonents(entity, components...);
		}

		// Update entity's signature
		entity->signature = signature;
	}

	template<typename ...Components>
	void removeComponents(EntityPtr entity)
	{
		// Gen signature of the target targetArchetype
		Signature signature = entity->signature;
		(..., signature.set(Utils::componentTypeId<Components>(), false));

		// Retrieve the current targetArchetype of the entity
		ArchetypePtr currArchetype = m_archetypes[entity->signature];

		//m_archetypes.find(entity->signature)->second->untrackEntity(entity);
		auto ptr = m_archetypes.find(signature);
		if (ptr == m_archetypes.end())
		{
			// Create a type copy of the old entity's current targetArchetype. But copy only some components specified by signature
			ArchetypePtr targetArchetype = Archetype::newArchetype(currArchetype, signature);

			// Save the new targetArchetype
			m_archetypes.insert({ signature, targetArchetype });

			// Pass ownership of the entity from current archetype to the target archetype
			targetArchetype->getOwnership(entity, currArchetype);

			// Assign this new targetArchetype for each interested system
			for (auto &pair : m_systems)
			{
				if ((pair.first->signature & signature) == pair.first->signature)
				{
					pair.second.push_back(targetArchetype);
				}
			}
		}
		else
		{
			// Pass ownership of the entity from current archetype to the target archetype
			ptr->second->getOwnership(entity, currArchetype);
		}

		// Update entity's signature
		entity->signature = signature;
	}

	template<typename T>
	void registerSystem()
	{
		auto pair = std::make_pair<ISystem *, std::vector<ArchetypePtr>>(new T(), {});
		pair.first->ecs = this;
		m_systems.push_back(pair);
	}

	template<typename T>
	T &getComponent(EntityPtr entity)
	{
		return m_archetypes[entity->signature]->getComponentArray<T>()[entity->index];
	}
private:
	friend class Engine;

	void update()
	{
		for (auto const &pair : m_systems)
		{
			pair.first->update(pair.second);
		}
	}

	void render()
	{
		for (auto const &pair : m_systems)
		{
			pair.first->render(pair.second);
		}
	}

	template<typename ...Components>
	ArchetypePtr findArchetype(Signature signature)
	{
		auto ptr = m_archetypes.find(signature);
		if (ptr == m_archetypes.end())
		{
			ArchetypePtr archetype = Archetype::newArchetype<Components...>();
			m_archetypes.insert({ signature, archetype });

			for (auto &pair : m_systems)
			{
				if ((pair.first->signature & signature) == pair.first->signature)
				{
					pair.second.push_back(archetype);
				}
			}

			return archetype;
		}

		return ptr->second;
	}

	std::unordered_map<Signature, ArchetypePtr> m_archetypes{};
	std::vector<std::pair<ISystem *, std::vector<ArchetypePtr>>> m_systems;
};

}

#endif // !__BE_ECS_H__
