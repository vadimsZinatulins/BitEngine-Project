#ifndef __BE_SYSTEM_H__
#define __BE_SYSTEM_H__

#include <vector>

#include "utils/Globals.h"
#include "Archetype.h"

namespace BE
{

class ECS;

struct ISystem
{
	ISystem(Signature s) : signature(s) {}
	virtual ~ISystem() {}
	virtual void update(const std::vector<ArchetypePtr> &archtypes) = 0;
	virtual void render(const std::vector<ArchetypePtr> &archtypes) = 0;

	Signature signature;

	ECS *ecs{ nullptr };
};

template<typename ...Queries>
struct System : public ISystem
{
	System() : ISystem(genSignature<Queries...>()) {}
	virtual ~System() {}

	virtual void update(const std::vector<ArchetypePtr> &archtypes) = 0;
	virtual void render(const std::vector<ArchetypePtr> &archtypes) = 0;
};

}

#endif // !__BE_SYSTEM_H__
