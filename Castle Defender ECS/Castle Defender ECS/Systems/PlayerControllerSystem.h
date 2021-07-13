#ifndef __PLAYER_CONTROLLER_SYSTEM__
#define __PLAYER_CONTROLLER_SYSTEM__

#include "../Components/Player.h"
#include "../Components/Position.h"
#include "../Components/Animations.h"

#include <BitEngine/System.h>

class PlayerControllerSystem final : public BE::System<Player, Position, Animations>
{
	virtual void update(const std::vector<BE::ArchetypePtr> &archtypes) override;
	virtual void render(const std::vector<BE::ArchetypePtr> &archtypes) override;
};

#endif // !__PLAYER_CONTROLLER_SYSTEM__
