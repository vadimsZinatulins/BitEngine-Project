#ifndef __SKY_SYSTEM_H__
#define __SKY_SYSTEM_H__

#include "../Components/Position.h"
#include "../Components/Texture.h"
#include "../Components/Sky.h"

#include <BitEngine/System.h>

struct SkySystem final : public BE::System<Sky, Position, Texture>
{
	virtual void update(const std::vector<BE::ArchetypePtr> &archtypes);
	virtual void render(const std::vector<BE::ArchetypePtr> &archtypes);
};

#endif // !__SKY_SYSTEM_H__
