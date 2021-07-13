#ifndef __GRAVITY_SYSTEM_H__
#define __GRAVITY_SYSTEM_H__

#include "../Components/Velocity.h"
#include "../Components/Gravity.h"

#include <BitEngine/System.h>

class GravitySystem final : public BE::System<Velocity, Gravity>
{
	virtual void update(const std::vector<BE::ArchetypePtr> &archtypes) override;
	virtual void render(const std::vector<BE::ArchetypePtr> &archtypes) override;
};

#endif // !__GRAVITY_SYSTEM_H__
