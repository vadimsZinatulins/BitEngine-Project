#ifndef __GAME_H__
#define __GAME_H__

#include <BitEngine/Engine.h>

struct Game final : public BE::Engine
{
	virtual void initialize() override;
	virtual void shutdown() override;
};


#endif // !__GAME_H__
