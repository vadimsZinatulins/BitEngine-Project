#ifndef __ANIMATIONS_SYSTEM_H__
#define __ANIMATIONS_SYSTEM_H__

#include "../Components/Texture.h"
#include "../Components/Animations.h"
#include "../Components/Position.h"
#include "../Components/AnimationDimension.h"

#include <BitEngine/System.h>

class AnimationSystem final : public BE::System<Texture, Animations, Position, AnimationDimension>
{
	// Inherited via System
	virtual void update(const std::vector<BE::ArchetypePtr> &archtypes) override;
	virtual void render(const std::vector<BE::ArchetypePtr> &archtypes) override;
};

#endif // !__ANIMATIONS_SYSTEM_H__
