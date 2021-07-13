#ifndef __MOVEMENT_SYSTEM_H__
#define __MOVEMENT_SYSTEM_H__

#include "../Components/Position.h"
#include "../Components/Velocity.h"

#include <BitEngine/System.h>

struct MovementSystem final : public BE::System<Position, Velocity>
{
	virtual void update(const std::vector<BE::ArchetypePtr> &archtypes) override;
	virtual void render(const std::vector<BE::ArchetypePtr> &archtypes) override;
};

#endif // !__MOVEMENT_SYSTEM_H__
