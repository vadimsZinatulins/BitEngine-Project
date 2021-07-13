#ifndef __ENEMY_SYSTEM_H__
#define __ENEMY_SYSTEM_H__

#include "../Components/Position.h"
#include "../Components/Velocity.h"
#include "../Components/Animations.h"
#include "../Components/Enemy.h"

#include <BitEngine/System.h>
#include <vector>

struct EnemySystem final : public BE::System<Enemy, Position, Velocity, Animations>
{
	EnemySystem();
	~EnemySystem();

	virtual void update(const std::vector<BE::ArchetypePtr> &archtypes) override;
	virtual void render(const std::vector<BE::ArchetypePtr> &archtypes) override;

	static std::vector<Position> explosionsToProcess;
};

#endif // !__ENEMY_SYSTEM_H__
