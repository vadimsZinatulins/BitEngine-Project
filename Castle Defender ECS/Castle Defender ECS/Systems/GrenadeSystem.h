#ifndef __GRENADE_SYSTEM_H__
#define __GRENADE_SYSTEM_H__


#include "../Components/Grenade.h"
#include "../Components/Position.h"

#include <BitEngine/System.h>

class GrenadeSystem final : public BE::System<Grenade, Position>
{
	virtual void update(const std::vector<BE::ArchetypePtr> &archtypes) override;
	virtual void render(const std::vector<BE::ArchetypePtr> &archtypes) override;
};

#endif // !__GRENADE_SYSTEM_H__
